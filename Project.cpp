#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player* playerptr;//these are the temporary pointers used for testing features
GameMechs* gamemech;


int main(void)
{

    Initialize();

    while(!gamemech->getExitFlagStatus())  //code used to be while(exitFlag == false) before, idk if this is not allowed to be changed, if we have to then I'll revert it back to what is required
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    //allocation on heap for the two pointers used.
    gamemech = new GameMechs();
    playerptr = new Player(gamemech);
    
    exitFlag = false;
}

void GetInput(void)
{
   if(MacUILib_hasChar()){//changed this to the get_input logic, previous logic was faulty
        gamemech->setInput(MacUILib_getChar());
        if(gamemech->getInput() == 27){
        gamemech->setExitTrue();
   }
   }
}

void RunLogic(void)
{
    /*
    these four methods do the following: They clear the board(not the static portions of the border)
    updatePlayerDir contains the logic to check if a button has been pushed and to change the direction
    movePlayer does what is sounds - it holds the logic that moves the snake. In this case, the head tail logic is used.
    the updateBoard places all of the objects onto the board. Self explanatory
    */
    playerptr->clearBoard();
    playerptr->updatePlayerDir();
    playerptr->movePlayer();
    playerptr->updateBoard();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); //this is my logic for implementing the board right now. Swap it out when the gamemech implementation is done.
        for(int i=0; i < gamemech->getBoardSizeY(); i++){
            for(int j = 0; j < gamemech->getBoardSizeX(); j++){
                MacUILib_printf("%c", gamemech->getBoard()[i][j]);  
            }
         }
    MacUILib_printf("Your current direction is: %d", playerptr->getDir());//debugging message, feel free to delete.
    MacUILib_printf("\nPress Esc to quit the game"); // UI message, feel free to change it if u dont like the wording or wanna remodel the UI
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 

    delete gamemech;
    delete playerptr;
    MacUILib_uninit();
}
