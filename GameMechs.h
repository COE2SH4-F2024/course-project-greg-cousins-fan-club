#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>
#include <MacUILib.h>
#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;
        char** board; // this is the array of the board, newly declared.
        objPos* food;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); 
        GameMechs(const GameMechs &g);
        GameMechs& operator=(const GameMechs &g);
        //respecting rule of min 4

        //exit and lose flag declaration
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        char** getBoard() const;
        int getScore() const;
        //added these for food gen and adding score
        void incrementScore();
        void specialIncrement();
        void generateFood(objPosArrayList* blockOff);
        objPos* getFoodPos() const;
        
};

#endif