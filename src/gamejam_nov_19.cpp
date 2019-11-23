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
        //orxObject_CreateFromConfig("SheepObject");
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
        orxVECTOR pos;
        orxLOG("LeftClick"); // DO Stuff
        orxMouse_GetPosition(&pos);

        orxVECTOR vPosition; // The world position of the neighborhood area
        orxVECTOR vSize; // The size of the neighborhood area
        orxVECTOR vPivot; // The pivot of the neighborhood area
        orxOBox_2DSet(&boundingBox, &vPosition, &vPivot, &vSize, 0);
        orxObject_GetPosition(exitButton, &vPosition); 
        orxObject_GetPivot(exitButton, &vPivot); 
        orxObject_GetSize(exitButton, &vSize);

        if(orxOBox_IsInside(&boundingBox, &pos))
        {
            orxLOG("Exit Button Klick"); // DO Stuff
        }

        orxOBJECT *object = orxNULL;
     
        // Let's fetch the mouse's position
        orxVECTOR vPos;
        if(orxRender_GetWorldPosition(orxMouse_GetPosition(&vPos), orxNULL, &vPos) != orxNULL)
        { 
            // Let's see what's currently under the mouse
            orxLOG("Irgendwas gefunden!!!");

            object = orxObject_Pick(&vPos, orxString_GetID("UI"));
            orxLOG(orxObject_GetName(object));
        }
        if(object && (orxInput_HasBeenActivated("LeftClick")))
        {
            // He clicked...so let's start the game if it was the PlayButton
            if(orxString_Compare(orxObject_GetName(object),"PlayButton") == 0)
            {
                //INSERT SOME CODE THAT STARTS YOUR GAME
                orxLOG("PlayButton geklcikt");
                gamestate = 1;
            }
            else if(orxString_Compare(orxObject_GetName(object),"OtherButton") == 0)
            {
                //DO OTHER STUFF FOR OTHER BUTTONS
            }
    }


    }

//orxLOG("Handle Menu Input fertitg");
}


//object that stores the currently highlighted button:
orxOBJECT* highlighted_button = orxNULL;
 
void orxFASTCALL Update(const orxCLOCK_INFO *_pstClockInfo, void *_pstContext)
{
    orxLOG("update aufgerufen");
    //current Button under mouse
    orxOBJECT *object = orxNULL;
 
    // Let's fetch the mouse's position
    orxVECTOR vPos;
    if(orxRender_GetWorldPosition(orxMouse_GetPosition(&vPos), orxNULL, &vPos) != orxNULL)
    { 
        // Let's see what's currently under the mouse
        object = orxObject_Pick(&vPos, orxString_GetID("UI"));
    }
 
    /* 
    // Not hovering the same button as before?
    if(object != highlighted_button)
    {
        // Was hovering a button before?
        if(highlighted_button != orxNULL)
        {
          // Go back to inactive state by removing the current target anim
          orxObject_SetTargetAnim(highlighted_button, orxNULL);
        }
 
        // Are we currently hovering a button?
        if(object != orxNULL)
        {
        // Go to active anim (the anim's name is `Active`, the prefix we defined in config if only used to find the data but doesn't modify the name itself, this makes the animation set reusable between buttons)
        orxObject_SetTargetAnim(object, "Active");
        }
 
        // Keep track of what we're hovering
        highlighted_button = object;
    }*/
    
     // Check if the user clicked on a button
    if(object && (orxInput_HasBeenActivated("LeftClick")))
    {
        // He clicked...so let's start the game if it was the PlayButton
        if(orxString_Compare(orxObject_GetName(object),"PlayButton") == 0)
        {
            //INSERT SOME CODE THAT STARTS YOUR GAME
            gamestate = 1;
        }
        else if(orxString_Compare(orxObject_GetName(object),"OtherButton") == 0)
        {
            //DO OTHER STUFF FOR OTHER BUTTONS
        }
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
