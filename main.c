/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : <A compléter>
 Date creation  : 26.04.2023

 Description    : Fichier de test des fonctions de la librairie liste_dynamique.
 						Chaque fonction de la librairie à tester à une fonction de
 						test.
 						Les fonctions de tests retournent toutes un bool si le test est
 						un succès et false sinon et ne prennent aucun paramètre. Dans le
 						main, toutes les fonctions de tests sont stockées dans un tableau
 						de pointeur sur des fonctions ne prenant aucun paramètre et
 						retournant un bool. Chaque fonction imprime son nom puis s'il y
 						a des erreurs, la nature de l'erreur pour faciliter le debuggage
 						. Pour chaque fonction, dans le main, on imprime si le test
 						était un échec ou une réussite selon le retour de la fonction de
 						test. Enfin, utilise un bool pour imprimer à la fin des tests
 						s'ils ont tous passés ou s'il y a encore des problèmes.


 Remarque(s)    : <A compléter>

 Compilateur    : Mingw-w64 gcc 9.0
 -----------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include "listes_dynamiques.h"
#include "fonctions_de_tests.h"
#include <assert.h>


/*void remplirListe(Liste *liste, int taille) {
	for (int i = 0; i < taille; ++i) {
		insererEnTete(liste, &i);
	}
}*/
bool (*tests[])(void) = {testInitialiser, testVider, testInsererEnTete,
								 testInsererEnQueue, testLongueur,
								 testEstVide, testSupprimerEnTete, testSupprimerEnQueue,
								 testSupprimerSelonCritere, testSontEgales};

int main(void) {
	bool testReussis = true;
	for (size_t i = 0; i < sizeof(tests) / sizeof(bool (*)(void)); i++) {
		bool reussite = tests[i]();
		printf("%s\n", reussite ? "reussi" : "echec");
		testReussis &= reussite;
	}

	printf("%s", testReussis ? "Tous les tests passent." : "Les tests ne passent "
																			 "pas");


	/*
	testInitialiser();
	testVider();
	testInsererEnTete();
	testInsererEnQueue();
	testEstVide();
	testSupprimerEnTete();
	testSupprimerEnQueue();
	testLongueur();
	testSupprimerSelonCritere();
	assert(testSontEgales());
	printf("Tous les tests passent.");
*/

	/*Liste *liste = initialiser();

	longueur(liste);
	printf("Est-ce que la liste est vide : %d \n", estVide(liste));

	for (int i = 0; i < 5; ++i) {
		insererEnTete(liste, &i);
	}

	printf("taille liste: %zu\n", longueur(liste));

	afficher(liste, FORWARD);
	afficher(liste, BACKWARD);
	//vider(liste, 0);
	printf("Vider\n");
	afficher(liste, FORWARD);
	// ATTENTION insererEnQueue fait un segfault -> a checker
	for(int i = 0; i < 5; ++i){
		insererEnTete(liste, &i);
	}
	afficher(liste, FORWARD);

	// Test supprimerEnTete
/*
  Info info = 0;
  Info* ptr = &info;
  supprimerEnTete(liste, ptr);
  printf("On enleve le premier element de la liste:\n");
  afficher(liste, FORWARD);
  printf("L'info contenue dans le premier maillon etait: %d\n", *ptr);

  // Test supprimerEnQueue
  printf("On enleve le dernier element de la liste:\n");
  supprimerEnQueue(liste, ptr);
  afficher(liste, FORWARD);
  printf("L'info contenue dans le dernier maillon etait: %d\n", *ptr);
*/
	//Test supprimerSelonCritere
	/*supprimerSelonCritere(liste, (bool (*)(size_t, const Info *)) impairOuindex);
	afficher(liste, FORWARD);
	Liste *liste3 = initialiser();
	Liste *liste4 = initialiser();
	Liste *liste5 = initialiser();
	for (int i = 0; i < 5; ++i) {
		insererEnTete(liste3, &i);
	}
	for (int i = 0; i < 5; ++i) {
		insererEnTete(liste4, &i);
	}
	printf("Les listes sont égales : %d\n", sontEgales(liste3, liste4));
	for (int i = 5; i >= 0; --i) {
		insererEnTete(liste5, &i);
	}
	printf("Les listes sont égales : %d\n", sontEgales(liste3, liste5));
	Liste *liste6 = initialiser();
	for (int i = 0; i < 4; ++i) {
		insererEnTete(liste6, &i);
	}

	printf("Les listes sont égales : %d\n", sontEgales(liste3, liste6));

	//supprimerSelonCritere(liste, (bool (*)(size_t, const Info *)) impairOuindex);
	Info info = 0;
	Liste* liste2 = initialiser();
	insererEnTete(liste2, &info);
	supprimerEnQueue(liste2, &info);
	afficher(liste2, FORWARD);
	vider(liste, 1);
	afficher(liste, FORWARD);
	vider(liste, 0);
	vider(liste2, 0);
	free(liste);
	free(liste2);
   */
	return EXIT_SUCCESS;

}
