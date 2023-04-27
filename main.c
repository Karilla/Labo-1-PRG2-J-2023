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

bool impairOuindex(size_t i, Info* info){
	if(i % 2 == 0){
		return false;
	}else{
		return true;
	}
}
int main(void) {

	Liste *liste = initialiser();
	Liste *liste2 = initialiser();
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
   return EXIT_SUCCESS;

}
