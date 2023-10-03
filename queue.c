#include "queue.h"

bool compareDeque(Deque *pxLeft, Deque *pxRight)
{
    // User define compare function
    return ((Character *)(pxLeft->pxData))->ch == ((Character *)(pxRight->pxData))->ch;
}

bool compareData(Data *pxLeft, Data *pxRight)
{
    // User define compare function
    return ((Character *)pxLeft)->ch == ((Character *)pxRight)->ch;
}

void displayData(Data *pxData)
{
    // User define display function
    printf("/-------------------\nCharacter: %c\n/-------------------\n", *(((Character *)pxData)->ch));
}