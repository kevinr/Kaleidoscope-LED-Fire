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
#include <Kaleidoscope-LED-Fire.h>

void setup (){
  Kaleidoscope.use(&FireEffect);

  Kaleidoscope.setup();

  FireEffect.activate();
}
```

It is recommended to place the activation of the plugin (the `USE_PLUGINS` call)
as early as possible, so the plugin can catch all relevant key presses.

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

