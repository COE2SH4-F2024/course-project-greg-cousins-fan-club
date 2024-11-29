#include "objPos.h"


// Default constructor: Initializes the object with default values
objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}


// Parameterized constructor: Initializes the object with specific values
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}


//destructor
objPos::~objPos(){
    delete pos;
}


// Copy constructor
objPos::objPos(const objPos &o){
    this->symbol = o.symbol;
    this->pos = new Pos;
    this->pos->x = o.pos->x;
    this->pos->y = o.pos->y;
}


// Assignment operator
objPos& objPos::operator=(const objPos &o){
    if(this != &o){
        this->symbol = o.symbol;//check
        this->symbol = o.symbol;
        this->pos->x = o.pos->x;
        this->pos->y = o.pos->y;
    }
    return *this;
}
// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule




// Sets the position and symbol based on another objPos object
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}


// Sets the position and symbol using specific values
void objPos::setObjPos(int yPos, int xPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}


//getters for objpos and for symbol of object
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}


// Compares the position of the current object with another objPos object
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}



// Returns the symbol if the position matches another objPos object. Otherwise, returns 0
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
