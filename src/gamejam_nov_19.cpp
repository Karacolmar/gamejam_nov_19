/**
 * @file gamejam_nov_19.cpp
 * @date 22-Nov-2019
 */

#include "orx.h"

#define STATE_MENU 0
#define STATE_PLAYING 1
#define STATE_SHOP 2
#define STATE_GAME_OVER 3

int gamestate = 0;

class Player {
    public:
    orxOBJECT* object;
    orxVECTOR left_speed = {-10, 0, 0};
    orxVECTOR right_speed = {10, 0, 0};
    orxVECTOR up_speed = {0, -10, 0};
    orxVECTOR down_speed = {0, 10, 0};
};

Player player;

/*
 * This is a basic code template to quickly and easily get started with a project or tutorial.
 */

/** Init function, it is called when all orx's modules have been initialized
 */
orxSTATUS orxFASTCALL Init()
{
    // Display a small hint in console
    orxLOG("\n* This template project creates a viewport/camera couple and an object"
    "\n* You can play with the config parameters in ../data/config/gamejam_nov_19.ini"
    "\n* After changing them, relaunch the executable to see the changes.");

    if(gamestate == STATE_MENU){
        // Create the viewport
        orxViewport_CreateFromConfig("Viewport");

        // Create the object
        player.object = orxObject_CreateFromConfig("PlayerObject");
    }


    // Done!
    return orxSTATUS_SUCCESS;
}

void handleKeyboardInput()
{
    if(orxInput_IsActive("GoLeft"))
    {
        orxObject_ApplyImpulse(player.object, &player.left_speed, orxNULL);
    }

    if(orxInput_IsActive("GoRight"))
    {
        orxObject_ApplyImpulse(player.object, &player.right_speed, orxNULL);
    }

    if(orxInput_IsActive("GoUp"))
    {
        orxObject_ApplyImpulse(player.object, &player.up_speed, orxNULL);
    }

    if(orxInput_IsActive("GoDown"))
    {
        orxObject_ApplyImpulse(player.object, &player.down_speed, orxNULL);
    }

}

/** Run function, it is called every clock cycle
 */
orxSTATUS orxFASTCALL Run()
{
    orxSTATUS eResult = orxSTATUS_SUCCESS;
        // Should quit?
    if(orxInput_IsActive("Quit"))
    {
        // Update result
        eResult = orxSTATUS_FAILURE;
    }
    /*
    switch(gamestate)
    {
        case STATE_MENU:
        case STATE_SHOP:
        case STATE_PLAYING:
        case STATE_GAME_OVER:
        default: 
    }*/

    handleKeyboardInput();    

    // Done!
    return eResult;
}

/** Exit function, it is called before exiting from orx
 */
void orxFASTCALL Exit()
{
    // Let Orx clean all our mess automatically. :)
}

/** Bootstrap function, it is called before config is initialized, allowing for early resource storage definitions
 */
orxSTATUS orxFASTCALL Bootstrap()
{
    // Add a config storage to find the initial config file
    orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, "../data/config", orxFALSE);

    // Return orxSTATUS_FAILURE to prevent orx from loading the default config file
    return orxSTATUS_SUCCESS;
}

/** Main function
 */
int main(int argc, char **argv)
{
    // Set the bootstrap function to provide at least one resource storage before loading any config files
    orxConfig_SetBootstrap(Bootstrap);

    // Execute our game
    orx_Execute(argc, argv, Init, Run, Exit);

    // Done!
    return EXIT_SUCCESS;
}
