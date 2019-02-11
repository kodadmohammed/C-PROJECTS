#include "arbre.c"

int main(){
    Node *A,*e1,*e2,*e3,*e4,*e5,*e6,*e7,*e8,*e9,*e10;
	e1=createNode(1);e2=createNode(2);e3=createNode(3);e4=createNode(4);
	e5=createNode(5);e6=createNode(6);e7=createNode(7);e8=createNode(8);
	e9=createNode(9);e10=createNode(10);

	A = e5;
	setFilsGauche(e5,e3);setFilsDroit(e5,e8);
	setFilsGauche(e3,e1);setFilsDroit(e3,e4);
	setFilsDroit(e1,e2);setFilsDroit(e8,e9);
	setFilsGauche(e8,e6);setFilsDroit(e9,e10);
	setFilsDroit(e6,e7);

	printf("\npostfixe : "); postfixe(A); printf("fin");
	printf("\nprefixe iter : "); prefixeIt(A); printf("fin");
	printf("\nparcours en largeur : "); parcoursLarg(A); printf("fin");
	printf("\ninfixe : "); infixeIt(A); printf("fin");
/*
	A = insertArbre(A, 0);
	A = insertArbre(A, 15);
	A = insertArbre(A, 11);
	printf("\ninfixe : "); infixe(A);
	*/
    A = NULL;
	ajouterAVL(&A, 7);
	ajouterAVL(&A, 2);
	ajouterAVL(&A, 3);
	ajouterAVL(&A, 9);
	ajouterAVL(&A, 11);
	ajouterAVL(&A, 5);
	ajouterAVL(&A, 10);

    printf("\nprefixe equilibrée  : "); prefixeIt(A);



    return 0;
}
