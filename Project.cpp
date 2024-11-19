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
objPos object1(4,4,'@');
objPos object2;//used for testing, ignore for now
Player* playerptr;//these are arbitary pointers, delete these when we get to another iteration
GameMechs tempptr1;
char map[8][18] = {
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
    object2.setObjPos(6,1,'H');
    MacUILib_clearScreen();
    playerptr = new Player(&tempptr1);
    exitFlag = false;
}

void GetInput(void)
{
   if(MacUILib_hasChar()){
        tempptr1.setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    objPos currentPlayerPos = playerptr->getPlayerPos();
    map[currentPlayerPos.pos->x][currentPlayerPos.pos->y] = currentPlayerPos.symbol;
    playerptr->updatePlayerDir();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    MacUILib_printf("####################\n");
        for(int i=0; i < 8; i++){
            MacUILib_printf("#");
            for(int j = 0; j < 18; j++){
                MacUILib_printf("%c", map[i][j]);  
            }
            MacUILib_printf("#");
            MacUILib_printf("\n");
         }
    MacUILib_printf("#################### Your current direction is: %d", playerptr->getDir());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete[] playerptr;
    MacUILib_uninit();
}
