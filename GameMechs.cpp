#include "GameMechs.h"
#include <iostream>
using namespace std;
//yo suchir, I think I'm gonna start working on the actual moving parts of the snake. I'll just have it start moving around, but the food logic
//and the end game logic, etc. are up you to implement. Feel free to go to my files and link up player, with food, etc.
GameMechs::GameMechs()
{//I slightly did this part so I could do some of my part, because I need the input part done. Feel free to change anything.
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;// not gonna use this for a while, but I just initialized it for now
    board = new char*[boardSizeY];//I think we need to DMA here, because we want to have the array sizes be variable. We can't exactly do dynamic arrays convetionally
    //without using DMA, and I want to implement the board 
    //border setup below. Feel free to check.
    for(int i = 0; i < boardSizeY; i++){
        board[i] = new char[boardSizeX];
    }
    for(int i = 0; i < boardSizeY; i++){//setting up the borders of the board.
        board[i][0] = '#';
        board[i][boardSizeX-2] = '#';
        board[i][boardSizeX-1] = '\n';
    }
    for(int j = 0; j<boardSizeX-1; j++){//I basically made everything variable, so everything that's being printed is the board
        board[0][j] = '#';
    }
    /*
    that includes the newlines and the border, I kinda wanted to implement everything here.
    */
    for(int j = 0; j<boardSizeX-1; j++){
        board[boardSizeY-1][j] = '#';
    }//again, more border stuff above.
    for(int i = 1; i<boardSizeY-1; i++){
        for(int j = 1; j<boardSizeX-2; j++){
            board[i][j] = ' ';//this sets everything that's not the border to a space. 
        }
    }
}

GameMechs::GameMechs(int boardX, int boardY)
{
    
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    for(int i = 0; i < boardSizeY; i++){
        delete[] board[i];
    }
    delete[] board;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{

}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{

}

void GameMechs::incrementScore()
{
    
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}
char** GameMechs::getBoard() const{
    return board;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{

}

// More methods should be added here
