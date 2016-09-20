# DeskDrop

While currently in a very early state, DeskDrop will eventually be an applet that can render text and images on the Windows desktop.

### Technical Information

DeskDrop is a DLL-injected solution which subclasses the target window for painting, rather than a bginfo-style solution which changes the Windows wallpaper. The DLL relies on an executable injector (shamelessly copied and adapted from the example located at [http://snipd.net/dll-injection-in-c](http://snipd.net/dll-injection-in-c)).

