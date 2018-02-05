#pragma once

#include "xhotkeys.h"
#include <X11/Xutil.h>  // X constants (XK_*)
#include <memory>
#include <map>

typedef std::unique_ptr<Display, decltype(&XCloseDisplay)> displayptr_t;

class TestHotkeys
{
public:
    explicit TestHotkeys();

    int run();

private:
    enum Action { SayHello, Quit };

    displayptr_t _displayptr;
    Window _root;
    XHotkeys _hotkeys;
    std::map<XHotkeys::keyid_t, Action> _idaction;

    void add_action(Action action, KeySym keysym, unsigned int modifiers);
    void event_loop() const;
    bool handle_action(Action action) const;
};
