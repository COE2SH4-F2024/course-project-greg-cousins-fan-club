#include "objPosArrayList.h"

// Constructor: Initializes the array list with the maximum capacity and sets the size to zero
objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[arrayCapacity];
}


objPosArrayList::~objPosArrayList()
{
    delete[] aList;//deallocate space.
}

// Copy constructor: Creates a deep copy of another objPosArrayList
objPosArrayList::objPosArrayList(const objPosArrayList &o){
    this->arrayCapacity = ARRAY_MAX_CAP;
    this->listSize = o.listSize;
    this->aList = new objPos[this->arrayCapacity];
    for(int i = 0; i < listSize; i++){
        this->aList[i] = o.aList[i];
    }
}


// Assignment operator: Creates a deep copy of another objPosArrayList
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &o){
    if(this != &o){
        this->arrayCapacity = ARRAY_MAX_CAP;
        this->listSize = o.listSize;
        for(int i = 0; i < listSize; i++){
            this->aList[i] = o.aList[i];
        }
    }
    return *this;
}


//return size of list 
int objPosArrayList::getSize() const
{
    return listSize;
}


// Inserts an element at the head of the list, shifting existing elements to the right
void objPosArrayList::insertHead(objPos thisPos)
{
    
    if(listSize != arrayCapacity){
        for(int i = listSize; i> 0; i--){
            aList[i] = aList[i-1];
        }
        aList[0] = thisPos;
        listSize += 1;
    }
}
    
    

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize != arrayCapacity){
        aList[listSize] = thisPos;
        listSize += 1;
    }//add 1 unit to end of snake
    
}

void objPosArrayList::removeHead()
{
    if(listSize!=0){
        listSize -= 1;
        for(int i = 0; i<listSize-1; i++){
            aList[i] = aList[i+1];
        }
    }//self explanitory 
}

void objPosArrayList::removeTail()
{
    if(listSize!= 0){
        listSize-=1;
    }//self explanatory, destroy the object at the end and decrease list size by one.
}


//self explanitory getters
objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}