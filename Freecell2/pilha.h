#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include <stdlib.h>

typedef struct ItemList
{
    int value;
    struct ItemList *next;
}Item;

typedef struct PileStructure
{
    Item *start;
    int length;
}Pile;

Pile* createPile();
int addNewItemPile(Pile* pile, int value);
int addItemPile(Pile* pile, Item* item);
Item* removeTopItemPile(Pile* pile);
int deleteItem(Item* item);
int deletePile(Pile* pile);
Item* getPreviousItemOnPile(Item *item, Pile *pile);

#endif // PILHA_H_INCLUDED
