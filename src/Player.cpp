#include "Player.h"
#include <iostream>

Player::Player(orxOBJECT* obj, float speed, float minus_speed){
    object = obj;
    velocity = speed;
    left_speed = {minus_speed, 0, 0};
    right_speed = {speed, 0, 0};
    up_speed = {0, minus_speed, 0};
    down_speed = {0, speed, 0};
    pushing_sheep = false;
}

void Player::move(char direction){
    switch(direction){
        case 'L':
            orxObject_ApplyImpulse(object, &left_speed, orxNULL);
        case 'R':
            orxObject_ApplyImpulse(object, &right_speed, orxNULL);
        case 'U':
            orxObject_ApplyImpulse(object, &up_speed, orxNULL);
        case 'D':
            orxObject_ApplyImpulse(object, &down_speed, orxNULL);
    }    
}

void Player::set_speed(float speed, float minus_speed){
    velocity = speed;
    left_speed = {minus_speed, 0, 0};
    right_speed = {speed, 0, 0};
    up_speed = {0, minus_speed, 0};
    down_speed = {0, speed, 0};
}

void Player::slow_down(){
    velocity = velocity - 5;
    left_speed = {(-1*velocity), 0, 0};
    right_speed = {velocity, 0, 0};
    up_speed = {0, (-1*velocity), 0};
    down_speed = {0, velocity, 0};
}
