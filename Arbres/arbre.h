#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

typedef struct Node{
    int content;
    int haut;
    struct Node* left;
    struct Node* right;
}Node;
typedef struct Node* Arbre;

typedef struct Element{
    Node* contenu;
    struct Element* suivant;
}Element;
typedef struct Element* Pile;

typedef struct File{
    Element* tete;
    Element* queue;
}File;

File* initFile();
int estVide(File F);
Node* getTeteFile(File F);
Element* createNodeFile(Node* e);
void enfiler(File *F, Element* e);
void defiler(File *F);

Node* getTetePile(Element* pil);
Element* createNodePile(Node* p);
void empiler(Element** pil, Element* e);
void depiler(Element** pil);

void setFilsGauche(Node* A, Node* n);
void setFilsDroit(Node* A, Node* n);
Node* getFilsGauche(Node* A);
Node* getFilsDroit(Node* A);
int getNodeValue(Node* A);

Node* createNode(int data);
int estFeuille(Node* A);
int taille(Node* A);
int Max(int a, int b);
int hauteur(Node* A);
void calculHauteur(Node* A);

void prefixe(Node* A);
void infixe(Node* A);
void postfixe(Node* A);

void prefixeIt(Node* A);
void infixeIt(Node* A);
void parcoursLarg(Node* A);

Node* insertArbre(Node* A, int data);

void SRD (Node** A);
void SRG (Node** A);
void DRD (Node** A);
void DRG (Node** A);

void equilibrer(Node** A);
void ajouterAVL(Node** A, int n);

#endif 
