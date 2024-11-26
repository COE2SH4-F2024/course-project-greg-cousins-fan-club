#include "objPosArrayList.h"


objPosArrayList::objPosArrayList()//constructor, need to ask about array expansion.
{
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[arrayCapacity];
}
objPosArrayList::~objPosArrayList()
{
    delete[] aList;//deallocate space.
}
objPosArrayList::objPosArrayList(const objPosArrayList &o){
    this->arrayCapacity = ARRAY_MAX_CAP;
    this->listSize = o.listSize;
    this->aList = new objPos[this->arrayCapacity];
    for(int i = 0; i < listSize; i++){
        this->aList[i] = o.aList[i];
    }
}
objPosArrayList& objPosArrayList::operator=(const objPosArrayList &o){
    this->arrayCapacity = ARRAY_MAX_CAP;
    this->listSize = o.listSize;
    for(int i = 0; i < listSize; i++){
        this->aList[i] = o.aList[i];
    }
    return *this;
}
int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    /* //ask about expanding array sizes like in class
    if(listSize == arrayCapacity && arrayCapacity < ARRAY_MAX_CAP){ //expanding the array by making a new one
    //, deep copy and deleting the old heap memory, then setting the pointer to the new one.
        arrayCapacity += 50;
        objPos* temp = new objPos[arrayCapacity];
        for(int i = 0; i < listSize; i++){
            temp[i] = aList[i];
        }
        delete[] aList;
        aList = temp;
    }
    */
    if(listSize != arrayCapacity){//this starts counting from the back, and moving everything back 1. Snake logic.
        for(int i = listSize; i> 0; i--){
            aList[i] = aList[i-1];
        }
        aList[0] = thisPos;
        listSize += 1;
    }
}
    
    

void objPosArrayList::insertTail(objPos thisPos)
{
    /*
    if(listSize == arrayCapacity && arrayCapacity < ARRAY_MAX_CAP){ //expanding the array by making a new one
    //, deep copy and deleting the old heap memory, then setting the pointer to the new one.
        arrayCapacity += 50;
        objPos* temp = new objPos[arrayCapacity];
        for(int i = 0; i < listSize; i++){
            temp[i] = aList[i];
        }
        delete[] aList;
        aList = temp;
    }
    */
    if(listSize != arrayCapacity){
        aList[listSize] = thisPos;
        listSize += 1;
    }
    
}

void objPosArrayList::removeHead()
{
    if(listSize!=0){
        //aList[0].~objPos();
        listSize -= 1;
        for(int i = 0; i<listSize-1; i++){
            aList[i] = aList[i+1];
        }
    }
}

void objPosArrayList::removeTail()
{
    if(listSize!= 0){
        //aList[listSize-1].~objPos();
        listSize-=1;
    }//self explanatory, destroy the object at the end and decrease list size by one.
}

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