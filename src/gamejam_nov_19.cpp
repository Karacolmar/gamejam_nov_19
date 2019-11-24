/**
 * @file gamejam_nov_19.cpp
 * @date 22-Nov-2019
 */

#include "orx.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <unistd.h>

#define STATE_MENU 0
#define STATE_PLAYING 1
#define STATE_WIN 2
#define STATE_GAME_OVER 3
#define STATE_CREDITS 4
#define STATE_INTRO 5
#define STATE_INTRO2 6
#define STATE_INTRO3 7
#define STATE_INTRO4 8
#define STATE_INTRO5 9



int gamestate = 0;
int level_no = 1;

Player *player = NULL;
orxOBJECT *gameover, *menu, *exitButton, *optionenButton, *creditsButton, *playButton, *level, *intro, *scoreObject, *clockObject;

orxS16 score = 0;
orxS32 score_win;
orxS16 time_left;
orxS32 time_lose;


void orxFASTCALL updateTimer(const orxCLOCK_INFO *info, void *object){
    if (gamestate == STATE_PLAYING){
        orxCHAR timerStr[5];
        orxS16 time_passed = orxMath_Floor(info->fTime);
        time_left = time_lose - time_passed;
        orxS16 minutes = orxMath_Floor(time_left/60);
        orxS16 seconds = time_left%60;

        orxString_Print(timerStr, "%02d:%02d", minutes, seconds);

        orxObject_SetTextString((orxOBJECT*)object, timerStr);
    }
}

void startMenu()
{
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

}

void startGame()
{
    if(gamestate == STATE_PLAYING)
    {
        // Create the viewport
        orxViewport_CreateFromConfig("Viewport");
        
        // Create Level
        switch(level_no){
            case 0:
                level = orxObject_CreateFromConfig("Level1");
                level_no += 1;
                if (orxConfig_PushSection("Level1WinLoseCond")){
                    time_lose = orxConfig_GetS32("Time");
                    time_left = time_lose;
                    score_win = orxConfig_GetS32("Points");
                    orxConfig_PopSection();
                }
                orxLOG("Level 1 geladen");
                break;
            case 1:
                level = orxObject_CreateFromConfig("Level2");
                level_no += 1;
                if (orxConfig_PushSection("Level2WinLoseCond")){
                    time_lose = orxConfig_GetS32("Time");
                    time_left = time_lose;
                    score_win = orxConfig_GetS32("Points");
                    orxConfig_PopSection();
                }
                orxLOG("Level 2 geladen");
                break;
            case 2:  // no level3
                level = orxObject_CreateFromConfig("Level1");
                level_no = 1;
                if (orxConfig_PushSection("Level1WinLoseCond")){
                    time_lose = orxConfig_GetS32("Time");
                    time_left = time_lose;
                    score_win = orxConfig_GetS32("Points");
                    orxConfig_PopSection();
                }
                orxLOG("Level 1 geladen");
                break;
        }

        scoreObject = orxObject_CreateFromConfig("ScoreTextObject");

        // Create the player
        player = new Player(orxObject_CreateFromConfig("PlayerObject"), 30, -30);

        orxCLOCK* clockTimer = orxClock_Create(0.9, orxCLOCK_TYPE_USER);
        clockObject = orxObject_CreateFromConfig("ClockObject");
        orxClock_Register(clockTimer, updateTimer, clockObject, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);   
    }

}


void startGameOver()
{
    if(gamestate == STATE_GAME_OVER)
    {
        // Create the viewport
        orxViewport_CreateFromConfig("Viewport");
        gameover = orxObject_CreateFromConfig("Gameover");
        orxLOG("Gameover geladen");
    }

}

void startWinScreen()
{
    if(gamestate == STATE_WIN)
    {
        // Create the viewport
        orxViewport_CreateFromConfig("Viewport");
        gameover = orxObject_CreateFromConfig("Winscreen");
        orxLOG("Win geladen");
    }

}

void startIntro()
{
    // Create the viewport
    orxViewport_CreateFromConfig("Viewport");
    if(gamestate == STATE_INTRO)
    {
        intro = orxObject_CreateFromConfig("Intro");
        orxLOG("Intro geladen");
    }
    else if(gamestate == STATE_INTRO2)
    {
        intro = orxObject_CreateFromConfig("Intro2");
        orxLOG("Intro2 geladen");
    }
    else if(gamestate == STATE_INTRO3)
    {
        intro = orxObject_CreateFromConfig("Intro3");
        orxLOG("Intro3 geladen");
    }
    else if(gamestate == STATE_INTRO4)
    {
        intro = orxObject_CreateFromConfig("Intro4");
        orxLOG("Intro4 geladen");
    }
    else if(gamestate == STATE_INTRO5)
    {
        intro = orxObject_CreateFromConfig("Intro5");
        orxLOG("Intro5 geladen");
    }
    else
    {}
}
        
void updateScore(int increase){
    score += increase;

    if (scoreObject) {
        orxCHAR formattedScore[3];
        orxString_Print(formattedScore, "%03d", score);

        orxObject_SetTextString(scoreObject, formattedScore);
    }
}

orxSTATUS orxFASTCALL PhysicsEventHandler(const orxEVENT *_pstEvent)
{
    if ((_pstEvent->eID == orxPHYSICS_EVENT_CONTACT_ADD) && (gamestate == STATE_PLAYING)) {
        orxOBJECT *pstRecipientObject, *pstSenderObject;

        /*
        // retrieve body part names from collision events
        orxPHYSICS_EVENT_PAYLOAD* payload = (orxPHYSICS_EVENT_PAYLOAD*)_pstEvent->pstPayload; 
        orxLOG("Recipient %s | Sender: %s", payload->zRecipientPartName, payload->zSenderPartName);
    
        pstSenderObject = orxOBJECT(_pstEvent->hSender);
        pstRecipientObject = orxOBJECT(_pstEvent->hRecipient);
        */
    
        orxSTRING senderObjectName = (orxSTRING)orxObject_GetName(pstSenderObject);
        orxSTRING recipientObjectName = (orxSTRING)orxObject_GetName(pstRecipientObject);
    
        if ((orxString_Compare(senderObjectName, "SheepObject") == 0) && (orxString_Compare(recipientObjectName, "SheepObject") == 0)){
                orxVECTOR stop = {0, 0, 0};
                orxObject_SetSpeed(pstSenderObject, &stop);
                orxObject_SetSpeed(pstRecipientObject, &stop);
        }
        if ((orxString_Compare(senderObjectName, "SheepObject") == 0) && (orxString_SearchString(recipientObjectName, "GateBodyObject"))){
            orxObject_SetLifeTime(pstSenderObject, orxFLOAT_0);
            updateScore(10);
        }

        if ((orxString_SearchString(senderObjectName, "GateBodyObject")) && (orxString_Compare(recipientObjectName, "SheepObject") == 0)){
            orxObject_SetLifeTime(pstRecipientObject, orxFLOAT_0);
            updateScore(10);
        }
    }
    return orxSTATUS_SUCCESS;
}


/** Init function, it is called when all orx's modules have been initialized
 */
orxSTATUS orxFASTCALL Init()
{   
    switch(gamestate)
    {
        case STATE_MENU: 
            startMenu();
            break;
        //case STATE_OPTIONS:
        case STATE_PLAYING: 
            startGame();
            break;
        case STATE_INTRO:
            startIntro();
            break;
        case STATE_GAME_OVER:
            startGameOver();
            break;
        //default:  
    }
    
    orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, PhysicsEventHandler);
    // Done!
    return orxSTATUS_SUCCESS;
}



void handleLevelInput()
{
    orxVECTOR player_movement = {0, 0, 0};
    if(orxInput_IsActive("GoLeft")){

        if(orxInput_HasNewStatus("GoLeft"))
        {
            orxObject_AddSound(level, "grass1");
        }
        
        player_movement = player->get_left();
        // player->move('L');
    }
    if(orxInput_IsActive("GoRight")){
        if(orxInput_HasNewStatus("GoRight"))
        {
            orxObject_AddSound(level, "grass1");
        }
        player_movement = player->get_right();
        // player->move('R');
    }
    if(orxInput_IsActive("GoUp")){
        if(orxInput_HasNewStatus("GoUp"))
        {
            orxObject_AddSound(level, "grass1");
        }
        player_movement = player->get_up();
        // player->move('U');
    }
    if(orxInput_IsActive("GoDown")){
        if(orxInput_HasNewStatus("GoDown"))
        {
            orxObject_AddSound(level, "grass1");
        }
        player_movement = player->get_down();
        // player->move('D');
    }

    
    orxObject_ApplyImpulse(player->get_object(), &player_movement, orxNULL);
}

void handleIntroInput()
{
    if (orxInput_IsActive("Space") && orxInput_HasNewStatus("Space"))
    {
        if(gamestate <10)
        {
            //Continue
            orxLOG("Spacebar!");
            orxObject_SetLifeTime(intro, orxFLOAT_0);
            gamestate++;
            startIntro();
        }
        else
        {
            orxLOG("Spacebar!");
            orxObject_SetLifeTime(intro, orxFLOAT_0);
            gamestate == STATE_PLAYING;
            startGame();    
        }    
    }
}

void handleMenuInput()
{
 //   orxLOG("Handle Menu Input");
    if (orxInput_IsActive("LeftClick") && orxInput_HasNewStatus("LeftClick"))
    {
        orxOBJECT *object = orxNULL;
     
        // Let's fetch the mouse's position
        orxVECTOR vPos;
        if(orxRender_GetWorldPosition(orxMouse_GetPosition(&vPos), orxNULL, &vPos) != orxNULL)
        { 
            // Let's see what's currently under the mouse
            //orxLOG("Irgendwas gefunden!!!");
            object = orxObject_Pick(&vPos, orxString_GetID("UI"));
            
            // Just click on things, crash when clicking background
            //orxLOG(orxObject_GetName(object));
            
        }

        if(object && (orxInput_HasBeenActivated("LeftClick")))
        {
            // He clicked...so let's start the game if it was the PlayButton
            if(orxString_Compare(orxObject_GetName(object),"StartObject") == 0)
            {
                //INSERT SOME CODE THAT STARTS YOUR GAME
                orxLOG("PlayButton geklcikt");
                orxObject_AddSound(menu, "StartSound");
                orxObject_SetLifeTime(menu, orxFLOAT_0);
                gamestate = STATE_INTRO;
                startIntro();
            }
            else if(orxString_Compare(orxObject_GetName(object),"GearObject") == 0)
            {
                orxLOG("Optionen geklickt");
                //gamestate = 2;
            }
            else if(orxString_Compare(orxObject_GetName(object),"SkullObject") == 0)
            {
                //DO OTHER STUFF FOR OTHER BUTTONS
                orxLOG("Exit geklickt");
                orxSTATUS eResult = orxSTATUS_SUCCESS;
                // Should quit?
                if(orxInput_IsActive("Quit"))
                {
                    orxObject_AddSound(menu, "ExitSound");
                    // Update result
                    eResult = orxSTATUS_FAILURE;
                }
            }
            else if(orxString_Compare(orxObject_GetName(object),"OtherButton") == 0)
            {
                //DO OTHER STUFF FOR OTHER BUTTONS
            }
        }   
    }

}

void handleGameoverInput()
{
    if (orxInput_IsActive("Space") && orxInput_HasNewStatus("Space"))
    {
        //Continue
        orxLOG("Spacebar!");
        orxObject_SetLifeTime(gameover, orxFLOAT_0);
        gamestate = STATE_MENU;
        startMenu();
        
    }
}

void checkOver(){
    if (time_left){
        if (time_left <= 0){
            
            orxObject_SetLifeTime(level, orxFLOAT_0);
            orxObject_SetLifeTime(player->get_object(), orxFLOAT_0);
            orxObject_SetLifeTime(scoreObject, orxFLOAT_0);
            orxObject_SetLifeTime(clockObject, orxFLOAT_0);
            
            if (score >= score_win){
                gamestate = STATE_WIN;
                startWinScreen();
            }
            else {
                gamestate = STATE_GAME_OVER;
                startGameOver();
            }

        }

        else if (time_left <= 10){
            orxVECTOR vec;
            vec.fX = 1.0;
            vec.fY = 0;
            vec.fZ = 0;
    
            orxCOLOR colour;
            colour.vRGB = vec;
            colour.fAlpha = orxFLOAT_1; //set alpha required to stop your object from becoming fully transparent.
            orxObject_SetColor(clockObject, &colour);
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
        //orxObject_AddSound(menu, "ExitSound");
        eResult = orxSTATUS_FAILURE;
    }
    
    //orxLOG("bin in run!");
    switch(gamestate)
    {
        case STATE_MENU: 
            handleMenuInput();
           // orxLOG("handle !");
            break;
        case STATE_PLAYING: 
            handleLevelInput();
            checkOver();
            break;
        case STATE_GAME_OVER:
            handleGameoverInput();
            break;
        case STATE_WIN:
            handleGameoverInput(); // WIn und Gameover haben gleichen Input / Logik
            break;
        case STATE_INTRO:
            handleIntroInput();
            break;
        //default: orxLOG("default"); 
    }

    //orxLOG("fertig mit run");
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
