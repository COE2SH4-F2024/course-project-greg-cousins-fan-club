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

Player* playerptr;// pointers to access GameMechs and Player classes 
GameMechs* gamemech;


int main(void)
{

    Initialize();

    while(!gamemech->getExitFlagStatus())// will run snake game while getExitFlagStatus is false
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
    gamemech->generateFood(playerptr->getPlayerPos());
    exitFlag = false;
}

void GetInput(void)
{
    if(MacUILib_hasChar()){
        gamemech->setInput(MacUILib_getChar());
        if(gamemech->getInput() == 27){
            gamemech->setExitTrue();
        }
    }// if user hits esc, game ends
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
    
    if(playerptr->checkSpecialFoodConsumption()){
        playerptr->increasePlayerLength();
        gamemech->specialIncrement();
        gamemech->generateFood(playerptr->getPlayerPos());//if player hits special food,score goes up by 5, snake grows by 1, and new food is generated such that its not on the snake
    }
    else if(playerptr->checkFoodConsumption()){
        playerptr->increasePlayerLength();
        gamemech->incrementScore();
        gamemech->generateFood(playerptr->getPlayerPos());//same logic as above but score only goes up by 1
        
    }
    else{
        playerptr->movePlayer();
    }
    playerptr->updateBoard();
    
}

void DrawScreen(void)
{
    int i,j;
    MacUILib_clearScreen();
    if(gamemech->getLoseFlagStatus() == true){
        MacUILib_printf("\nGAME OVER!!! You hit yourself!");
        MacUILib_printf("\nYour final score is: %d, good job!",gamemech->getScore());//display message after player hits themselves
        MacUILib_Delay(5000000);//5 second delay
        gamemech->setExitTrue();//exit game
    }
    else{
        for(i=0; i < gamemech->getBoardSizeY(); i++){
            for(j = 0; j < gamemech->getBoardSizeX(); j++){
                    MacUILib_printf("%c", gamemech->getBoard()[i][j]);//print gameboard
                }
            }
        MacUILib_printf("\nCurrent Score: %d",gamemech->getScore());
        MacUILib_printf("\nPress Esc to quit the game"); // UI message displayed during game
    }
    
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 

    delete gamemech;
    delete playerptr;//freeing pointers allocated on heap
    MacUILib_uninit();
}
