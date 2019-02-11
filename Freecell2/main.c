#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include "pilha.h"
#include "ui.c"

void cardToStr(Item *card, char *c)
{
    if(card == NULL)
    {
        strcpy(c, "   ");
        return;
    }

    int category = getCardNipe(card);
    int value = getCardNumber(card);
    c[0] = ' '; c[1] = ' '; c[2] = ' ';
    switch(value)
    {
        case 0: c[1] = 'A'; break; //A
        case 9: c[0] = '1'; c[1] = '0'; break; //10
        case 10: c[1] = 'J'; break; //J
        case 11: c[1] = 'Q'; break; //Q
        case 12: c[1] = 'K'; break; //K
        default: c[1] = '1'+value; break;
    }
    switch(category)
    {
        case 0: c[2] = '\3'; break;
        case 1: c[2] = '\4'; break;
        case 2: c[2] = '\5'; break;
        case 3: c[2] = '\6'; break;
        default: c[2] = ' '; break;
    }
}

void shuffleArray(int *arr, size_t n)
{
    if(n>1)
    {
        size_t i, j;
        for(i = 0; i < n-1; i++)
        {
            j = i + (rand() / (RAND_MAX / (n - i) + 1));
            int t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
        }
    }
}

void initializeCards()
{
    srand(time(NULL));
    int ar[52];
    size_t i;
    for(i=0; i<52; i++)
    {
        ar[i] = i;
    }

    shuffleArray(ar, 52);


    for(i=0; i<=3; i++)
    {
        top_slots[i] = createPile();
        base_slots[i] = createPile();
        mid_slots[i] = createPile();
        mid_slots[i+4] = createPile();
    }

    for(i=0; i<52; i++){
        addNewItemPile(mid_slots[i%8], ar[i]);
    }

    gameStatus = GAME_STATUS_START;
}

void writeCards()
{
    if(!mid_slots[0])
        return;

    int i;
    Item* item;
    char *c = malloc(sizeof(char[3]));

    for(i=0; i<8; i++)
    {
        if(mid_slots[i])
        {
            item = mid_slots[i]->start;
            while(item->next != NULL)
            {
                cardToStr(item, c);
                printf("%s   ", c);
                item = item->next;
            }
            printf("\n");
        }
    }
    free(c);
}

int moveCardToPile(Pile* from, Pile* to)
{
    if(from == NULL || to == NULL)
        return -1;

    Item *prev = removeTopItemPile(from);
    if(prev == NULL)
        return -1;

    return addItemPile(to, prev);
}

int moveCardToBase(Pile *from)
{
    if(from == NULL)
        return -1;

    Item *prev = removeTopItemPile(from);
    if(prev == NULL)
        return -1;

    return addItemPile(base_slots[getCardNipe(prev)], prev);
}

int getCardNipe(Item* card)
{   int a=4;
    if(card != NULL)
        a = (int)(card->value / 13);
        if((a==0)||(a==1)){
            Color(12,0);
            return a;
            Color(7,0);
        }
            Color(7,0);
        return a;
    return -1;
}

int getCardNumber(Item* card)
{
    if(card != NULL)
        return (int)(card->value % 13);
    return -1;
}

int canMove(Pile *from, Pile *to)
{
    if(from == NULL || to == NULL)
        return 0;

    if(from->start == NULL)
        return 0;

    Item *toMove = from->start;
    Item *toReceive = to->start;
    if(toReceive == NULL)
        return 1;

    if(getCardNumber(toMove) != getCardNumber(toReceive)-1)
        return 0;

    if((getCardNipe(toMove) ^ getCardNipe(toReceive)) > 1)
        return 1;

    return 0;
}

int canMoveToBase(Pile *from)
{
    if(from == NULL || base_slots[0] == NULL)
        return -1;

    Item *toMove = from->start;
    if(toMove == NULL)
        return -1;

    Item *toReceive = base_slots[getCardNipe(toMove)]->start;
    if(toReceive != NULL)
    {
        if(getCardNumber(toReceive) == getCardNumber(toMove)-1)
            return 1;
    }
    else if(getCardNumber(toMove) == 0)
        return 1;

    return 0;
}

int main()
{
    initializeCards();
    drawBoard();
    return 0;
}

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
