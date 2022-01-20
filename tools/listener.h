#pragma once
#include <SFML/Graphics.hpp>
#include "object.h"

using namespace sf;
class EventListener{
public:
    static void checkForEvents(RenderWindow &window,Event &event);
};

class StatusChecker{
public:
    static void checkKeyboardStatus();
    static void checkMouseStatus(PhysicalObject &object, RenderWindow &window);

};

#include "listener.cpp"
