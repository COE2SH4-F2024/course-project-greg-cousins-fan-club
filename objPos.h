#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;        
        char symbol;

        objPos();
        objPos(int xPos, int yPos, char sym);
        ~objPos();
        objPos(const objPos &o);
        objPos& operator=(const objPos &o);
        // Respect the rule of six / minimum four

        //setters of object position
        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  

        //getters of object position
        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        bool isPosEqual(const objPos* refPos) const;
};

#endif