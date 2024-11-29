#include "GameMechs.h"
#include <iostream>
using namespace std;

#include <stdlib.h>
#include <time.h>
//yo suchir, I think I'm gonna start working on the actual moving parts of the snake. I'll just have it start moving around, but the food logic
//and the end game logic, etc. are up you to implement. Feel free to go to my files and link up player, with food, etc.
GameMechs::GameMechs()
{//I slightly did this part so I could do some of my part, because I need the input part done. Feel free to change anything.
    input = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;
    food = new objPos[5];
    //food.setObjPos (5,5,'o');   dr.chen said to have this line but we don't really need it
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
{//YO SUCHIR IMPLEMENT THIS PLEASE!!! THIS NEEDS TO IMPLEMENTED!!!!!!!
    input = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;


    //food.setObjPos (5,5,'o');
    exitFlag = false;
    loseFlag = false;// not gonna use this for a while, but I just initialized it for now
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    for(int i = 0; i < boardSizeY; i++){
        delete[] board[i];
    }
    delete[] board;
    delete[] food;
}
GameMechs::GameMechs(const GameMechs &g){
    this->input = g.input;
    this->boardSizeX = g.boardSizeX;
    this->boardSizeY = g.boardSizeY;
    this->score = g.score;
    this->exitFlag = g.exitFlag;
    this->loseFlag = g.loseFlag;
    this->board = new char*[this->boardSizeY];
    for(int i = 0; i < this->boardSizeY; i++){
        board[i] = new char[this->boardSizeX];
    }
    for(int i = 1; i<this->boardSizeY; i++){
        for(int j = 1; j<this->boardSizeX; j++){
            this->board[i][j] = g.board[i][j];//deep copy
        }
    }
}
GameMechs& GameMechs::operator=(const GameMechs &g){
    if (this != &g){
        this->input = g.input;
        this->boardSizeX = g.boardSizeX;
        this->boardSizeY = g.boardSizeY;
        this->score = g.score;
        this->exitFlag = g.exitFlag;
        this->loseFlag = g.loseFlag;
        for(int i = 1; i<this->boardSizeY; i++){
            for(int j = 1; j<this->boardSizeX; j++){
                this->board[i][j] = g.board[i][j];//deep copy
            }
        }
    }
    return *this;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
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
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
void GameMechs::generateFood(objPosArrayList* blockOff)
{
    int unique = 0; 
    int x, y;
    int size = blockOff->getSize();
    srand(time(NULL)); // Seed the RNG
        // Generate random coordinates avoiding borders
        for(int i = 0; i < 5; i++){//for each element in food
            unique = 0;
            while (unique == 0) {
                unique = 1; // Assume unique initially
                x = rand() % (boardSizeX - 3) + 1;
                y = rand() % (boardSizeY - 3) + 1;
                
                // Check against snake's body
                for (int j = 0; j < size; j++) {
                    objPos snake = blockOff->getElement(j);
                    if (snake.pos->x == x && snake.pos->y == y) {
                        unique = 0; // Not unique
                        break;
                    }
                }
            }
                food[i].pos->x = x;
                food[i].pos->y = y;
                if(i == 4){
                    food[i].symbol = '^';
                }
                else{
                    food[i].symbol = 'o';
                }        
        }
}

objPos* GameMechs::getFoodPos() const
{
    return food;
}
void GameMechs::specialIncrement(){
    score += 5;
}
