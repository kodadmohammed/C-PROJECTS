#include <stdio.h>
#include "gestionFacture.h"
#include <stdlib.h>
#include <string.h>
int g=1;

//-------Ligne de commande---------------------------------------------------------------
ElementLC* createLC(LC lc){
	ElementLC *e;
	
	e=(ElementLC*)malloc(sizeof(ElementLC));
	e->contenu=lc;
	e->suivant=NULL;
	return e;
}
void saisirLC(ElementLC **L,ElementProduit **LP){
		printf("\n------Ligne de commande -----\n");
		LC *c;
		c=(LC*)malloc(sizeof(LC));
		int qte,code;
		double total;
		
		printf("\nCode produit :");scanf("%d",&code);
		printf("\nQuantite: ");scanf("%d",&qte);

		c->p=chercherProduit(LP,code);
		c->Qte=qte;
		c->total=c->p.prix*qte;
		
		ElementLC *e;
		e=createLC(*c);
		insertLCFinListe(L,e);
}
void menuGestionLC(){

 	    printf("\n---------------<<MENU DES COMMANDES>>-------------\n ");
		printf("| 1:Afficher les commandes------------------------|\n ");
		printf("| 2:ajouter une commande--------------------------|\n ");
		printf("| 3:Ajouter un produit----------------------------|\n ");
		printf("| 4:sortir ---------------------------------------|\n");
		printf("|---------------<<LISTE TERMINER>>-------------------|\n ");
}
void afficherLC(LC lc){
		printf(" %s\t\t%d\t%.2f  \n",lc.p.designation,lc.Qte,lc.total);
}
void afficherListeLC(ElementLC *L){
	int i=1;
ElementLC *p;
p=L;
system("cls");
printf("----------AFFICHAGE DE LA LISTE DES COMMANDES----\n\n");
printf(" Produit\tQuantite\tTotal \n\n");

while(p!=NULL){
	printf("%d - ",i);
	afficherLC(p->contenu);
	p=p->suivant;
	i++;
}
}
void insertLCFinListe(ElementLC **L,ElementLC *n){

if(*L==NULL) {

*L=n;
return;	
}

ElementLC *c;
c=*L;
ElementLC *position;
position=*L;

while(c!=NULL){
	position=c;
	c=c->suivant;
}

position->suivant=n;

}
void insertLCDebutListe(ElementLC **L,ElementLC *n){
	
	n->suivant=*L;
	
	*L=n;
}


//----Facture-------------------------------------------------------------------------
ElementFacture* createFacture(Facture f){
	ElementFacture *e;
	
	e=(ElementFacture*)malloc(sizeof(ElementFacture));
	e->contenu=f;
	e->suivant=NULL;
	return e;
}
void saisirFacture(ElementFacture **L,ElementClient **LClt){
		printf("\n--------<<NOUVELLE FACTURE>> -----\n");
		Facture *c;
		c=(Facture*)malloc(sizeof(Facture));
		int num,test=1,d;
		double HT=0,TTC=0;

		
		printf("\nNumero Client :");scanf("%d",&num);

  		ElementProduit * Produits=NULL;
		loadDataProduits(&Produits);		
		ElementLC * lc=NULL;
		
		while(test!=4){
			menuGestionLC();
			scanf("%d",&test);
		
			switch (test){
			case 1:
  				afficherListeLC(lc);
  			break;
			
			case 2:
				afficherListeProduits(Produits);
  				saisirLC(&lc,&Produits);
  			break;
			
			case 3:
  				saisirProduit(&Produits);
  			break;
  			
			case 4:
  				
  			break;
			default:
				printf("Choix invalide !");
			break;
			
			}
		}
		
		c->num=g;
		g++;
		c->Clt=chercherClient(LClt,num);
		c->Cmd=lc;
		c->HT=0;
		
		ElementLC * u;
		u=c->Cmd;
		while(u!=NULL){c->HT=c->HT+u->contenu.total;u=u->suivant;}
		c->TTC=c->HT+c->HT*0.2;
				
		ElementFacture *e;
		e=createFacture(*c);
		insertFactureFinListe(L,e);
		
}
void menuGestionFacture(){
 	    printf("|-------------MENU DE FACTURE---------------|\n ");
		printf("| 1:Afficher les Factures-------------------|\n ");
		printf("| 2:Saisir une Facture----------------------|\n ");
		printf("| 3:Supprimer une Facture-------------------|\n ");
		printf("| 4:Ajouter un Client-----------------------|\n ");
		printf("|------------------FIN DE LISTE-------------|\n ");
}
void afficherFacture(Facture F){
		printf(" %d\t\t%s\t\t%.2f\t\t%.2f  \n",F.num,F.Clt.nom,F.HT,F.TTC);
}
void afficherListeFacture(ElementFacture *L){
	
ElementFacture *p;
p=L;
system("cls");
printf("\n----------<< LISTE DES Factures>>----\n\n");
printf(" Numero\t\tNom Client\tTotal HT\tTotal TTC  \n\n");

while(p!=NULL){
	afficherFacture(p->contenu);
	p=p->suivant;

}
}
void insertFactureFinListe(ElementFacture **L,ElementFacture *n){

if(*L==NULL) {

*L=n;
return;	
}

ElementFacture *c;
c=*L;
ElementFacture *position;
position=*L;

while(c!=NULL){
	position=c;
	c=c->suivant;
}



position->suivant=n;

}
void insertFactureDebutListe(ElementFacture **L,ElementFacture *n){
	
	n->suivant=*L;
	
	*L=n;
}
void supprimerFacture(ElementFacture **L,int num){
	ElementFacture * p;
	ElementFacture * q;
	p=*L;
	q=(*L)->suivant;
	if(p->contenu.num==num){
		*L=(*L)->suivant;
		free(p);
		return;
	}
	
	while(q!=NULL){
		if(q->contenu.num==num){
			q=q->suivant;
			free(p->suivant);
			p->suivant=q;
		return;
		}
	}
}


