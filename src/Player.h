#ifndef PLAYER_H
#define PLAYER_H

#include "orx.h"

class Player {
    private:
    orxOBJECT* object;
    orxVECTOR left_speed;
    orxVECTOR right_speed;
    orxVECTOR up_speed;
    orxVECTOR down_speed;
    
    public:
    Player(orxOBJECT* obj, float speed, float minus_speed);
    orxOBJECT* get_object() {return object;}
    orxVECTOR get_left() {return left_speed;}
    orxVECTOR get_right() {return right_speed;}
    orxVECTOR get_up() {return up_speed;}
    orxVECTOR get_down() {return down_speed;} 
    void move(char direction);
};

#endif