#include "pilha.h"

Pile* createPile()
{
    Pile* newPile = (Pile*)malloc(sizeof(Pile));
    if(newPile == NULL)
        return NULL;

    newPile->start = NULL;
    newPile->length = 0;
    return newPile;
}

int addNewItemPile(Pile* pile, int value)
{
    Item* newItem;
    if(pile == NULL)
        return -1;

    newItem = (Item*)malloc(sizeof(Item));
    if(newItem == NULL)
        return -1;

    newItem->value = value;
    newItem->next = pile->start;
    pile->start = newItem;
    pile->length++;
    return 0;
}

int addItemPile(Pile* pile, Item* item)
{
    if(item == NULL)
        return -1;

    if(item->next != NULL)
        return -1;

    item->next = pile->start;
    pile->start = item;
    pile->length++;
    return 0;
}

Item* removeTopItemPile(Pile* pile)
{
    Item* removedItem;
    if(pile == NULL || pile->length <= 0)
        return NULL;

    removedItem = pile->start;
    pile->start = removedItem->next;
    pile->length--;
    removedItem->next = NULL;
    return removedItem;
}

int deleteItem(Item* item)
{
    if(item == NULL || item->next != NULL)
        return -1;

    free(item);
    return 0;
}

int deletePile(Pile* pile)
{
    Item* item;
    if(pile == NULL)
        return -1;

    while(pile->length > 0)
    {
        item = removeTopItemPile(pile);
            if(item != NULL)
            deleteItem(item);
    }

    free(pile);
    return 0;
}


Item* getPreviousItemOnPile(Item *item, Pile *pile)
{
    if(item == NULL || pile == NULL)
        return NULL;

    Item* Q = pile->start;
    if(Q == NULL) return NULL;
    if(Q == item) return item;

    while(Q->next != NULL)
    {
        if(Q->next == item) return Q;

        Q = Q->next;
    }

    return NULL;
}
