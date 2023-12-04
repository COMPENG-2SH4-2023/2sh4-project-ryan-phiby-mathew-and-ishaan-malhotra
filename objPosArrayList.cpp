#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;  // deallocates for each instance withing array
}

int objPosArrayList::getSize() // return size of list
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos) // check if list is already at maximum capacity, if so return
{
    if (sizeList == ARRAY_MAX_CAP) 
    {
        return;
    }
    
    for (int i = sizeList; i > 0; i--)
    {
        aList[i].setObjPos(aList[i - 1]);
    }

    aList[0].setObjPos(thisPos);
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos) // insert at tail of list
{
    if (sizeList == ARRAY_MAX_CAP)  // check if list is already at maximum capacity, if so return
    {
        return;
    }
    aList[sizeList++].setObjPos(thisPos);
}

void objPosArrayList::removeHead() // remove from head
{
    if (sizeList == 0) //check if list is already empty, if so return
    {
        return;
    }
    for (int i = 0; i < sizeList - 1; i++)
    {
        aList[i].setObjPos(aList[i + 1]);
    }
    sizeList--;
}

void objPosArrayList::removeTail() // remove from tail
{
    if (sizeList == 0) //check if list is already empty, if so return
    {
        return;
    }
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos) // returns head elemnt
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)  // return tail element
{
    returnPos.setObjPos(aList[sizeList - 1]); 
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (sizeList == 0 || index < 0 || index >= sizeList) // out of bounds index
    {
        return;
    }
    returnPos.setObjPos(aList[index]);
}