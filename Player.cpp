#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList;//making the new arrayList, and setting the head to the middle.
    playerPosList->insertHead(objPos(12,7,'*'));

    // more actions to be included
}

Player::Player(GameMechs* thisGMRef, int y, int x, char symbol){//alternative player constructor, more explicit.
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList;
    playerPosList->insertHead(objPos(y, x, symbol));
}

Player::~Player()
{
    delete[] playerPosList;
    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos() const
{
    objPosArrayList* returnPos = playerPosList;//idk why it's return by value here
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
    objPos currentHeadPos = playerPosList->getHeadElement();
    int currentHeadx = currentHeadPos.pos->x;
    int currentHeadY = currentHeadPos.pos->y;
    char currentHeadsym = currentHeadPos.symbol;
    switch (myDir){//this is makeshift, I just want to see if the logic works here. 
        case LEFT: //change to the game mech ref, because the borders can vary in this case. This only works for the ppa board!!!
            if (currentHeadx == 1){
                playerPosList->insertHead(objPos(mainGameMechsRef->getBoardSizeX()-3,currentHeadY,currentHeadsym));
                playerPosList->removeTail();
            }
            else{
                currentHeadx -= 1;
                playerPosList->insertHead(objPos(currentHeadx,currentHeadY,currentHeadsym));
                playerPosList->removeTail();
            }
            break;
        case RIGHT:
            if (currentHeadx == mainGameMechsRef->getBoardSizeX()-3){
                playerPosList->insertHead(objPos(1,currentHeadY,currentHeadsym));
                playerPosList->removeTail();
            }
            else{
                currentHeadx += 1;
                playerPosList->insertHead(objPos(currentHeadx,currentHeadY,currentHeadsym));
                playerPosList->removeTail();
            }
            break;
        case UP:
            if (currentHeadY == 1){
                playerPosList->insertHead(objPos(currentHeadx, mainGameMechsRef->getBoardSizeY()-2,currentHeadsym));
                playerPosList->removeTail();
            }
            else{
                currentHeadY -= 1;
                playerPosList->insertHead(objPos(currentHeadx, currentHeadY,currentHeadsym));
                playerPosList->removeTail();
            }
        break;
        case DOWN:
            if (currentHeadY == mainGameMechsRef->getBoardSizeY()-2){
                playerPosList->insertHead(objPos(currentHeadx, 1, currentHeadsym));
                playerPosList->removeTail();
            }
            else{
                currentHeadY += 1;
                playerPosList->insertHead(objPos(currentHeadx, currentHeadY,currentHeadsym));
                playerPosList->removeTail();
            }
        break;
        default:
            break;
    }
    // PPA3 Finite State Machine logic
}

// More methods to be added