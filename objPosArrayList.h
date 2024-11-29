#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200// Maximum capacity of the array

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;  // Pointer to dynamically allocated array of objPos objects
        int listSize;
        int arrayCapacity;

    public:
        objPosArrayList();//initialize list constructor
        ~objPosArrayList();//destructor
        objPosArrayList(const objPosArrayList &o);//copy constructor
        objPosArrayList& operator=(const objPosArrayList &o);//Assignment operator
        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        //getters
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
};

#endif