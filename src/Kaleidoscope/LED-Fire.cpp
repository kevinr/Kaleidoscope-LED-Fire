/* -*- mode: c++ -*-
 * Kaleidoscope-LED-Fire
 * Copyright (C) 2018 Kevin Riggle
 * Copyright (C) 2017 Selene Scriven
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Kaleidoscope-LED-Fire.h>
#include <LEDUtils.h>

namespace kaleidoscope {

#define INTERPOLATE 1 // smoother, slower animation
#define MS_PER_FRAME 40  // 40 = 25 fps
#define FRAMES_PER_DROP 120  // max time between raindrops during idle animation

uint8_t FireEffect::surface[2][WP_WID*WP_HGT];
uint8_t FireEffect::page = 0;
uint8_t FireEffect::frames_since_event = 0;
uint16_t FireEffect::idle_timeout = 5000;  // 5 seconds

// map native keyboard coordinates (16x4) into geometric space (14x5)
PROGMEM const uint8_t FireEffect::rc2pos[ROWS*COLS] = {
     0,  1,  2,  3,  4,  5,  6,    59, 66,    7,  8,  9, 10, 11, 12, 13,
    14, 15, 16, 17, 18, 19, 34,    60, 65,   35, 22, 23, 24, 25, 26, 27,
    28, 29, 30, 31, 32, 33, 48,    61, 64,   49, 36, 37, 38, 39, 40, 41,
    42, 43, 44, 45, 46, 47,     58,62, 63,67,    50, 51, 52, 53, 54, 55,
};

EventHandlerResult FireEffect::onKeyswitchEvent(Key &mapped_key, byte row, byte col, uint8_t key_state) {
  if (row >= ROWS || col >= COLS)
    return EventHandlerResult::OK;

  if (keyIsPressed(key_state)) {
    uint8_t offset = (row*COLS)+col;
    surface[page][pgm_read_byte(rc2pos + offset)] = 0xff;
    frames_since_event = 0;
  }

  return EventHandlerResult::OK;
}

// this is a lot smaller than the standard library's rand(),
// and still looks random-ish
uint8_t FireEffect::wp_rand() {
    static uint16_t offset = 0x400;
    offset = ((offset + 1) & 0x4fff) | 0x400;
    return (Kaleidoscope.millisAtCycleStart()/MS_PER_FRAME) + pgm_read_byte(offset);
}

void FireEffect::update(void) {

  // limit the frame rate; one frame every 64 ms
  static uint8_t prev_time = 0;
  uint8_t now = Kaleidoscope.millisAtCycleStart() / MS_PER_FRAME;
  if (now != prev_time) {
      prev_time = now;
  } else {
      return;
  }

  frames_since_event ++;

  // needs two pages of temp map to do the calculations
  uint8_t *newpg = surface[page^1];
  uint8_t *oldpg = surface[page];

  // render fire
  #ifdef INTERPOLATE
  if (!(now & 1)) {  // even frames only
  #endif
  for (uint8_t y = 0; y < WP_HGT; y++) {
    for (uint8_t x = 0; x < WP_WID; x++) {

      // for all but the bottom row, push the fire up
      if (y < WP_HGT - 1) {
          // on even rows, divide by two
          if (y % 2 == 0) {
              newpg[(y * WP_WID) + x] = oldpg[((y + 1) * WP_WID) + x] / 2;
          } else {
              newpg[(y * WP_WID) + x] = oldpg[((y + 1) * WP_WID) + x];
          }
      }
      // for the bottom row, generate new sparks
      else {
        newpg[(y * WP_WID) + x] = wp_rand();
      }
    }
  }
  #ifdef INTERPOLATE
  }
  #endif

  // draw the buffer on the keys
  for (byte r = 0; r < ROWS; r++) {
    for (byte c = 0; c < COLS; c++) {
      uint8_t offset = (r*COLS) + c;
      uint8_t temp = oldpg[pgm_read_byte(rc2pos+offset)];
      #ifdef INTERPOLATE
      if (now & 1) {  // odd frames only
          // average temp with other frame
          temp = ((int16_t)temp + newpg[pgm_read_byte(rc2pos+offset)]) >> 1;
      }
      #endif

      // clamp hue between red and yellow, with yellow = hotter
      int16_t hue = (abs(temp) / 6) & 0xff;

      uint8_t intensity = 0xff;
      if (temp <= 0x7f) {
          intensity = temp * 2;
      }

      cRGB color = hsvToRgb(hue,
                            0xff,
                            ((uint16_t)intensity) & 0xff);

      ::LEDControl.setCrgbAt(r, c, color);
    }
  }

  #ifdef INTERPOLATE
  // swap pages every other frame
  if (!(now & 1)) page ^= 1;
  #else
  // swap pages every frame
  page ^= 1;
  #endif

}

}

kaleidoscope::FireEffect FireEffect;
