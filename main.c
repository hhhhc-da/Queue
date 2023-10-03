#include "main.h"

int main(void)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    char *strData = "China I Love You";

    unsigned strLen = strlen(strData);
    Character *setCh[strLen];

    unsigned i = 0;
    for (; i < strLen; ++i)
    {
        setCh[i] = (Character *)malloc(sizeof(Character));
        (setCh[i])->ch = (char *)malloc(sizeof(char));
    }

    for (i = 0; i < strLen; ++i)
    {
        char c = (char)(*(strData + i));
        *((setCh[i])->ch) = c;
    }

    InitQueue(&queue);

    for (i = 0; i < strLen; ++i)
    {
        EnQueue(&queue, &(setCh[i]));
    }

    for (i = 0; i < strLen; ++i)
    {
        Character *c = NULL;
        DeQueue(&queue, &c);
        printf("Chracter: %c\n", *(c->ch));
    }

    // Free Memory
    for (; i < strLen; ++i)
    {
        free(setCh[i]);
        free((setCh[i])->ch);
    }

    free(queue);

    system("pause");
    return 0;
}