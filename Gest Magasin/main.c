#include <stdio.h>
#include "gestionFacture.c"
#include <stdlib.h>
#include <string.h>

main(){
	
	printf("\t\t-------------------------GESTION DE MAGASIN---------------------------------\n");
	printf("\t\t---------------------------KODAD MOHAMMED-----------------------------------\n");
	printf("\t\t-------------------------------BDCC1----------------------------------------\n");
	printf("\t\t-----------------------------2017/2018--------------------------------------\n\n\n\n");
int choix=1,f;
ElementClient * Clients=NULL;
loadDataClients(&Clients);
ElementFacture * Factures=NULL;

while(choix){
	menuGestionFacture();
	printf("entrez votre choix S'il vous plais:\t");
	scanf("%d",&choix);
	switch(choix){
		case 1:
			afficherListeFacture(Factures);
		break;
		
		case 2:
			afficherListeClients(Clients);
			saisirFacture(&Factures,&Clients);
		break;
		
		case 3:
			printf("Choisir numero de facture :");scanf("%d",&f);
			supprimerFacture(&Factures,f);
		break;
		
		case 4:
			saisirClient(&Clients);
		break;
		
		default:
			printf("Choix invalide !!");
		break;
	}
}



return 0;
}
