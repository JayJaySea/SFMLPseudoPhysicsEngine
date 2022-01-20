


void EventListener::checkForEvents(RenderWindow &window, Event &event){

    while(window.pollEvent(event)){

        switch(event.type){

        case Event::Closed:
            window.close();
            break;

        case Event::KeyPressed:
            switch(event.key.code){
            case Keyboard::Space:
                PhysicalObject::pause = ((int)PhysicalObject::pause + 1)%2;
                break;

            default:
                break;
            }
            break;

        default:
            break;

        }
    }
}

void StatusChecker::checkKeyboardStatus(){}

void StatusChecker::checkMouseStatus(PhysicalObject &object, RenderWindow &window){
    if(Mouse::isButtonPressed(Mouse::Left)){
        object.moveWithMouse(object, window);
    } else { object.is_clicked = false; object.is_held = false;}
}
