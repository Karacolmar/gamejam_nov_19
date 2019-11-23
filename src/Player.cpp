#include "Player.h"
#include <iostream>

Player::Player(orxOBJECT* obj, float speed, float minus_speed){
    object = obj;
    left_speed = {minus_speed, 0, 0};
    right_speed = {speed, 0, 0};
    up_speed = {0, minus_speed, 0};
    down_speed = {0, speed, 0};
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

