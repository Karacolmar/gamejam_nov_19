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

int gamestate = 1;

Player *player = NULL;
orxOBJECT *menu, *exitButton, *optionenButton, *creditsButton, *playButton, *level1;

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

    if(gamestate == STATE_MENU)
    {
        // Create the viewport
        orxViewport_CreateFromConfig("Viewport");
        menu = orxObject_CreateFromConfig("Menu");

        //Get the Children of Menu
        exitButton      = orxObject_GetOwnedChild(menu);
        optionenButton  = orxObject_GetOwnedSibling(orxObject_GetOwnedChild(menu));
        creditsButton   = orxObject_GetOwnedSibling(orxObject_GetOwnedSibling(orxObject_GetOwnedChild(menu)));
        playButton      = orxObject_GetOwnedSibling(orxObject_GetOwnedSibling(orxObject_GetOwnedSibling(orxObject_GetOwnedChild(menu))));
        orxLOG(orxObject_GetName(exitButton));
        orxLOG(orxObject_GetName(optionenButton));
        orxLOG(orxObject_GetName(creditsButton));
        orxLOG(orxObject_GetName(playButton));

    }
    else if(gamestate == STATE_PLAYING)
    {
        // Create the viewport
        orxViewport_CreateFromConfig("Viewport");
        
        level1 = orxObject_CreateFromConfig("Level1");

        // Create the object
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
    orxVECTOR pos;
    if (orxInput_IsActive("LeftClick") && orxInput_HasNewStatus("LeftClick")){
        orxLOG("LeftClick"); // DO Stuff
        orxMouse_GetPosition(&pos);
/*
        if(orxOBox_IsInside(&exitButton, &pos))
        {
            orxLOG("Exit Button Klick"); // DO Stuff
        }*/   
    }


}

/*
    if(orxOBox_IsInside("ExitButton", &pos))
    {
          orxLOG("JAAAAAAAAA"); // DO Stuff
    }   
*/

/*
void orxFASTCALL Update(const orxCLOCK_INFO *_pstClockInfo, void *_pContext)
{ 
}

orxClock_Register(orxClock_FindFirst(orx2F(-1.0f), orxCLOCK_TYPE_CORE), 
                  Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);




void orxFASTCALL Update(const orxCLOCK_INFO *_pstClockInfo, void *_pContext)
{
    if (ufo) {
 
        if (orxInput_IsActive("GoLeft")) {
            orxLOG("LEFT PRESSED!");
        }
    }
}
*/

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
