#pragma once

#include <X11/Xlib.h>

class XKeyGrab
{
public:
    explicit XKeyGrab(
            Display *display, int keycode, unsigned int modifiers,
            Window grab_window, Bool owner_events, int pointer_mode,
            int keyboard_mode);

    XKeyGrab(XKeyGrab &&other) noexcept;

    XKeyGrab() = delete;
    XKeyGrab(const XKeyGrab&) = delete;

    ~XKeyGrab();

private:
    Display *_display;
    int _keycode;
    unsigned int _modifiers;
    Window _grab_window;
};
