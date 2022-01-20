#pragma once

#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class PhysicalObject: public Sprite{
private:
    float x , y;

    float g = 9.81;
    unsigned long long m;

    float v_x, v_y, h, t_g, time_elapsed = 0;
    float s_x, s_y, previous_s_x, previous_s_y, t_t;
    Clock t_for_gravity, t_for_throw;
public:
    float v_y_max;
    float h_current, h_max;
    static bool pause;
    bool bug_handling_tool = true;
    bool is_clicked = false;
    bool did_collided = false;
    bool is_held = false;
public:
    PhysicalObject(float m);
    void gravity(PhysicalObject &object);
    void throwVelocity(PhysicalObject &object,RenderWindow &window);
    void checkForCollision(PhysicalObject &object1, PhysicalObject &object2);
    void moveObject(PhysicalObject &object);
    void loopWorld(PhysicalObject &object, RenderWindow &window);
    void measureCurrentHeight(PhysicalObject &object, PhysicalObject &ground);
    void measureMaxHeight(PhysicalObject &object);
    void velocityReflection(PhysicalObject &object);

    void moveWithMouse(PhysicalObject &object, RenderWindow &window);
    Vector2f currentVelocity();
};

#include "object.cpp"
