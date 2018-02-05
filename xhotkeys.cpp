#include "xhotkeys.h"
#include <assert.h>

inline static XHotkeys::keyid_t make_id(int keycode, unsigned int modifiers)
{
    // keycodes and modifiers use 1 byte each so keyid_t must be >=2 bytes
    return ((XHotkeys::keyid_t)modifiers << 8) | (XHotkeys::keyid_t)keycode;
}

XHotkeys::keyid_t XHotkeys::grab(KeySym keysym, unsigned int modifiers)
{
    int keycode = XKeysymToKeycode(_display, keysym);
    keyid_t id = make_id(keycode, modifiers);
    assert(id_exists(id) == false);
    _keygrab.emplace(
            id, XKeyGrab(
                _display, keycode, modifiers, _window, False, GrabModeAsync,
                GrabModeAsync));
    return id;
}

void XHotkeys::ungrab(KeySym keysym, unsigned int modifiers)
{
    ungrab(make_id(XKeysymToKeycode(_display, keysym), modifiers));
}

void XHotkeys::ungrab(keyid_t id)
{
    auto it = _keygrab.find(id);
    assert(it != _keygrab.end());
    _keygrab.erase(it);
}

bool XHotkeys::is_hotkey_event(const XEvent& ev, keyid_t *pid_out) const
{
    if (ev.type == KeyPress) {
        keyid_t id = make_id(ev.xkey.keycode, ev.xkey.state);
        if (id_exists(id)) {
            if (pid_out != nullptr)
                *pid_out = id;
            return true;
        }
    }
    return false;
}

bool XHotkeys::id_exists(keyid_t id) const
{
    return _keygrab.find(id) != _keygrab.end();
}
