typedef struct Produit{
	int code;
	char *designation;
	double prix;
}Produit;

typedef struct ElementProduit{
	Produit contenu;
	struct ElementProduit * suivant;
}ElementProduit;


ElementProduit* createProduit(Produit pr);
void saisirProduit(ElementProduit **L);
void menuGestionProduits();
void afficherProduit(Produit p);
void afficherListeProduits(ElementProduit *L);
void insertProduitFinListe(ElementProduit **L,ElementProduit *n);
void insertProduitDebutListe(ElementProduit **L,ElementProduit *n);
void loadDataProduits(ElementProduit **L);
void supprimerProduit(ElementProduit **L,int code);
Produit chercherProduit(ElementProduit **L,int code);
