# Kaleidoscope-LED-Fire

![status][st:experimental] [![Build Status][travis:image]][travis:status]

 [travis:image]: https://travis-ci.org/keyboardio/Kaleidoscope-LED-Fire.svg?branch=master
 [travis:status]: https://travis-ci.org/keyboardio/Kaleidoscope-LED-Fire

 [st:stable]: https://img.shields.io/badge/stable-✔-black.svg?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.svg?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.svg?style=flat&colorA=dfb317&colorB=494e52

The `FireEffect` plugin makes waves of light splash out from each keypress.
When idle, it will also simulate gentle rainfall on the keyboard.

## Using the plugin

To use the plugin, one needs to include the header and select the effect.

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-LED-Fire.h>

void setup (){
  Kaleidoscope.use(&FireEffect);

  Kaleidoscope.setup();

  FireEffect.idle_timeout = 5000;  // 5 seconds
  FireEffect.activate();
}
```

It is recommended to place the activation of the plugin (the `USE_PLUGINS` call)
as early as possible, so the plugin can catch all relevant key presses.

## Plugin methods

The plugin provides the `FireEffect` object, which has the following
properties:

### `.idle_timeout`

> When to keys are being pressed, light will periodically splash across
> the keyboard.  This value sets the delay in ms before that starts.
>
> To disable the idle animation entirely, set this to 0.
>
> Default is 5000 (5 seconds).

## Dependencies

* [Kaleidoscope-LEDControl](https://github.com/keyboardio/Kaleidoscope-LEDControl)

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

 [plugin:example]: https://github.com/ToyKeeper/Kaleidoscope-LED-Fire/blob/master/examples/LED-Fire/LED-Fire.ino
