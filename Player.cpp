#include "Player.h"

// Constructor initializes the Player object with a reference to the game mechanics,
// creates a new objPosArrayList for storing the snake's position
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList;//making the new arrayList, and setting the head to the middle.
    playerPosList->insertHead(objPos(12,7,'*'));
    playerPosList->insertTail(objPos(12,8,'*'));
    playerPosList->insertTail(objPos(12,9,'*'));
    playerPosList->insertTail(objPos(12,10,'*'));
    playerPosList->insertTail(objPos(11,10,'*'));//creates snake that is 5 units long
}

Player::Player(GameMechs* thisGMRef, int y, int x, char symbol){//alternative player constructor, allows explicitly setting the snake's initial position
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

// Copy constructor 
Player::Player(const Player &p){
    this->mainGameMechsRef = p.mainGameMechsRef;
    this->myDir = p.myDir;
    this->playerPosList = new objPosArrayList;// Allocate new memory for position list.
    this->playerPosList = p.playerPosList;

// Assignment operator 
}
Player& Player::operator=(const Player &p){
    if(this != &p){
        this->mainGameMechsRef = p.mainGameMechsRef;
        this->myDir = p.myDir;
        this->playerPosList = p.playerPosList;
    }
    return *this;
}


objPosArrayList* Player::getPlayerPos() const
{
    objPosArrayList* returnPos = playerPosList;//return by pointer getting the position so you can modify the values.
    return returnPos;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    switch(input)
        {                      
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

// Returns the current direction of the player
Player::Dir Player::getDir() const{
    return myDir;
}



void Player::movePlayer()
{
    objPos currentHeadPos = playerPosList->getHeadElement();// Get the head position.
    //setting the current position of x and y and the symbol as shorter varaible names. Stores the x,y, and symbol of the head.
    int currentHeadx = currentHeadPos.pos->x;// Extract x-coordinate
    int currentHeadY = currentHeadPos.pos->y;// Extract y-coordinate.
    char currentHeadsym = currentHeadPos.symbol;// Extract symbol.
    switch (myDir){ 
        case LEFT:
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
    }//above is the wraparound logic, if the snake head reaches one of the extremities while going in a specific direction, its head will move to the other extremity
    //everytime snake moves, the head is added to one space ahead and the tail is removed


    objPos head = playerPosList->getHeadElement().getObjPos();
    // Check for self-collision with the body
    for (int i = 1; i < playerPosList->getSize(); i++) { // Loop through the body
        objPos bodyPart = playerPosList->getElement(i);
        if (head.pos->x == bodyPart.pos->x && head.pos->y == bodyPart.pos->y) {
            // Collision detected, set flags
            mainGameMechsRef->setLoseFlag();
            //mainGameMechsRef->setExitTrue();
            return; // Exit the function to avoid further movement
        }
    }

}

void Player::clearBoard(){
    for(int i = 1; i < mainGameMechsRef->getBoardSizeY()-1; i++){
        for(int j = 1; j< mainGameMechsRef->getBoardSizeX()-2; j++){
            mainGameMechsRef->getBoard()[i][j] = ' ';//set everything back to space, except the border
        }
    }
}

// Updates the board with the player's and food positions.
void Player::updateBoard(){
    objPos* foodPos = mainGameMechsRef->getFoodPos();
    for(int i = 0; i < 5; i++){
        int x = foodPos[i].pos->x;
        int y = foodPos[i].pos->y;
        mainGameMechsRef->getBoard()[y][x] = foodPos[i].symbol;
    }
    for(int i = 0; i< playerPosList->getSize(); i++){
        int x = playerPosList->getElement(i).pos->x;
        int y = playerPosList->getElement(i).pos->y;
        char sym = playerPosList->getElement(i).symbol;
        mainGameMechsRef->getBoard()[y][x] = sym;
        //place all of the objects onto the board.
    }
    
}


// Checks if the player has consumed regular food.
bool Player::checkFoodConsumption(){
    objPos* foodPos = mainGameMechsRef->getFoodPos();
    objPos headElement = playerPosList->getHeadElement();
    for(int i = 0; i < 5; i++){
        if(foodPos[i].pos->x == headElement.pos->x && foodPos[i].pos->y == headElement.pos->y){
            return true;//checks if head pos is the same as food pos
        }
    }
    return false;
}

//same logic for reg food
bool Player::checkSpecialFoodConsumption(){
    objPos* foodPos = mainGameMechsRef->getFoodPos();
    objPos headElement = playerPosList->getHeadElement();
    for(int i = 0; i < 5; i++){
        if(foodPos[i].pos->x == headElement.pos->x && foodPos[i].pos->y == headElement.pos->y && foodPos[i].symbol == '^'){
            return true;
        }
    }
    return false;
}



void Player::increasePlayerLength(){
    objPos currentHeadPos = playerPosList->getHeadElement();
    //setting the current position of x and y and the symbol as shorter varaible names. Stores the x,y, and symbol of the head.
    int currentHeadx = currentHeadPos.pos->x;
    int currentHeadY = currentHeadPos.pos->y;
    char currentHeadsym = currentHeadPos.symbol;
    switch (myDir){ 
        case LEFT: //similar logic to movePlayer(), however when food pos is the same as headPos, tail is not removed
            if (currentHeadx == 1){
                playerPosList->insertHead(objPos(mainGameMechsRef->getBoardSizeX()-3,currentHeadY,currentHeadsym));
            }
            else{
                currentHeadx -= 1;
                playerPosList->insertHead(objPos(currentHeadx,currentHeadY,currentHeadsym));
            }
            break;
        case RIGHT:
            if (currentHeadx == mainGameMechsRef->getBoardSizeX()-3){
                playerPosList->insertHead(objPos(1,currentHeadY,currentHeadsym));
            }
            else{
                currentHeadx += 1;
                playerPosList->insertHead(objPos(currentHeadx,currentHeadY,currentHeadsym));
            }
            break;
        case UP:
            if (currentHeadY == 1){
                playerPosList->insertHead(objPos(currentHeadx, mainGameMechsRef->getBoardSizeY()-2,currentHeadsym));
            }
            else{
                currentHeadY -= 1;
                playerPosList->insertHead(objPos(currentHeadx, currentHeadY,currentHeadsym));
            }
            break;
        case DOWN:
            if (currentHeadY == mainGameMechsRef->getBoardSizeY()-2){
                playerPosList->insertHead(objPos(currentHeadx, 1, currentHeadsym));
                
            }
            else{
                currentHeadY += 1;
                playerPosList->insertHead(objPos(currentHeadx, currentHeadY,currentHeadsym));
                
            }
            break;
        default:
            break;
    }
}

