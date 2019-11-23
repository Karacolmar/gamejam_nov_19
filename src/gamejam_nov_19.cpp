/**
 * @file gamejam_nov_19.cpp
 * @date 22-Nov-2019
 */

#include "orx.h"
#include "Player.h"

#define STATE_MENU 0
#define STATE_PLAYING 1
#define STATE_OPTIONS 2
#define STATE_GAME_OVER 3

int gamestate = 0;

Player* player;

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
        orxObject_CreateFromConfig("Menu");
        //orxObject_CreateFromConfig("Level1");
        // Create the object
        player = Player::create(orxObject_CreateFromConfig("PlayerObject"), 10);

    }


    // Done!
    return orxSTATUS_SUCCESS;
}

void handleLevelInput()
{
    if(orxInput_IsActive("GoLeft")){
        player->move('L');
    }
    if(orxInput_IsActive("GoRight")){
        player->move('R');
    }
    if(orxInput_IsActive("GoUp")){
        player->move('U');
    }
    if(orxInput_IsActive("GoDown")){
        player->move('D');
    }
}

void handleMenuInput()
{
    orxVECTOR pos;
    if (orxInput_IsActive("LeftClick") && orxInput_HasNewStatus("LeftClick")){
        orxLOG("LeftClick"); // DO Stuff
        orxMouse_GetPosition(&pos);
    }


    if(orxOBox_IsInside("ExitButton", &pos))
    {
          orxLOG("JAAAAAAAAA"); // DO Stuff
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
    
    switch(gamestate)
    {
        case STATE_MENU: handleMenuInput();
        //case STATE_OPTIONS:
        case STATE_PLAYING: handleLevelInput();
        //case STATE_GAME_OVER:
        //default: 
    }

    //handleLevelInput();    

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
