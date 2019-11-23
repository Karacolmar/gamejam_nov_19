/**
 * @file gamejam_nov_19.cpp
 * @date 22-Nov-2019
 */

#include "orx.h"
#include "Player.h"
#include <iostream>

#define STATE_MENU 0
#define STATE_PLAYING 1
#define STATE_OPTIONS 2
#define STATE_GAME_OVER 3

int gamestate = 0;

Player *player = NULL;
orxOBJECT *menu, *exitButton, *optionenButton, *creditsButton, *playButton, *level1;
orxVECTOR pos;

orxOBOX boundingBox;
/*
 * This is a basic code template to quickly and easily get started with a project or tutorial.
 */

/** Init function, it is called when all orx's modules have been initialized
 */
orxSTATUS orxFASTCALL Init()
{
    
    //orxLOG("Init aufgerufen");
    if(gamestate == STATE_MENU)
    {
        // Create the viewport
        orxViewport_CreateFromConfig("Viewport");
        menu = orxObject_CreateFromConfig("Menu");
        //orxLOG("Level Geladen");

        //Get the Children of Menu
        exitButton      = orxObject_GetOwnedChild(menu);
        optionenButton  = orxObject_GetOwnedSibling(orxObject_GetOwnedChild(menu));
        creditsButton   = orxObject_GetOwnedSibling(orxObject_GetOwnedSibling(orxObject_GetOwnedChild(menu)));
        playButton      = orxObject_GetOwnedSibling(orxObject_GetOwnedSibling(orxObject_GetOwnedSibling(orxObject_GetOwnedChild(menu))));
        //orxLOG(orxObject_GetName(exitButton));
        //orxLOG(orxObject_GetName(optionenButton));
        //orxLOG(orxObject_GetName(creditsButton));
        //orxLOG(orxObject_GetName(playButton));

    }
    else if(gamestate == STATE_PLAYING)
    {
        // Create the viewport
        orxViewport_CreateFromConfig("Viewport");
        
        // Create Level
        level1 = orxObject_CreateFromConfig("Level1");
        orxLOG("Level geladen");

        // Create the player
        player = new Player(orxObject_CreateFromConfig("PlayerObject"), 15, -15);
        orxObject_CreateFromConfig("SheepObject");
    }

    // Done!
    return orxSTATUS_SUCCESS;
}

void handleLevelInput()
{
    orxVECTOR player_movement = {0, 0, 0};
    if(orxInput_IsActive("GoLeft")){
        player_movement = player->get_left();
        // player->move('L');
    }
    if(orxInput_IsActive("GoRight")){
        player_movement = player->get_right();
        // player->move('R');
    }
    if(orxInput_IsActive("GoUp")){
        player_movement = player->get_up();
        // player->move('U');
    }
    if(orxInput_IsActive("GoDown")){
        player_movement = player->get_down();
        // player->move('D');
    }
    orxObject_ApplyImpulse(player->get_object(), &player_movement, orxNULL);
}

void handleMenuInput()
{
 //   orxLOG("Handle Menu Input");
    
    if (orxInput_IsActive("LeftClick") && orxInput_HasNewStatus("LeftClick"))
    {
        orxLOG("LeftClick"); // DO Stuff
        orxMouse_GetPosition(&pos);

        orxVECTOR vPosition; // The world position of the neighborhood area
        orxVECTOR vSize; // The size of the neighborhood area
        orxVECTOR vPivot; // The pivot of the neighborhood area
        orxOBox_2DSet(&boundingBox, &vPosition, &vPivot, &vSize, 0);
        orxObject_GetPosition(exitButton, &vPosition); 
        orxObject_GetPivot(exitButton, &vPivot); 
        orxObject_GetSize(exitButton, &vSize);

        orxLOG()

        if(orxOBox_IsInside(&boundingBox, &pos))
        {
            orxLOG("Exit Button Klick"); // DO Stuff
        }
    }

//orxLOG("Handle Menu Input fertitg");
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
    
    //orxLOG("bin in run!");
    switch(gamestate)
    {
        case STATE_MENU: 
            handleMenuInput();
           // orxLOG("handle !");
            break;
        //case STATE_OPTIONS:
        case STATE_PLAYING: 
            handleLevelInput();
            break;
        //case STATE_GAME_OVER:
        //default: orxLOG("default"); 
    }

    //handleLevelInput();    
    //orxLOG("fertig mit run");
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
