/*
 -----------------------------------------------------------------------------------
 Nom du fichier : fonctions_de_tests.c
 Auteur(s)      : <A compléter>
 Date creation  : 30.04.2023

 Description    : <A compléter>

 Remarque(s)    : <A compléter>

 Compilateur    : Mingw-w64 gcc 9.0
 -----------------------------------------------------------------------------------
*/

#include "fonctions_de_tests.h"
#include "listes_dynamiques.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

bool impairOuEntre1et4(size_t i, Info *info) {
	if (i % 2 == 1 || (*info > 1 && *info < 4)) {
		return true;
	}
	return false;
}

void remplirSelonCritere(Liste *liste, size_t taille, bool (*critere)(size_t
																							 position,
																							 const Info *info)) {
	Info info;
	for (size_t i = 0; i < taille; ++i) {
		info = (Info) i;
		if (!critere(i, &info))
			insererEnQueue(liste, &info);
	}
}

void remplirListe(Liste *liste, size_t taille) {
	Info info;
	for (size_t i = 0; i < taille; ++i) {
		info = (Info) i;
		insererEnQueue(liste, &info);
	}
}

// trouver un truc pour vérifier en cas de mémoire insuffisante
bool testInitialiser(void) {
	Liste *liste = initialiser();
	if (liste->queue == NULL && liste->tete == NULL) {
		free(liste);
		return true;
	}
	free(liste);
	return false;
}

// le test d'inserererEnTete doit être fait avant celui de estVide car on utilise insererEnTete dans cette fct
bool testEstVide(void) {
	Liste *liste = initialiser();
	bool testReussi = true;
	if (!estVide(liste)) { // on teste si une liste vide est bien vide
		printf("testEstVide: liste vide n'est pas vide\n");
		testReussi = false;
	} else {
		Info info = 1;
		insererEnTete(liste, &info);
		if (estVide(liste)) { // on teste si une liste non vide est bien non vide
			printf("testEstVide: liste non vide est vide\n");
			testReussi = false;
		}
	}
	vider(liste, 0);
	free(liste);
	return testReussi;
}

// le test d'inserererEnTete doit être fait avant celui de longueur car on utilise insererEnTete dans cette fct
// le test d'inserererEnTete doit être fait avant celui de longueur car on utilise insererEnTete dans cette fct
bool testLongueur(void) {
	Liste *liste = initialiser();
	bool testReussi = true;
	for (size_t i = 1; i < 3; i++) {
		Info info = (int) i;
		insererEnTete(liste, &info);
		if (longueur(liste) !=
			 i) { // on vérifie que la longueur de la liste est bien égale au nombre d'éléments insérés
			printf("%s : longueur attendue %zu, actuelle %lld\n", __func__, i, longueur
				(liste));
			testReussi = false;
		}
	}
//	if (longueur(liste) != 0) { // on vérifie que la longueur d'une liste vide est 0
//		printf("testLongueur: longueur attendue 0, actuelle %lld\n", longueur(liste));
//		testReussi = false;
//	} else {
//		Info infoPremierElement = 1;
//		insererEnTete(liste, &infoPremierElement);
//		if (longueur(liste) !=
//			 1) { // on vérifie que la longueur d'une liste de 1 élément est 1
//			testReussi = false;
//		} else {
//			Info infoDeuxiemeElement = 2;
//			insererEnTete(liste, &infoDeuxiemeElement);
//			if (longueur(liste) !=
//				 2) { // on vérifie que la longueur d'une liste de 2 éléments est 2 (cas général)
//				testReussi = false;
//			}
//		}
//	}
	vider(liste, 0);
	free(liste);
	return testReussi;
}

void testAfficher(void) {

}

bool testInsererEnTete(void) {
	bool testReussi = true;
	Liste *liste = initialiser();
	Info info = 1;
	insererEnTete(liste, &info);
	if (liste->tete->info != info) {
		printf("testInsererEnTete: info attendue %d, actuelle %d\n", info,
				 liste->tete->info);
		testReussi = false;
	}
	vider(liste, 0);
	free(liste);
	return testReussi;
}

bool testInsererEnQueue(void) {
	bool testReussi = true;
	Liste *liste = initialiser();
	Info info = 1;
	insererEnQueue(liste, &info);
	if (liste->queue->info != info) {
		printf("testInsererEnQueue: info attendue %d, actuelle %d\n", info,
				 liste->queue->info);
		testReussi = false;
	}
	vider(liste, 0);
	free(liste);
	return testReussi;
}

// tester insererEnTete avant
void testSupprimerEnTete(void) {
	Liste *liste = initialiser();
	bool testReussi = true;
	Info infoPremierElement = 1;
	Info infoDeuxiemeElement = 2;
	Info infoRetour;
	if (supprimerEnTete(liste, NULL) !=
		 LISTE_VIDE)
		testReussi = false; // on vérifie le cas d'une liste vide
	insererEnTete(liste, &infoPremierElement);
	supprimerEnTete(liste, &infoRetour);
	assert(estVide(liste)); // on vérifie pour une liste de 1 élément
	assert(infoPremierElement == infoRetour);
	insererEnTete(liste, &infoPremierElement);
	insererEnTete(liste, &infoDeuxiemeElement);
	supprimerEnTete(liste, &infoRetour);
	assert(liste->tete->info ==
			 infoPremierElement); // on vérifie pour une liste de 2 éléments (cas général)
	assert(infoDeuxiemeElement == infoRetour);
	vider(liste, 0);
	free(liste);
}

void testSupprimerEnQueue(void) {
	Liste *liste = initialiser();
	Info infoPremierElement = 1;
	Info infoDeuxiemeElement = 2;
	Info infoRetour;
	assert(supprimerEnQueue(liste, NULL) ==
			 LISTE_VIDE); // on vérifie le cas d'une liste vide
	insererEnTete(liste, &infoPremierElement);
	supprimerEnQueue(liste, &infoRetour);
	assert(estVide(liste)); // on vérifie pour une liste de 1 élément
	assert(infoPremierElement == infoRetour);
	insererEnTete(liste, &infoPremierElement);
	insererEnTete(liste, &infoDeuxiemeElement);
	supprimerEnQueue(liste, &infoRetour);
	assert(liste->queue->info ==
			 infoDeuxiemeElement); // on vérifie pour une liste de 2 éléments (cas général)
	assert(infoPremierElement == infoRetour);
	vider(liste, 0);
	free(liste);
}

bool testSupprimerSelonCritere(void) {
	Liste *liste = initialiser();
	Liste *listeAttendue = initialiser();

	remplirListe(liste, 5);
	remplirSelonCritere(listeAttendue, 5, (bool (*)(size_t, const Info *))
		impairOuEntre1et4);
	supprimerSelonCritere(liste, (bool (*)(size_t, const Info *)) impairOuEntre1et4);

	if (!sontEgales(liste, listeAttendue)) {
		printf("%s: listeAttendue et liste ne sont pas "
				 "egales\n", __func__);
		printf("listeAttendue: ");
		afficher(listeAttendue, FORWARD);
		printf("liste recue: ");
		afficher(liste, FORWARD);
		return false;
	}
	return true;
}


// j'utilise pas estVide car testEstVide utilise Vider
bool testVider(void) {
	bool testReussi = true;
	Liste *liste = initialiser();
	Liste *listeAttendue = initialiser();
//	remplirListe(liste, 5);
//	vider(liste, 0);
//	assert(sontEgales(liste, listeAttendue));
//	remplirListe(liste, 5);
//	remplirListe(listeAttendue, 1);
//	vider(liste, 1);
//	if(!sontEgales(liste, listeAttendue)) {
//		printf("testVider: listeAttendue et liste ne sont pas égales pour vider "
//				 "depuis l'élément 1\n");
//		testReussi = false;
//	}
//	vider(listeAttendue, 0);
//	vider(liste, 0);
//	remplirListe(liste, 5);
//	remplirListe(listeAttendue, 2);
//	vider(liste, 2);
	const size_t TAILLE_REMPLISSAGE = 5;
	for (size_t i = 0; i < 3; i++) {

		remplirListe(liste, TAILLE_REMPLISSAGE);
		remplirListe(listeAttendue, i);
		vider(liste, i);
		if (!sontEgales(liste, listeAttendue)) {
			printf("%s: listeAttendue et liste ne sont pas égales pour vider "
					 "depuis l'élément %zu\n", __func__, i);
			testReussi = false;
		}
		vider(listeAttendue, 0);
		vider(liste, 0);
	}


	free(liste);
	free(listeAttendue);
	return testReussi;
}

bool testSontEgales(void) {
	printf("Fonction de test pour la fonction sontEgales....\n");
	bool testOk = true;
	Liste *liste1 = initialiser();
	Liste *liste2 = initialiser();

	printf("Test quand les 2 listes sont vides: ");
	//Test si les 2 listes sont vides la fonction nous renvoie true
	if (sontEgales(liste1, liste2) != true) {
		printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
		testOk = false;
	} else {
		printf(ANSI_COLOR_GREEN"reussite\n"ANSI_COLOR_RESET);
	}


	//Test si la liste 1 est plus grande que la 2 renvoie false
	printf("Test quand la liste 1 est plus grande que la liste 2: ");
	Info valeur = 10;
	insererEnTete(liste1, &valeur);
	if (sontEgales(liste1, liste2) != false) {
		printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
		testOk = false;
	} else {
		printf(ANSI_COLOR_GREEN"reussite\n"ANSI_COLOR_RESET);
	}

	//Test si la liste 1 et la liste 2 sont egales et renvoie true
	printf("Test quand les 2 listes sont bien egales: ");
	insererEnTete(liste2, &valeur);
	if (sontEgales(liste1, liste2) != true) {
		printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
		testOk = false;
	} else {
		printf(ANSI_COLOR_GREEN"reussite\n"ANSI_COLOR_RESET);
	}

	//Test quand liste 1 et liste 2 ont la meme taille mais pas les meme elements
	printf(
		"Test quand les 2 listes ont la meme taille mais pas les memes elements: ");
	supprimerEnQueue(liste2, NULL);
	valeur = 20;
	insererEnTete(liste2, &valeur);
	if (sontEgales(liste1, liste2) != false) {
		printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
		testOk = false;
	} else {
		printf(ANSI_COLOR_GREEN"reussite\n"ANSI_COLOR_RESET);
	}

	//Test quand la liste 2 est plus grande que la liste 1 renvoie false
	printf("Test quand la liste 2 est plus grande que la liste 1: ");
	insererEnTete(liste2, &valeur);
	if (sontEgales(liste1, liste2) != false) {
		printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
		testOk = false;
	} else {
		printf(ANSI_COLOR_GREEN"success\n"ANSI_COLOR_RESET);
	}

	vider(liste1, 0);
	vider(liste2, 0);

	free(liste2);
	free(liste1);
	return testOk;
}
