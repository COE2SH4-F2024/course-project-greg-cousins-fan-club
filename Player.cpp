#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(4,8,'*');

    // more actions to be included
}

Player::Player(GameMechs* thisGMRef, int y, int x, char symbol){//alternative player constructor, more explicit.
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(y,x, symbol);
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
    switch (myDir){
        case LEFT: //change to the game mech ref, because the borders can vary in this case. This only works for the ppa board!!!
            if (playerPos.pos->x == 0){
                playerPos.pos->x = 17;
            }
            else{
                playerPos.pos->x -= 1;
            }
            break;
        case RIGHT:
            if (playerPos.pos->x == 17){
                playerPos.pos->x = 0;
            }
            else{
                playerPos.pos->x += 1;
            }
            break;
        case UP:
            if (playerPos.pos->y == 0){
                playerPos.pos->y = 7;
            }
            else{
                playerPos.pos->y -= 1;
            }
        break;
        case DOWN:
            if (playerPos.pos->y == 7){
                playerPos.pos->y = 0;
            }
            else{
                playerPos.pos->y += 1;
            }
        break;
        default:
            break;
    }
    // PPA3 Finite State Machine logic
}

// More methods to be added