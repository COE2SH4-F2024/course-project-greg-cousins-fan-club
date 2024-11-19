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
//objPos object1(4,4,'@');
//objPos object2;//used for testing, ignore for now
Player* playerptr;//these are arbitary pointers, delete these when we get to another iteration
GameMechs* tempptr1;
char map[8][18] = {//temp map.
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
};

int main(void)
{

    Initialize();

    while(exitFlag == false)  
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
    //object2.setObjPos(6,1,'H'); more legacy code
    MacUILib_clearScreen();
    tempptr1 = new GameMechs();
    playerptr = new Player(tempptr1, 7,12,'@');
    
    exitFlag = false;
}

void GetInput(void)
{
   if(MacUILib_hasChar()){
        tempptr1->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    //objPos currentPlayerPos = playerptr->getPlayerPos(); legacy code, delete
    
    tempptr1->getBoard()[playerptr->getPlayerPos().pos->y][playerptr->getPlayerPos().pos->x] = ' '; //before updating, make previous parts empty.
    playerptr->updatePlayerDir();
    playerptr->movePlayer();
    tempptr1->getBoard()[playerptr->getPlayerPos().pos->y][playerptr->getPlayerPos().pos->x] = playerptr->getPlayerPos().symbol;//you should probably make a method for this
    //I should implement two methods that does this in player.
    //wow this is insanely stupid but the logic works here, if you want to set the map equation the logic is here, feel free to test
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); //this is my logic for implementing the board right now. Swap it out when the gamemech implementation is done.
        for(int i=0; i < tempptr1->getBoardSizeY(); i++){
            for(int j = 0; j < tempptr1->getBoardSizeX(); j++){
                MacUILib_printf("%c", tempptr1->getBoard()[i][j]);  
            }
         }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete[] playerptr;
    delete[] tempptr1;
    MacUILib_uninit();
}
