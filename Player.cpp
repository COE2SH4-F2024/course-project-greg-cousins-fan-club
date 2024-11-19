#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(4,8,'*');

    // more actions to be included
}

Player::Player(GameMechs* thisGMRef, int x, int y, char symbol){
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(x,y, symbol);
}

Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    objPos returnPos = playerPos.getObjPos();//idk why it's return by value here
    return returnPos;
}

void Player::updatePlayerDir()
{ //basically copied pasted the ppa2 code here
    char input = mainGameMechsRef->getInput();
    switch(input)
        {                      
            case ' ':  // exit
                mainGameMechsRef->setExitTrue();
                break;
            case 'w':
            case 'W'://wasd movement, same as ppa2
                if (myDir == LEFT || myDir == RIGHT || myDir == STOP){
                    myDir = UP;
                }
                break;
            case 'a':
            case 'A':
                if (myDir == UP || myDir == DOWN || myDir == STOP){
                    myDir = LEFT;
                }
                break;
            case 's':
            case 'S':
                if (myDir == LEFT || myDir == RIGHT || myDir == STOP){
                    myDir = DOWN;
                }
                break;
            case 'd':
            case 'D':
                if (myDir == UP || myDir == DOWN || myDir == STOP){
                    myDir = RIGHT;
                }
                break;
            default:
                break;
        }
        // PPA3 input processing logic          
}
Player::Dir Player::getDir() const{//this is really messed up, because you need to specify that the data type you are returning is part of the player class.
    return myDir;
}
void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added