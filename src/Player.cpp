#include "Player.h"

Player* Player::instance = 0;

Player::Player(orxOBJECT* obj, int speed){
    object = obj;
    orxVECTOR left_speed = {(-1*speed), 0, 0};
    orxVECTOR right_speed = {speed, 0, 0};
    orxVECTOR up_speed = {0, (-1*speed), 0};
    orxVECTOR down_speed = {0, speed, 0};
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

Player* Player::create(orxOBJECT* obj, int speed){
    if (instance == 0){
        instance = new Player(obj, speed);
    }
    return instance;
}

