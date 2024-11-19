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
GameMechs tempptr1;
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
    playerptr = new Player(&tempptr1, 4,8,'@');
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
    //objPos currentPlayerPos = playerptr->getPlayerPos(); legacy code, delete
    
    map[playerptr->getPlayerPos().pos->y][playerptr->getPlayerPos().pos->x] = ' '; //before updating, make previous parts empty.
    playerptr->updatePlayerDir();
    playerptr->movePlayer();
    map[playerptr->getPlayerPos().pos->y][playerptr->getPlayerPos().pos->x] = playerptr->getPlayerPos().symbol;
    //wow this is insanely stupid but the logic works here, if you want to set the map equation the logic is here, feel free to test
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); //this is my logic for implementing the board right now. Swap it out when the gamemech implementation is done.
    MacUILib_printf("####################\n");
        for(int i=0; i < 8; i++){
            MacUILib_printf("#");
            for(int j = 0; j < 18; j++){
                MacUILib_printf("%c", map[i][j]);  
            }
            MacUILib_printf("#");
            MacUILib_printf("\n");
         }
    MacUILib_printf("#################### Your current direction is: %d", playerptr->getDir());//for debugging, just seeing what the diretion is to check if input works
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
