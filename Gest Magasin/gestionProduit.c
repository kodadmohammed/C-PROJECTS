#include <stdio.h>
#include "gestionProduit.h"
#include <stdlib.h>
#include <string.h>
ElementProduit* createProduit(Produit pr){
	ElementProduit *e;
	
	e=(ElementProduit*)malloc(sizeof(ElementProduit));
	e->contenu=pr;
	e->suivant=NULL;
	return e;
}

void saisirProduit(ElementProduit **L){
		printf("\n--------<<CRration D'UN NOUVEAU PRODUIT>> -----\n");
		Produit *p;
		p=(Produit*)malloc(sizeof(Produit));
		char des[15];int code; double prix;
		printf("\nCode:");scanf("%d",&code);
			printf("\nPrix:");scanf("%lf",&prix);
	
		printf("\nNOM PRODUIT:");scanf("%s",des);rewind(stdin);
		p->code=code;
		p->prix=prix;
		printf("\nle prix entrée est:%.2f",p->prix);
		p->designation=(char*)malloc(sizeof(char)*strlen(des));
		strcpy(p->designation,des);
		ElementProduit *e;e=createProduit(*p);
		insertProduitFinListe(L,e);
		
}
void menuGestionProduits(){
 	   printf("\n---------------MENU PRODUIT STEP PLUS-------------\n ");
		printf("| 1:Afficher les produits --------------------------|\n ");
		printf("| 2:Ajouter un produit-------------------------------|\n ");
		printf("| 3:Supprimer un produit----------------------------|\n ");
		printf("| \n------------------------------------------------|\n ");
}
void afficherProduit(Produit p){
		printf(" %d\t%s\t\t%.2f \n",p.code,p.designation,p.prix);
		

}
void afficherListeProduits(ElementProduit *L){
		system("cls");
		ElementProduit *p;
p=L;
printf("\n----------<<lES Produits>>------\n");
while(p!=NULL){
	afficherProduit(p->contenu);
	p=p->suivant;

}

}
void insertProduitFinListe(ElementProduit **L,ElementProduit *n){



if(*L==NULL) {
*L=n;
return;	
}
ElementProduit *p;
p=*L;
ElementProduit *position;
position=*L;
while(p!=NULL){
	position=p;
	p=p->suivant;
}

position->suivant=n;
}
void insertProduitDebutListe(ElementProduit **L,ElementProduit *n){
	
	n->suivant=*L;

	*L=n;
}
void loadDataProduits(ElementProduit **L){

char designation[][10]={"kodad","mohammed","oujda","shampo",
"chocolat","bonbon","lunette","step plus","tokyo goul","titan"};
int code[]={1,2,3,4,5,6,7,8,9,10};
double prix[]={3200,3400,4000,4200,4400,4600,4800,5200,5600,6200};

ElementProduit *e;
Produit *p;
p=(Produit*)malloc(sizeof(Produit));
int i;
for(i=0;i<10;i++){
p->code=code[i];
p->designation=(char*)malloc(sizeof(char)*12);
strcpy(p->designation,designation[i]);
p->prix=prix[i];

e=createProduit(*p);

insertProduitFinListe(L,e);
}
}
void supprimerProduit(ElementProduit **L,int code){
	ElementProduit * p;
	ElementProduit * q;
	p=*L;
	q=(*L)->suivant;
	if(p->contenu.code==code){
		*L=(*L)->suivant;
		free(p);
		return;
	}
	
	while(q!=NULL){
		if(q->contenu.code==code){
			q=q->suivant;
			free(p->suivant);
			p->suivant=q;
		return;
		}
	}
}
Produit chercherProduit(ElementProduit **L,int code){
	ElementProduit * P;
	P=*L;
	while(P!=NULL){
		if(P->contenu.code==code){
			return P->contenu;
		}
		
		P=P->suivant;
	}
}
