#ifndef DEQUE_H
#define DEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#define pdTRUE 1
#define pdFALSE 0

#define ERROR_CODE 65535
#define USER_DEFINE 0

#define status bool

// type declearation
typedef struct data Data;

typedef struct deque
{
    Data *pxData;
    struct deque *pxPre;
    struct deque *pxNext;
} Deque;

typedef struct miniDeque
{
    Deque *pxPre;
    Deque *pxNext;
} MiniDeque;

typedef void (*pvFuncHook)(void *);
typedef bool (*pbCompareDequeFunction)(Deque *, Deque *);
typedef bool (*pbCompareDataFunction)(Data *, Data *);
typedef void (*pvDisplayDataFunction)(Data *);

static pbCompareDequeFunction pbCompareDequeHook = NULL;
static pbCompareDataFunction pbCompareDataHook = NULL;
static pvDisplayDataFunction pvDisplayDataHook = NULL;

// function declearation
status pbDequeInit(Deque **pxList);
status pbGetElem(Deque **pxList, int iIndex, Data **pxData);
Deque *pxLocateElem(Deque **pxList, Data **pxData, bool reverse);
int pxLocateElemID(Deque **pxList, Data **pxData);
status pbDequeInsert(Deque **pxList, int iIndex, Data **pxData);
status pbDequeDelete(Deque **pxList, int iIndex, Data **pxData);
status pbDequeFree(Deque **pxList, int iIndex);
void pvDequeDisplay(Deque **pxList, bool reverse);
void pvDequeDisplayIndex(Deque **pxList, int iIndex);
size_t ulGetLength(Deque **pxList);
status pbDequeProp(void);

// external declearation
#if USER_DEFINE
extern pvFuncHook userInit;
#endif

extern bool compareDeque(Deque *l, Deque *r);
extern bool compareData(Data *l, Data *r);
extern void displayData(Data *data);

#endif