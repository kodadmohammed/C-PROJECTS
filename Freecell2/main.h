#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "pilha.h"


Pile *top_slots[4];
Pile *base_slots[4];
Pile *mid_slots[8];


void cardToStr(Item *card, char *c);
void shuffleArray(int *arr, size_t n);
void initializeCards();
int moveCardToPile(Pile *from, Pile *to);
int moveCardToBase(Pile *from);
int getCardNipe(Item *card);
int getCardNumber(Item *card);
int canMove(Pile *from, Pile *to);
int canMoveToBase(Pile *from);
void Color(int couleurDuTexte,int couleurDeFond);



#define NOMINMAX 1
//Je vais utiliser ma propre fonction max



void drawCard(Item *card);
void drawBoard();
void drawMiddle();
void drawRequestHandle();
void receiveUserInput();
void checkGameStatus();


int gameStatus; //statut du jeu
#define GAME_STATUS_START 0
#define GAME_STATUS_CHOSECARD 1
#define GAME_STATUS_CHOSETARGET 2
#define GAME_STATUS_DEFEAT 3
#define GAME_STATUS_VICTORY 4

Pile *selectedSlot; //pile sélectionnée pour se déplacer

#endif // MAIN_H_INCLUDED
