/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main
 Auteur(s)      : <A compléter>
 Date creation  : 26.04.2023

 Description    : <A compléter>

 Remarque(s)    : <A compléter>

 Compilateur    : Mingw-w64 gcc 9.0
 -----------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include "listes_dynamiques.h"

bool impairOuindex(size_t i, Info *info) {
	if (i % 2 == 0 || (*info > 1 && *info < 4)) {
		return false;
	} else {
		return true;
	}
}

void remplirListe(Liste *liste, int taille) {
	for (int i = 0; i < taille; ++i) {
		insererEnTete(liste, &i);
	}
}

int main(void) {

	Liste *liste = initialiser();
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
	/*for(int i = 0; i < 5; ++i){
		insererEnQueue(liste2, &i);
	}
	afficher(liste2, FORWARD);*/

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
	supprimerSelonCritere(liste, (bool (*)(size_t, const Info *)) impairOuindex);
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
	return EXIT_SUCCESS;

}
