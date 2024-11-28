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
        //hshsPlayer* gamer;
        objPos* food;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // is this one needed at all? Why or why not?
        //you should probably add the other two required rule of 4 functions here
        GameMechs(const GameMechs &g);
        GameMechs& operator=(const GameMechs &g);
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
        void incrementScore();
        void specialIncrement();
        void generateFood(objPosArrayList* blockOff);
        objPos* getFoodPos() const;
        
};

#endif