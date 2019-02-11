#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "main.h"
#include "pilha.h"

void drawCard(Item *card)
{
    if(card != NULL)
    {
        char *c = malloc(sizeof(char[3]));
        cardToStr(card, c);
        printf("{%s} ", c);
        free(c);
    }
    else
    printf("{   } ");
}


void drawBoard()
{
    system("cls");
    int i;

    if(top_slots[0] == NULL)
        return;
/*

      #1   #2    #3    #4       C     O     P     E
    {   } {   } {   } {   } | {   } {   } {   } {   }
    -------------------------------------------------
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
    {   } {   } {   } {   }   {   } {   } {   } {   }
      a     b     c     d       e     f     g     h

    Dans quelle colonne est la carte que vous voulez prendre? _

    (après avoir sélectionné la lettre)
    À l'endroit où vous voulez envoyer cette carte?
    Valid options: 1,2,3,4,a,b,c,d,e,f,g,h,BASE
    Enter with the target: _


   // NOTE: Les options possibles sont aussi, out, base, costume


*/

    printf(" #1    #2    #3    #4       \3     \4     \5     \6 \n");
    for(i=0;i<4;i++)
        drawCard(top_slots[i]->start);

    printf("| ");

    for(i=0;i<4;i++)
        drawCard(base_slots[i]->start);

    printf("\n");
    printf("------------------------------------------------- \n");

    drawMiddle();

    printf("\n\n");

    drawRequestHandle();

    if(gameStatus != GAME_STATUS_DEFEAT && gameStatus != GAME_STATUS_VICTORY)
        receiveUserInput();
}


int max(a,b){
    return ((a)>(b)?(a):(b));
}
void drawMiddle()
{

    if(mid_slots[0] == NULL)
        return;

    Pile *tempPile[8];
    Item *tempItem;
    Item *tmpVector[8];
    int i, j, max_length;
    max_length = -1;

    for(i=0;i<8;i++)
    {

        tempPile[i] = createPile();
        tempItem = mid_slots[i]->start;
        while(tempItem != NULL)
        {
            addNewItemPile(tempPile[i], tempItem->value);
            tempItem = tempItem->next;
        }

        max_length = max(max_length, tempPile[i]->length);

    }

    for(i = 0; i < max_length; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(i == 0)
                tmpVector[j] = tempPile[j]->start;
            else if(tmpVector[j] != NULL){
                tmpVector[j] = tmpVector[j]->next;
            }

            drawCard(tmpVector[j]);
            if(j == 3)
                printf("  ");
        }
        printf("\n");
    }


    printf("  a     b     c     d       e     f     g     h   \n");

    for(i= 0; i < 8; i++)
        deletePile(tempPile[i]);

}

void drawRequestHandle()
{

    switch(gameStatus)
    {
        case GAME_STATUS_START:
            printf("-----------------Bonjour sur notre Application FreeCell----------------------\n");
            printf("Au-dessus, vous verrez vos cartes!\n");
        case GAME_STATUS_CHOSECARD:
            printf("Veuillez choisir la carte que vous voulez deplacer!\n");
            printf("Valid options: a, b, c, d, e, f, g, h, 1, 2, 3, 4\n");
            break;
        case GAME_STATUS_CHOSETARGET:
            printf("Veuillez choisir ou vous voulez vous deplacer ");
            drawCard(selectedSlot->start);
            printf("\nValid options: a, b, c, d, e, f, g, h, 1, 2, 3, 4, base\n");
            break;
        case GAME_STATUS_DEFEAT:
            printf("Plus de mouvements possibles. Jeu termine!");
            break;
        case GAME_STATUS_VICTORY:
            printf("Felicitations, vous avez gagne!");
            break;
    }
}

void receiveUserInput()
{
    char *c = malloc(sizeof(char[5]));
    int i;
    scanf("%5s", c);
    if(gameStatus == GAME_STATUS_START || gameStatus == GAME_STATUS_CHOSECARD)
    {
        if(c[0] >= 'a' && c[0] <= 'h')
        {
            i = (int)(c[0] - 'a');
            selectedSlot = mid_slots[i];
        }
        else if(c[0] >= '1' && c[0] <= '4')
        {
            i = (int)(c[0] - '1');
            selectedSlot = top_slots[i];
        }
        else{
            printf("Selection non validee! \nValid options are a,b,c,d,e,f,g,h,1,2,3,4!\n");
            free(c);
            receiveUserInput();
            return;
        }


        if(selectedSlot->start == NULL)
        {
            printf("Cette pile n'a pas de cartes! Veuillez selectionner un autre emplacement.\n");
            free(c);
            receiveUserInput();
            return;
        }

        gameStatus = GAME_STATUS_CHOSETARGET;
    }
    else if(gameStatus == GAME_STATUS_CHOSETARGET)
    {
        Pile *targetSlot;
        if(strcasecmp(c, "base") == 0)
        {
            strcpy(c, "     ");
            free(c);
            if(canMoveToBase(selectedSlot) == 1)
            {
                moveCardToBase(selectedSlot);
                checkGameStatus();
                selectedSlot = NULL;
                drawBoard();
                return;
            }
            else
            {
                selectedSlot = NULL;
                printf("Deplacement invalide! Veuillez selectionner une autre carte.\n");
                gameStatus = GAME_STATUS_CHOSECARD;
                receiveUserInput();
                return;
            }

        }
        else if(c[0] >= 'a' && c[0] <= 'h')
        {
            i = (int)(c[0] - 'a');
            targetSlot = mid_slots[i];
        }
        else if(c[0] >= '1' && c[0] <= '4')
        {
            i = (int)(c[0] - '1');
            targetSlot = top_slots[i];
            if(targetSlot->length > 0)
            {
                printf("Deplacement invalide! Veuillez selectionner une autre carte.\n");
                free(c);
                selectedSlot = NULL;
                gameStatus = GAME_STATUS_CHOSECARD;
                receiveUserInput();
                return;
            }
        }
        else{
            printf("Selection non validee! \nValid options are a,b,c,d,e,f,g,h,1,2,3,4,base!");
            free(c);
            receiveUserInput();
            return;
        }

        if(canMove(selectedSlot, targetSlot) == 1)
        {
            moveCardToPile(selectedSlot, targetSlot);
            checkGameStatus();
        }
        else{
            printf("Deplacement invalide! Veuillez selectionner une autre carte.\n");
            free(c);
            selectedSlot = NULL;
            gameStatus = GAME_STATUS_CHOSECARD;
            receiveUserInput();
            return;
        }
    }

    free(c);
    drawBoard();
}

void checkGameStatus()
{

    if(top_slots[0]->length == 13 && top_slots[1]->length == 13 && top_slots[2]->length == 13 && top_slots[4]->length == 13){
        gameStatus = GAME_STATUS_VICTORY;
        return;
    }

    Pile *a, *b;
    int j;
    int isDefeat = 1;

    a = mid_slots[0];
    for(j=0; j<8; j++)
    {
        b = mid_slots[j];
        if(canMove(a, b) == 1 || canMove(b, a) == 1){
            isDefeat = 0;
            break;
        }
        if(j<4)
        {
            b = top_slots[j];
            if(top_slots[j]->length == 0)
            {
                isDefeat = 0;
                break;
            }
        }
    }

    if(isDefeat == 1)
        gameStatus = GAME_STATUS_DEFEAT;
    else
        gameStatus = GAME_STATUS_CHOSECARD;

}

