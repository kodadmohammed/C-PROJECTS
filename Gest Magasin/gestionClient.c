#include <stdio.h>
#include "gestionClient.h"
#include <stdlib.h>
#include <string.h>
ElementClient* createClient(Client clt){
	ElementClient *e;
	
	e=(ElementClient*)malloc(sizeof(ElementClient));
	e->contenu=clt;
	e->suivant=NULL;
	return e;
}

void saisirClient(ElementClient **L){
		printf("\n--------CREER UN NOUVEAU Client -----\n");
		Client *c;
		c=(Client*)malloc(sizeof(Client));
		char nom[20],prenom[20];int num, age;
		
		printf("\nCode:");scanf("%d",&num);
		printf("\nNom:");scanf("%s",nom);rewind(stdin);
		printf("\nPrenom:");scanf("%s",prenom);rewind(stdin);
		printf("\nAge:");scanf("%d",&age);
		
		c->num=num;
		c->age=age;
		c->nom=(char*)malloc(sizeof(char)*strlen(nom));
		strcpy(c->nom,nom);
		c->prenom=(char*)malloc(sizeof(char)*strlen(prenom));
		strcpy(c->prenom,prenom);
		
		ElementClient *e;
		e=createClient(*c);
		insertClientFinListe(L,e);
		
}
void menuGestionClients(){
 	    printf("\n---------------MENU-------------\n ");
		printf("1:Afficher les client\n ");
		printf("2:Saisir un client\n ");
		printf("3:Supprimer un client\n ");
		printf("\n----------------------------\n ");
}
void afficherClient(Client c){
		printf("| %d\t\t\t%s\t\t%s\t\t\t%d|\n",c.num,c.nom,c.prenom,c.age);
}
void afficherListeClients(ElementClient *L){
	
ElementClient *p;
p=L;
system("cls");
printf("\n----------------------<<Clients>>-----------------------------------\n\n");
printf("| Numero\t\t\tNom\t\tPrenom\t\tAge |\n\n");

while(p!=NULL){
	afficherClient(p->contenu);
	p=p->suivant;

}
printf("\n|----------------------<<FIN DE LISTE >>------------------------------|\n");
}
void insertClientFinListe(ElementClient **L,ElementClient *n){

if(*L==NULL) {

*L=n;
return;	
}

ElementClient *c;
c=*L;
ElementClient *position;
position=*L;

while(c!=NULL){
	position=c;
	c=c->suivant;
}

position->suivant=n;

}
void insertClientDebutListe(ElementClient **L,ElementClient *n){
	
	n->suivant=*L;
	
	*L=n;
}
void loadDataClients(ElementClient **L){
	char nom[][10]={"kodad","tarkane","mabchour","zbaida","elazizi","barbie","khatiri","stat","lyamani","kader"};
	char prenom[][10]={"mohammed","amin","inass","renard","yassine","fola","yassmine","itihad","hazimo ra3d","GOGO"};
	int num[]={50,512,121,145,457,16,134,154,555,1248};
	int age[]={18,19,20,21,22,23,24,25,26,27};

	ElementClient *e;

	Client *c;
	c=(Client*)malloc(sizeof(Client));
	int i;
	for(i=0;i<10;i++){
//---Initialisation d'un client-----------------------------
		c->num=num[i];
		c->nom=(char*)malloc(sizeof(char)*20);
		strcpy(c->nom,nom[i]);
		c->prenom=(char*)malloc(sizeof(char)*20);
		strcpy(c->prenom,prenom[i]);
		c->age=age[i];
		

		e=createClient(*c);


		insertClientFinListe(L,e);

	}
	}
Client chercherClient(ElementClient **L,int num){
		ElementClient * P;
	P=*L;
	while(P!=NULL){
		if(P->contenu.num==num){
			return P->contenu;
		}
		
		P=P->suivant;
	}
}
