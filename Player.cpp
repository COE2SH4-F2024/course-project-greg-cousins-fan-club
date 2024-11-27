#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList;//making the new arrayList, and setting the head to the middle.
    playerPosList->insertHead(objPos(12,7,'*'));
    playerPosList->insertTail(objPos(12,8,'*'));
    playerPosList->insertTail(objPos(12,9,'*'));
    playerPosList->insertTail(objPos(12,10,'*'));
    playerPosList->insertTail(objPos(11,10,'*'));
    //right now, the objects here are used for debugging and seeing if the program works. Will rework at the end.
}

Player::Player(GameMechs* thisGMRef, int y, int x, char symbol){//alternative player constructor, more explicit.
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList;
    playerPosList->insertHead(objPos(y, x, symbol));
}

Player::~Player()
{
    delete playerPosList;
    // delete any heap members here
}
Player::Player(const Player &p){
    this->mainGameMechsRef = p.mainGameMechsRef;
    this->myDir = p.myDir;
    this->playerPosList = new objPosArrayList;
    this->playerPosList = p.playerPosList;
}
Player& Player::operator=(const Player &p){
    this->mainGameMechsRef = p.mainGameMechsRef;
    this->myDir = p.myDir;
    this->playerPosList = p.playerPosList;
    return *this;
}
objPosArrayList* Player::getPlayerPos() const
{
    objPosArrayList* returnPos = playerPosList;//return by pointer getting the position so you can modify the values.
    return returnPos;
}

void Player::updatePlayerDir()
{ //basically copied pasted the ppa2 code here
    char input = mainGameMechsRef->getInput();
    switch(input)
        {                      
            //case ' ':  // exit
                //mainGameMechsRef->setExitTrue();
                //break;
                /*
            case 27:
                mainGameMechsRef->setExitTrue();//will exit game when Esc is hit
                break;
                */
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
}
Player::Dir Player::getDir() const{//this is really messed up, because you need to specify that the data type you are returning is part of the player class.
    return myDir;
}
void Player::movePlayer()
{
    objPos currentHeadPos = playerPosList->getHeadElement();
    //setting the current position of x and y and the symbol as shorter varaible names. Stores the x,y, and symbol of the head.
    int currentHeadx = currentHeadPos.pos->x;
    int currentHeadY = currentHeadPos.pos->y;
    char currentHeadsym = currentHeadPos.symbol;
    switch (myDir){ 
        case LEFT: //this logic shouldn't be touched. It works perfectly fine, and it implements the wraparound logic.
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
}

void Player::clearBoard(){
    for(int i = 1; i < mainGameMechsRef->getBoardSizeY()-1; i++){
        for(int j = 1; j< mainGameMechsRef->getBoardSizeX()-2; j++){
            mainGameMechsRef->getBoard()[i][j] = ' ';//set everything back to space, except the border
        }
    }
}
void Player::updateBoard(){
    
    for(int i = 0; i< playerPosList->getSize(); i++){
        int x = playerPosList->getElement(i).pos->x;
        int y = playerPosList->getElement(i).pos->y;
        char sym = playerPosList->getElement(i).symbol;
        mainGameMechsRef->getBoard()[y][x] = sym;
        //place all of the objects onto the board.
    }
}