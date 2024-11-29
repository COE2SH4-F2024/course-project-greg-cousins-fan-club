#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        Player(GameMechs* thisGMRef, int x, int y, char symbol);//alternative constructor.
        ~Player();//destructor
        Player(const Player &p);
        Player& operator=(const Player &p);

        objPosArrayList* getPlayerPos() const; // pointer to snake object.      
        void updatePlayerDir();
        void movePlayer();
        void updateBoard();
        void clearBoard();//above functions explained in project.cpp
        Dir getDir() const;//get the direction as an enum
        bool checkFoodConsumption();
        bool checkSpecialFoodConsumption();
        void increasePlayerLength();//above 3 are used for snake growth

    private:
        objPosArrayList* playerPosList;       
        enum Dir myDir;
        GameMechs* mainGameMechsRef;
};

#endif