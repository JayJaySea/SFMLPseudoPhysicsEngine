#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <thread>

#include "tools/object.h"
#include "tools/listener.h"

#define LOG(x) std::cout << x << std::endl

using namespace sf;
using namespace std;

int WIDTH = 800;
int HEIGHT = 600;

PhysicalObject ball(2);
PhysicalObject ground(5.96*pow(10,24));
Sprite bg;

RenderWindow window(VideoMode(WIDTH,HEIGHT), "Physics Engine", Style::Titlebar | Style::Close);
Texture texture, background;

void update(){
    Event event;

    EventListener::checkForEvents(window,event);
    StatusChecker::checkKeyboardStatus();
    StatusChecker::checkMouseStatus(ball,window);

    ball.gravity(ball);
    ball.throwVelocity(ball,window);
    ball.checkForCollision(ball, ground);
    ball.moveObject(ball);
    ball.loopWorld(ball,window);
    ball.measureCurrentHeight(ball,ground);
    ball.measureMaxHeight(ball);
    //ball.velocityReflection(ball);
    //std::cout<< ball.currentVelocity().y << std::endl;
}

void render(){
    window.clear(Color::White);
    window.draw(bg);
    window.draw(ball);
    window.display();
}

int main()
{
    float x = WIDTH/2;
    float y = 500-15;

    window.setFramerateLimit(50);

    texture.loadFromFile("texture.png");
    ball.setTexture(texture);
    ball.setTextureRect(IntRect(0,0,15,15));
    ball.setPosition(Vector2f(x,y));

    background.loadFromFile("background.png");
    bg.setTexture(background);
    bg.setPosition(Vector2f(0,0));

    ground.setTexture(background);
    ground.setTextureRect(IntRect(0,500,800,100));
    ground.setPosition(Vector2f(0,500));

    Clock time;
    while(window.isOpen()){
        if(time.getElapsedTime().asMilliseconds() >= 10){
            update();
            time.restart();
        }
        render();
    }

    return 0;
}
