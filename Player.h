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
        ~Player();
        Player(const Player &p);
        Player& operator=(const Player &p);
        //need to implement these as well, the copy and copy assignment ops.

        objPosArrayList* getPlayerPos() const; // pointer to snake object.      
        void updatePlayerDir();//these 4 functions are explained more in the main project file.
        void movePlayer();
        void updateBoard();
        void clearBoard();
        Dir getDir() const;//get the direction as an enum(not really required, mostly used for debugging)
        bool checkFoodConsumption();
        void increasePlayerLength();

    private:
        objPosArrayList* playerPosList;       
        enum Dir myDir;
        GameMechs* mainGameMechsRef;
};

#endif