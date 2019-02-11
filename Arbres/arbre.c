#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

File* initFile(){
    File *f = (File*)malloc(sizeof(File));
    f->tete = NULL;
    f->queue = NULL;
    return f;
}
int estVide(File F){
    return (F.tete == NULL && F.queue == NULL);
}
Node* getTeteFile(File F){
    if (!estVide(F)) return F.tete->contenu;
}
Element* createNodeFile(Node* e){
    Element* p = (Element*)malloc(sizeof(Element));
    p->contenu = e;
    p->suivant = NULL;
    return p;
}
void enfiler(File *F, Element* e){
    if(estVide(*F)){
        F->tete = e;
        F->queue = e;
    }else{
        F->queue->suivant= e;
        F->queue = e;
    }
}
void defiler(File *F){
    if(!estVide(*F)){
        if(F->tete == F->queue){
            free(F->tete);
            F->tete = NULL;
            F->queue = NULL;
        }else{
            Element* tmp = F->tete;
            F->tete = F->tete->suivant;
            free(tmp);
        }
    }
}

Node* getTetePile(Element* pil){
    if (pil != NULL) return pil->contenu;
    return NULL;
}
Element* createNodePile(Node* e){
    Element* p = (Element*)malloc(sizeof(Element));
    p->contenu = e;
    p->suivant = NULL;
    return p;
}
void empiler(Element** pil, Element* e){
    e->suivant = *pil;
    *pil = e;
}
void depiler(Element** pil){
    if (*pil) *pil = (*pil)->suivant;
}

void setFilsGauche(Node* A, Node* n){
    if (A != NULL) A->left = n;
}
void setFilsDroit(Node* A, Node* n){
    if (A != NULL) A->right = n;
}
Node* getFilsGauche(Node* A){
    if (A != NULL) return A->left;
    return NULL;
}
Node* getFilsDroit(Node* A){
    if (A != NULL) return A->right;
    return NULL;
}
int getNodeValue(Node* A){
    if (A != NULL) return A->content;
    return -1;
}

Node* createNode(int data){
    Node* n = (Node*)malloc(sizeof(Node));
    n->content = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}
int estFeuille(Node* A){
    return (A != NULL && A->left == NULL && A->right == NULL);
}
int taille(Node* A){
    if (A == NULL) return 0;
    return 1 + taille(A->left) + taille(A->right);
}
int Max(int a, int b){
    if (a > b) return a;
    return b;
}
int hauteur(Node* A){
    if (A == NULL) return 0;
    return 1 + Max(hauteur(A->left), hauteur(A->right));
}
void calculHauteur(Node* A){
    if (A != NULL){
        A->haut = hauteur(A->right) - hauteur(A->left);
        calculHauteur(A->left);
        calculHauteur(A->right);
    }
}

void prefixe(Node* A){
    if (A != NULL){
        printf("(%2d - %d) ", A->content, A->haut);
        prefixe(A->left);
        prefixe(A->right);
    }
}
void infixe(Node* A){
    if (A != NULL){
        infixe(A->left);
        printf("%2d ", A->content);
        infixe(A->right);
    }
}
void postfixe(Node* A){
    if (A != NULL){
        postfixe(A->left);
        postfixe(A->right);
        printf("%2d-> ", A->content);
    }
   
}
void prefixeIt(Node* A){
    Node* n;
    Element *pil = NULL, *p;
    n = A;
    while (n != NULL){
        printf("%2d-> ", n->content);
        if (n->right){
            p = createNodePile(n->right);
            empiler(&pil, p);
        }
        n = n->left;
        if (n == NULL){
            n = getTetePile(pil);
            depiler(&pil);
        }
    }
}
void infixeIt(Node* A){
    Node *n, *pre;
    if (A == NULL) return;
    n = A;
    while (n != NULL){
        if (n->left == NULL){
            printf("%d-> ", n->content);
            n = n->right;
        }else{
            pre = n->left;
            while (pre->right != NULL && pre->right != n)
                pre = pre->right;
            if (pre->right == NULL){
                pre->right = n;
                n = n->left;
            }else{
                pre->right = NULL;
                printf("%d ", n->content);
                n = n->right;
            }
        }
    }
}
void parcoursLarg(Node* A){
    Node* n;
    Element *p, *l, *r;
    p = createNodePile(A);

    File* F = initFile();
    enfiler(F, p);

    while (!estVide(*F)){
        n = getTeteFile(*F);
        defiler(F);
        printf("%2d-> ", n->content);
        if (n->left != NULL){
            l = createNodeFile(n->left);
            enfiler(F, l);
        }if (n->right != NULL){
            r = createNodeFile(n->right);
            enfiler(F, r);
        }
    }
}

Node* insertArbre(Node* A, int data){
    Node* p;
    p = createNode(data);

    if(A == NULL){
        A = p;
    }else{
        if(A->content > data){
            A->left = insertArbre(A->left, data);
        }else{
            A->right = insertArbre(A->right, data);
        }
    }
    return A;
}

void SRD (Node** A){
    Node* p = (*A)->left;
    (*A)->left = p->right;
    p->right = (*A);
    *A = p;
    calculHauteur(*A);
}
void SRG (Node** A){
    Node* p = (*A)->right;
    (*A)->right = p->left;
    p->left = (*A);
    *A = p;
    calculHauteur(*A);
}
void DRD (Node** A){
    SRG(&((*A)->left));
    SRD(A);
}
void DRG (Node** A){
    SRD(&((*A)->right));
    SRG(A);
}

void equilibrer(Node** A){
    Node* tmp = *A;
    if (tmp->haut == 2){
        if (tmp->right->haut >= 0) SRG(A);
        else DRG(A);
    }else if (tmp->haut == -2){
        if (tmp->left->haut <= 0) SRD(A);
        else DRD(A);
    }
    calculHauteur(*A);
    return;
}
void ajouterAVL(Node** A, int n){
    if (*A == NULL){
        Node* p;
        p = createNode(n);
        *A = p;
        (*A)->haut = 0;
    }else if (n < (*A)->content)
        ajouterAVL(&((*A)->left), n);
    else if (n > (*A)->content)
        ajouterAVL(&((*A)->right), n);
    calculHauteur(*A);
    equilibrer(A);
}
