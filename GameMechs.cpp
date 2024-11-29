#include "GameMechs.h"
#include <iostream>
using namespace std;

#include <stdlib.h>// For rand() and srand()
#include <time.h>

GameMechs::GameMechs()
{
    input = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;
    food = new objPos[5];// Allocate memory for 5 food items
    exitFlag = false;
    loseFlag = false;//important to set exit and lose flag as false initially for program to run
    board = new char*[boardSizeY];// Dynamically allocate memory for the board rows
    
    // Allocate memory for each column in the board
    for(int i = 0; i < boardSizeY; i++){
        board[i] = new char[boardSizeX];
    }

    for(int i = 0; i < boardSizeY; i++){//setting up the borders of the board.
        board[i][0] = '#';
        board[i][boardSizeX-2] = '#';
        board[i][boardSizeX-1] = '\n';
    }

    for(int j = 0; j<boardSizeX-1; j++){
        board[0][j] = '#';
    }
    

    for(int j = 0; j<boardSizeX-1; j++){
        board[boardSizeY-1][j] = '#';
    }//again, more border stuff above.

    // Fill the rest of the board (non-border areas) with spaces
    for(int i = 1; i<boardSizeY-1; i++){
        for(int j = 1; j<boardSizeX-2; j++){
            board[i][j] = ' ';//this sets everything that's not the border to a space. 
        }
    }
}

//constructor: Initializes the game mechanics with custom board dimensions
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;


    exitFlag = false;
    loseFlag = false;
}


//destructor
GameMechs::~GameMechs()
{
    for(int i = 0; i < boardSizeY; i++){
        delete[] board[i];
    }
    delete[] board;
    delete[] food;
}


// Copy constructor
GameMechs::GameMechs(const GameMechs &g){
    this->input = g.input;
    this->boardSizeX = g.boardSizeX;
    this->boardSizeY = g.boardSizeY;
    this->score = g.score;
    this->exitFlag = g.exitFlag;
    this->loseFlag = g.loseFlag;
    this->board = new char*[this->boardSizeY];

    // Allocate memory for each row and copy board content
    for(int i = 0; i < this->boardSizeY; i++){
        board[i] = new char[this->boardSizeX];
    }


    for(int i = 1; i<this->boardSizeY; i++){
        for(int j = 1; j<this->boardSizeX; j++){
            this->board[i][j] = g.board[i][j];//deep copy
        }
    }
}


// Assignment operator
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

//accessor methods
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


//regular food score increase
void GameMechs::incrementScore()
{
    score++;
}

//more accessors
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


// Generates random food positions while avoiding snake positions
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
                // Set food position and symbol
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
// Accessor for the food positions
objPos* GameMechs::getFoodPos() const
{
    return food;
}

// Special score increment for special food
void GameMechs::specialIncrement(){
    score += 5;
}
