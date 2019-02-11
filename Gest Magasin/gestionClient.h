typedef struct Client{
	int num;
	char *nom;
	char *prenom;
	int age;
}Client;

typedef struct ElementClient{
	Client contenu;
	struct ElementClient *suivant;
}ElementClient;


ElementClient* createClient(Client c);
void saisirClient(ElementClient **L);
void menuGestionClients();
void afficherClient(Client c);
void afficherListeClients(ElementClient *L);
void insertClientFinListe(ElementClient **L,ElementClient *n);
void insertClientDebutListe(ElementClient **L,ElementClient *n);
void loadDataClients(ElementClient **L);
Client chercherClient(ElementClient **L,int num);
