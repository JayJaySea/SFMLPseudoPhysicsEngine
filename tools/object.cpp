bool PhysicalObject::pause = false;

PhysicalObject::PhysicalObject(float m){
    this->m = m;
}

void PhysicalObject::gravity(PhysicalObject &object){
    if(!(object.is_clicked)&&!(pause)){
        time_elapsed += t_g;
        t_g = t_for_gravity.getElapsedTime().asSeconds();
        t_for_gravity.restart();

        h = (v_y * t_g + 0.5*g*pow(t_g,2))*100;
        v_y += g*t_g;
        //std::cout << v_y << std::endl;
    }
    else {
        t_for_gravity.restart();
        time_elapsed = 0;
    }
    //std::cout << object.did_collided << std::endl;
}

void PhysicalObject::checkForCollision(PhysicalObject &object1, PhysicalObject &object2){
    if((object2.getPosition().y - (object1.getPosition().y + object1.getGlobalBounds().height) < h)&&(h > 0)){
        h = object2.getPosition().y - (object1.getPosition().y + object1.getGlobalBounds().height) + 1;
    }
    if(object1.getGlobalBounds().intersects(object2.getGlobalBounds())){
        v_x *= 0.9;

        if(bug_handling_tool){
            v_y *= -0.6;
            bug_handling_tool = false;
        }

        //v_y = v_y_max*0.6;

        object1.did_collided = true;
    }else {
        object1.did_collided = false;
        bug_handling_tool = true;
    }
}

void PhysicalObject::moveWithMouse(PhysicalObject &object, RenderWindow &window){
    if((Mouse::getPosition(window).y >= object.getPosition().y)&&(Mouse::getPosition(window).y <= object.getPosition().y + object.getGlobalBounds().height)&&(Mouse::getPosition(window).x >= object.getPosition().x)&&(Mouse::getPosition(window).x <= object.getPosition().x + object.getGlobalBounds().width)){
        object.is_clicked = true;
    }

    if(object.is_clicked){
        object.setPosition(Vector2f(Mouse::getPosition(window).x - (int)object.getGlobalBounds().width/2,Mouse::getPosition(window).y - (int)object.getGlobalBounds().height/2));
    }
}

Vector2f PhysicalObject::currentVelocity(){
    return Vector2f(v_x,v_y);
}

void PhysicalObject::throwVelocity(PhysicalObject &object, RenderWindow &window){
    if(object.is_clicked){
        t_t = t_for_throw.restart().asSeconds();

        previous_s_y = s_y;
        s_y = object.getPosition().y;
        v_y = ((s_y - previous_s_y)/t_t)/250;

        previous_s_x = s_x;
        s_x = object.getPosition().x;
        v_x = ((s_x - previous_s_x)/t_t)/250;
    }
    else{
        s_x = Mouse::getPosition(window).x;
        s_y = Mouse::getPosition(window).y;
        t_for_throw.restart();
    }
}

void PhysicalObject::moveObject(PhysicalObject &object){
    if(!pause){
        object.move(Vector2f(v_x,h));
    }
}

void PhysicalObject::loopWorld(PhysicalObject &object, RenderWindow &window){
    if(object.getPosition().x > window.getSize().x){
        object.setPosition(Vector2f(0,object.getPosition().y));
    }
    if(object.getPosition().x < -20){
        object.setPosition(Vector2f(window.getSize().x,object.getPosition().y));
    }
}

void PhysicalObject::measureCurrentHeight(PhysicalObject &object, PhysicalObject &ground){
    object.h_current = ground.getPosition().y - (object.getPosition().y + object.getGlobalBounds().height)+1;
    //std::cout << object.h_current << std::endl;
}

void PhysicalObject::measureMaxHeight(PhysicalObject &object){
    if((v_y <= 1)||(v_y <= -1)){
        object.h_max = object.h_current;
    }
    //std::cout << object.h_max << std::endl;
}

void PhysicalObject::velocityReflection(PhysicalObject &object){
    if(did_collided){
        std::cout << v_y << std::endl;
        v_y = v_y_max*0.6;
        std::cout << v_y << std::endl;
        //if(v_y_max)
    }
}
