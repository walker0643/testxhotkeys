#include "xkeygrab.h"

XKeyGrab::XKeyGrab(
        Display *display, int keycode, unsigned int modifiers,
        Window grab_window, Bool owner_events, int pointer_mode,
        int keyboard_mode) :
    _display(display),
    _keycode(keycode),
    _modifiers(modifiers),
    _grab_window(grab_window)
{
    XGrabKey(
            display, keycode, modifiers, grab_window, owner_events,
            pointer_mode, keyboard_mode);
}

XKeyGrab::XKeyGrab(XKeyGrab &&other) noexcept :
    _display(other._display),
    _keycode(other._keycode),
    _modifiers(other._modifiers),
    _grab_window(other._grab_window)
{
    // _display is the only resource
    other._display = nullptr;
}

XKeyGrab::~XKeyGrab()
{
    if (_display != nullptr)
        XUngrabKey(_display, _keycode, _modifiers, _grab_window);
}
