#include "testxhotkeys.h"
#include <iostream>

inline static displayptr_t make_displayptr(char *display_name)
{
    return { XOpenDisplay(display_name), &XCloseDisplay };
}

TestHotkeys::TestHotkeys() :
    _displayptr(make_displayptr(nullptr)),
    _root(DefaultRootWindow(_displayptr.get())),
    _hotkeys(_displayptr.get(), _root)
{ }

int TestHotkeys::run()
{
    add_action(SayHello, XK_H, ControlMask | ShiftMask);
    add_action(Quit, XK_F11, ControlMask | ShiftMask);
    std::cout << "Waiting for hotkey..." << std::endl;
    event_loop();
    std::cout << "successful" << std::endl;
    return 0;
}

void TestHotkeys::add_action(Action action, KeySym keysym, unsigned modifiers)
{
    XHotkeys::keyid_t id = _hotkeys.grab(keysym, modifiers);
    _idaction.emplace(id, action);
    std::cout << std::hex;
    std::cout << "Mapped action " << action << " to id " << id << std::endl;
    std::cout << std::dec;
}

void TestHotkeys::event_loop() const
{
    XSelectInput(_displayptr.get(), _root, KeyPressMask);
    while(1) {
        XEvent ev;
        XNextEvent(_displayptr.get(), &ev);
        XHotkeys::keyid_t id;
        if (_hotkeys.is_hotkey_event(ev, &id)) {
            if (handle_action(_idaction.at(id)))
                break;
        }
    }
}

bool TestHotkeys::handle_action(Action action) const
{
    switch (action) {
    case SayHello:
        std::cout << "Hello!" << std::endl;
        break;
    case Quit:
        break;
    default:
        std::cout << "No action for that hotkey" << std::endl;
    };
    return action == Quit;
}

int main()
{
    return TestHotkeys().run();
}
