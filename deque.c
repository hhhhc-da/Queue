/*
 * deque.c & deque.h overview
 *
 * @ defined_type:
 * Deque & Data
 *
 * @ argument:
 * pxList is the end of the Deque
 * pdTRUE & pdFALSE to thread opeartion
 *
 * Edited by Mr.Zheng on 2023.9.11.
 */

#include "deque.h"
#include <string.h>

#define DISPLAY_MODE 0

///////////  USER  /////////////////////////
#include "queue.h"
status pbDequeProp(void)
{
    pbCompareDequeHook = (pbCompareDequeFunction)compareDeque;
    pbCompareDataHook = (pbCompareDataFunction)compareData;

    pvDisplayDataHook = (pvDisplayDataFunction)displayData;

#if DISPLAY_MODE
    printf("Hook prepare OK.\n");
#endif

    return pdTRUE;
}
////////////////////////////////////////////

// 'Deque' Initializer
status pbDequeInit(Deque **pxList)
{
    Deque *pxEnd = (Deque *)malloc(sizeof(MiniDeque));

    pxEnd->pxNext = pxEnd;
    pxEnd->pxPre = pxEnd;

    (*pxList) = pxEnd;

    (*pxList)->pxNext = pxEnd;
    (*pxList)->pxPre = pxEnd;

    pbDequeProp();

#if USER_DEFINE
    userInit();
#endif

    return pdTRUE;
}

// From 'Deque' get 'Data' (Double direction iterator)
status pbGetElem(Deque **pxList, int iIndex, Data **pxData)
{
    int iCount = 0;

    if (iIndex < 0)
    {
        size_t length = ulGetLength(pxList);
        iIndex = 0 - abs(iIndex) % length;

        Deque *pxTmp = *pxList;
        while (iCount > iIndex)
        {
            pxTmp = pxTmp->pxPre;
            --iCount;
        }
        // confirm type
        *pxData = (Data *)pxTmp->pxData;
    }
    else
    {
        size_t length = ulGetLength(pxList);
        iIndex = iIndex % length;

        Deque *pxTmp = (*pxList)->pxNext;
        while (iCount < iIndex)
        {
            pxTmp = pxTmp->pxNext;
            ++iCount;
        }
        // confirm type
        *pxData = (Data *)pxTmp->pxData;
    }

    return pdTRUE;
}

// From 'Data' get 'Deque' (Double direction iterator)
Deque *pxLocateElem(Deque **pxList, Data **pxData, bool reverse)
{
    Deque *pxEnd = *pxList;

    if (reverse == pdFALSE)
    {
        Deque *pxTmp = (*pxList)->pxNext;

        while (pxTmp != pxEnd)
        {
            if (!pbCompareDataHook((Data *)*pxData, (Data *)pxTmp->pxData))
                return pxTmp;
            pxTmp = pxTmp->pxNext;
        }
    }
    else
    {
        Deque *pxTmp = (*pxList)->pxPre;

        while (pxTmp != pxEnd)
        {
            if (!pbCompareDataHook((Data *)*pxData, (Data *)pxTmp->pxData))
                return pxTmp;
            pxTmp = pxTmp->pxPre;
        }
    }

    return NULL;
}

int pxLocateElemID(Deque **pxList, Data **pxData)
{
    Deque *pxEnd = *pxList;
    int iIndex = 0;
    Deque *pxTmp = (*pxList)->pxNext;

    while (pxTmp != pxEnd)
    {
        if (!pbCompareDataHook((Data *)*pxData, (Data *)pxTmp->pxData))
            return iIndex;
        pxTmp = pxTmp->pxNext;
        ++iIndex;
    }

    return ERROR_CODE;
}

// Insert 'Data' to 'Deque' (Double direction iterator)
status pbDequeInsert(Deque **pxList, int iIndex, Data **pxData)
{
    int iCount = 0;

#if DISPLAY_MODE
    pvDisplayDataHook(*pxData);
#endif

    Deque *pxNew = (Deque *)malloc(sizeof(Deque));

    pxNew->pxData = *pxData;

    Deque *pxTmp;
    int iIndex01 = 0;

    if (iIndex < 0)
    {
        size_t length = ulGetLength(pxList);
        pxTmp = (*pxList)->pxPre;

        if (length == 0)
            goto goto_label;
        iIndex01 = 0 - abs(iIndex) % length;

        for (; --iCount > iIndex01; pxTmp = pxTmp->pxPre)
            ;
    }
    else
    {
        size_t length = ulGetLength(pxList);
        pxTmp = (*pxList)->pxNext;

        if (length == 0)
            goto goto_label;
        iIndex01 = iIndex % length;

        for (; iCount++ < iIndex01; pxTmp = pxTmp->pxNext)
            ;
    }

goto_label:
    pxNew->pxPre = pxTmp;
    pxNew->pxNext = pxTmp->pxNext;

    pxTmp->pxNext->pxPre = pxNew;
    pxTmp->pxNext = pxNew;

#if DISPLAY_MODE
    printf("Insert OK.\n");
#endif

    return pdTRUE;
}

// Delete 'index' in 'Deque' (Double direction iterator)
status pbDequeDelete(Deque **pxList, int iIndex, Data **pxData)
{

    int iCount = 0;

    Deque *pxTmp;

    if (iIndex < 0)
    {
        size_t length = ulGetLength(pxList);
        iIndex = 0 - abs(iIndex) % length;

        pxTmp = (*pxList)->pxPre;

        for (; --iCount > iIndex; pxTmp = pxTmp->pxPre)
            ;
    }
    else
    {
        size_t length = ulGetLength(pxList);
        iIndex = iIndex % length;

        pxTmp = (*pxList)->pxNext;

        for (; iCount++ < iIndex; pxTmp = pxTmp->pxNext)
            ;
    }

    pxTmp->pxNext->pxPre = pxTmp->pxPre;
    pxTmp->pxPre->pxNext = pxTmp->pxNext;

    pxTmp->pxNext = NULL;
    pxTmp->pxPre = NULL;

    *pxData = pxTmp->pxData;

    return pdTRUE;
}

// Delete 'index' in 'Deque' (Double direction iterator)
status pbDequeFree(Deque **pxList, int iIndex)
{

    int iCount = 0;

    Deque *pxTmp;

    if (iIndex < 0)
    {
        size_t length = ulGetLength(pxList);
        iIndex = 0 - abs(iIndex) % length;

        pxTmp = (*pxList)->pxPre;

        for (; --iCount > iIndex; pxTmp = pxTmp->pxPre)
            ;
    }
    else
    {
        size_t length = ulGetLength(pxList);
        iIndex = iIndex % length;

        pxTmp = (*pxList)->pxNext;

        for (; iCount++ < iIndex; pxTmp = pxTmp->pxNext)
            ;
    }

    pxTmp->pxNext->pxPre = pxTmp->pxPre;
    pxTmp->pxPre->pxNext = pxTmp->pxNext;

    pxTmp->pxNext = NULL;
    pxTmp->pxPre = NULL;

    free(pxTmp);

    return pdTRUE;
}

// Display 'Data' in 'Deque' (Double direction iterator)
void pvDequeDisplay(Deque **pxList, bool reverse)
{
    Deque *pxEnd = *pxList;

    if (reverse == pdFALSE)
    {
        Deque *pxTmp = (*pxList)->pxNext;
        while (pxTmp != pxEnd)
        {
            pvDisplayDataHook((Data *)(pxTmp->pxData));
            pxTmp = pxTmp->pxNext;
        }
    }
    else
    {
        Deque *pxTmp = (*pxList)->pxPre;
        while (pxTmp != pxEnd)
        {
            pvDisplayDataHook((Data *)(pxTmp->pxData));
            pxTmp = pxTmp->pxPre;
        }
    }
}

void pvDequeDisplayIndex(Deque **pxList, int iIndex)
{
    int iCount = 0;
    Deque *pxTmp;

    if (iIndex < 0)
    {
        unsigned length = ulGetLength(pxList);
        iIndex = 0 - abs(iIndex) % length;

        pxTmp = (*pxList)->pxPre;

        for (; --iCount > iIndex; pxTmp = pxTmp->pxPre)
            ;
    }
    else
    {
        size_t length = ulGetLength(pxList);
        iIndex = iIndex % length;

        pxTmp = (*pxList)->pxNext;

        for (; iCount++ < iIndex; pxTmp = pxTmp->pxNext)
            ;
    }

    pvDisplayDataHook(pxTmp->pxData);
}

size_t ulGetLength(Deque **pxList)
{
    Deque *pxEnd = (Deque *)*pxList, *pxTmp = (*pxList)->pxNext;
    size_t ulCount = 0;

    while (pxTmp != pxEnd)
    {
        ++ulCount;
        pxTmp = pxTmp->pxNext;
    }

    return ulCount;
}