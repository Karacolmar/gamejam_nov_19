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
    Player(orxOBJECT* obj, float speed);
    orxOBJECT* getObject() {return object;}
    void move(char direction);
};

#endif