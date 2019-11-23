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
    Player(orxOBJECT* obj, int speed);
    static Player* instance;
    
    public:
    static Player* create(orxOBJECT* obj, int speed);
    orxOBJECT* getObject() {return object;}
    void move(char direction);
};

#endif