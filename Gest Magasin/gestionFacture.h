#include "gestionClient.c"
#include "gestionProduit.c"

//--------Ligne de commande--------------------
typedef struct LigneDeCommande{
	Produit p;
	int Qte;
	double total;	
}LC;

typedef struct ElementLC{
	LC contenu;
	struct ElementLC * suivant;
}ElementLC;
//----------------------------------------------

//-------Facture--------------------------------
typedef struct Facture{
	int num;
	ElementLC * Cmd;
	Client Clt;
	double HT;
	double TTC;
}Facture;

typedef struct ElementFacture{
	Facture contenu;
	struct ElementFacture * suivant;
}ElementFacture;
//-----------------------------------------------


ElementLC* createLC(LC lc);
void saisirLC(ElementLC **lc,ElementProduit **LP);
void menuGestionLC();
void afficherLC(LC lc);
void afficherListeLC(ElementLC *lc);
void insertLCFinListe(ElementLC **lc,ElementLC *n);
void insertLCDebutListe(ElementLC **lc,ElementLC *n);

ElementFacture* createFacture(Facture F);
void saisirFacture(ElementFacture **L,ElementClient **LClt);
void menuGestionFacture();
void afficherFacture(Facture F);
void afficherListeFacture(ElementFacture *L);
void insertFactureFinListe(ElementFacture **L,ElementFacture *n);
void insertFactureDebutListe(ElementFacture **L,ElementFacture *n);
void supprimerFacture(ElementFacture **L,int num);




