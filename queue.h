#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "deque.h"

#define OK 0
#define ERR 1

typedef struct MyData
{
    char *ch;
} Character;

typedef Character Elemtype;

bool compareDeque(Deque *l, Deque *r);
bool compareData(Data *l, Data *r);
void displayData(Data *data);

typedef struct
{
    Deque *lst;
    unsigned int count;
} Queue;

// bool InitQueue(Queue *pxQueue)
#define InitQueue(pxQueue)                           \
    {                                                \
        (*((Queue **)pxQueue))->count = 0;           \
        pbDequeInit(&((*((Queue **)pxQueue))->lst)); \
    }

// bool EmptyQueue(Queue *pxQueue)
#define EmptyQueue(pxQueue) ((Queue **)pxQueue)->count == 0

// bool EnQueue(Queue *pxQueue, Character *Element)
#define EnQueue(pxQueue, Element)                                            \
    {                                                                        \
        pbDequeInsert(&((*((Queue **)pxQueue))->lst), -1, (Data **)Element); \
        (*((Queue **)pxQueue))->count++;                                     \
    }

// bool DeQueue(Queue *pxQueue, Character *Element)
#define DeQueue(pxQueue, Element)                                       \
    {                                                                   \
        pbGetElem(&((*((Queue **)pxQueue))->lst), 0, (Data **)Element); \
        pbDequeFree(&((*((Queue **)pxQueue))->lst), 0);                 \
        (*((Queue **)pxQueue))->count--;                                \
    }

#endif