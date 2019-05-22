# Kaleidoscope-LED-Fire

The `FireEffect` plugin makes flames that roar from the bottom of your keyboard
and every keypress.

![Keyboardio Model 01 running the FireEffect plugin][video]

![Keyboardio Model 01 running the FireEffect plugin with a key depressed][video-keypress]

[video]: examples/fire-effect.gif
[video-keypress]: examples/fire-effect-keypress.gif

## Using the plugin

To use the plugin, one needs to include the header and select the effect.

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-LEDControl.h>
#include <Kaleidoscope-LED-Fire.h>

KALEIDOSCOPE_INIT_PLUGINS(
  LEDControl,
  LEDOff,
  FireEffect
);

void setup () {
  Kaleidoscope.setup();

  //FireEffect.highlight_wasd = false;      // default; set true to make WASD keys brighter
  FireEffect.activate();
}

void loop() {
  Kaleidoscope.loop();
}
```

## Configuration

The plugin provides one configuration field, `highlight_wasd` (default: `false`), which makes the WASD keys of the standard QWERTY layout brighter, even when the fire effect is almost completely dimmed. Like so:

[highlight-wasd]: examples/fire-effect-highlight-wasd.jpg

The backstory is that, unlike a lot of Keyboardio users, it seems, I mostly use my Model 01 for gaming, and I mostly game at night with the room lights down.  Glancing down in the middle of a madcap Overwatch match to reset my fingers, at the exact moment the LEDs were almost entirely out, was no fun. Hence, this configuration option.

## Dependencies

* [Kaleidoscope-LEDControl](https://github.com/keyboardio/Kaleidoscope-LEDControl)

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

 [plugin:example]: examples/LED-Fire/LED-Fire.ino

## Acknowledgments

The `FireEffect` plugin is based on [Selene Scriven](https://github.com/ToyKeeper/)'s 
excellent [`WavePoolEffect` plugin](https://github.com/ToyKeeper/Kaleidoscope-LED-Wavepool/),
without which I likely would never have succeeded.

It implements a simplified version of the [classic demoscene fire effect as documented by Lode][fire].

[fire]: https://lodev.org/cgtutor/fire.html

Oldsters like me may recall Javier "Jare" Arévalo's classic [firedemo][firedemo] from 1993 (which he recently [ported to HTML5][firedemo-html5]).  Hans Wennborg has written a [nice walkthrough of it][firedemo-walkthrough].

[firedemo]: http://www.iguanademos.com/Jare/wp/?p=2756
[firedemo-html5]: http://www.iguanademos.com/Jare/files/Fire/
[firedemo-walkthrough]: https://www.hanshq.net/fire.html

