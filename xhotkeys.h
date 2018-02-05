#pragma once
#include "xkeygrab.h"
#include <map>

class XHotkeys
{
public:
    typedef unsigned int keyid_t;

    explicit XHotkeys(Display * display, Window window) :
        _display(display),
        _window(window)
    { }

    keyid_t grab(KeySym keysym, unsigned int modifiers);
    void ungrab(KeySym keysym, unsigned int modifiers);
    void ungrab(keyid_t id);

    bool is_hotkey_event(const XEvent& ev, keyid_t *pid_out = nullptr) const;
    bool id_exists(keyid_t id) const;
    Display * display() const { return _display; }
    Window window() const { return _window; }

private:
    Display * const _display;
    const Window _window;

    std::map<keyid_t, XKeyGrab> _keygrab;

};
