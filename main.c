/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Rachel Tranchida, Benoît Delay, Eva Ray
 Date creation  : 26.04.2023

 Description    : Fichier de test des fonctions de la librairie listes_dynamiques.
 						Chaque fonction de la librairie à tester a une fonction de
 						test associée.
 						Les fonctions de tests retournent toutes un bool qui vaut true
 						si le test est un succès et false sinon et ne prennent aucun
 						paramètre. Dans le main, toutes les fonctions de tests sont
 						stockées dans un tableau de pointeurs sur des fonctions ne
 						prenant aucun paramètre et retournant un bool. Chaque fonction
 						imprime son nom puis, s'il y a des erreurs, la nature de
 						l'erreur pour faciliter le débuggage. Pour chaque fonction, dans
 						le main, on imprime si le test est un échec ou une réussite
 						selon le retour de la fonction de test. Enfin, on utilise un bool
 						pour imprimer à la fin des tests s'ils ont tous passé ou s'il y
 						a encore des problèmes.


 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 9.0
 -----------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include "listes_dynamiques.h"

bool testInitialiser(void);

bool testEstVide(void);

bool testLongueur(void);

bool testInsererEnTete(void);

bool testInsererEnQueue(void);

bool testSupprimerEnTete(void);

bool testSupprimerEnQueue(void);

bool testSupprimerSelonCritere(void);

bool testVider(void);

bool testSontEgales(void);

bool impairOuEntre1et4(size_t i, const Info *info);

void remplirSelonCritere(Liste *liste, size_t taille, bool (*critere)(size_t
																							 position,
																							 const Info
																							 *info));

void remplirListe(Liste *liste, size_t taille);

int main(void) {

	bool (* const fonctionsATester[])(void) = {testInitialiser, testVider,
													 testInsererEnTete,
													testInsererEnQueue, testLongueur,
													testEstVide, testSupprimerEnTete,
													testSupprimerEnQueue,
													testSupprimerSelonCritere, testSontEgales};
	bool testReussis = true;
	for (size_t i = 0; i < sizeof(fonctionsATester) / sizeof(bool (*)(void)); i++) {
		bool reussite = fonctionsATester[i]();
		printf("%s\n", reussite ? "reussi" : "echec");
		testReussis &= reussite;
	}

	printf("%s", testReussis ? "Tous les tests passent." :
	"Les tests ne passent pas");

	return EXIT_SUCCESS;
}

// FONCTIONS UTILISEES DANS LES TESTS

// Fonction d'exemple utilisée comme critère pour tester supprimerSelonCritere
// Fonction qui teste si la position est impaire ou si la valeur contenue à cette
// position est entre 1 et 4
bool impairOuEntre1et4(size_t i, const Info *info) {

	return i % 2 == 1 || (*info > 1 && *info < 4);
}

// Fonction qui permet de remplir une liste selon un critère choisi
void remplirSelonCritere(Liste *liste, size_t taille,
								 bool(*critere)(size_t position, const Info *info)) {
	Info info;
	for (size_t i = 0; i < taille; ++i) {
		info = (Info) i;
		if (!critere(i, &info))
			insererEnQueue(liste, &info);
	}
}

// Fonction qui permet de remplir une liste chaînée avec un nombre de maillons choisi
void remplirListe(Liste *liste, size_t taille) {
	Info info;
	for (size_t i = 0; i < taille; ++i) {
		info = (Info) i;
		insererEnQueue(liste, &info);
	}
}

// FONCTIONS DE TESTS

bool testInitialiser(void) {
	printf("%s:\n", __func__);

	Liste *liste = initialiser();
	if (liste->queue == NULL && liste->tete == NULL) {
		free(liste);
		return true;
	}
	free(liste);
	return false;
}

bool testEstVide(void) {
	printf("%s:\n", __func__);
	Liste *liste = initialiser();
	bool testReussi = true;
	if (!estVide(liste)) { // on teste si une liste vide est bien vide
		printf("\tErreur: liste vide n'est pas vide\n");
		testReussi = false;
	} else {
		Info info = 1;
		insererEnTete(liste, &info);
		if (estVide(liste)) { // on teste si une liste non vide est bien non vide
			printf("\tErreur: liste non vide est vide\n");
			testReussi = false;
		}
	}
	vider(liste, 0);
	free(liste);
	return testReussi;
}

bool testLongueur(void) {
	printf("%s:\n", __func__);
	Liste *liste = initialiser();
	bool testReussi = true;
	for (size_t i = 1; i < 3; i++) {
		Info info = (int) i;
		insererEnTete(liste, &info);
		if (longueur(liste) != i) { // on vérifie que la longueur de la liste est
			// bien égale au nombre d'éléments insérés
			printf("\tErreur : longueur attendue %zu, actuelle %zu\n", i, longueur
				(liste));
			testReussi = false;
		}
	}
	vider(liste, 0);
	free(liste);
	return testReussi;
}

bool testInsererEnTete(void) {
	printf("%s:\n", __func__);
	bool testReussi = true;
	Liste *liste = initialiser();
	Info info = 1;
	insererEnTete(liste, &info);
	if (liste->tete->info != info) {
		printf("\tErreur : info attendue %d, actuelle %d\n", info,
				 liste->tete->info);
		testReussi = false;
	}
	vider(liste, 0);
	free(liste);
	return testReussi;
}

bool testInsererEnQueue(void) {
	printf("%s:\n", __func__);
	bool testReussi = true;
	Liste *liste = initialiser();
	Info info = 1;
	insererEnQueue(liste, &info);
	if (liste->queue->info != info) {
		printf("\tErreur : info attendue %d, actuelle %d\n", info,
				 liste->queue->info);
		testReussi = false;
	}
	vider(liste, 0);
	free(liste);
	return testReussi;
}

bool testSupprimerEnTete(void) {
	printf("%s:\n", __func__);
	Liste *liste = initialiser();
	bool testReussi = true;
	Info infoPremierElement = 1;
	Info infoDeuxiemeElement = 2;
	Info infoRetour;
	if (supprimerEnTete(liste, NULL) != LISTE_VIDE) { // on vérifie le cas d'une
		// liste vide
		printf("\tErreur: le cas de la liste vide n'est pas traite correctement.\n");
		testReussi = false;
	} else {
		insererEnTete(liste, &infoPremierElement);
		supprimerEnTete(liste, &infoRetour);
		if (!estVide(liste)) { // on vérifie pour une liste de 1 élément
			printf("\tErreur: le cas de la liste de taille 1 n'est pas traite "
					 "correctement.\n");
			testReussi = false;
		} else {
			if (infoPremierElement != infoRetour) {
				printf("\tErreur: le parametre de retour \"info\" ne contient pas "
						 "la valeur attendue. Valeur attendue: %d, Valeur actuelle: %d\n",
						 infoPremierElement, infoRetour);
				testReussi = false;
			} else {
				insererEnTete(liste, &infoPremierElement);
				insererEnTete(liste, &infoDeuxiemeElement);
				supprimerEnTete(liste, &infoRetour);
				if (liste->tete->info != infoPremierElement) {
					printf("\tErreur: le cas de la liste de taille 2 n'est pas traite "
							 "correctement.\n");
					testReussi = false;
				} // on vérifie pour une liste de 2 éléments (cas général)
			}
		}
	}
	vider(liste, 0);
	free(liste);
	return testReussi;
}

bool testSupprimerEnQueue(void) {
	printf("%s:\n", __func__);
	Liste *liste = initialiser();
	Info infoPremierElement = 1;
	Info infoDeuxiemeElement = 2;
	Info infoRetour;
	bool testReussi = true;
	if (supprimerEnQueue(liste, NULL) !=
		 LISTE_VIDE) { // on vérifie le cas d'une liste vide
		printf("\tErreur: le cas de la liste vide n'est pas traite correctement.\n");
		testReussi = false;
	} else {
		insererEnTete(liste, &infoPremierElement);
		supprimerEnQueue(liste, &infoRetour);
		if (!estVide(liste)) { // on vérifie pour une liste de 1 élément
			printf("\tErreur: le cas de la liste de taille 1 n'est pas traite "
					 "correctement.\n");
			testReussi = false;
		} else {
			if (infoPremierElement != infoRetour) {
				printf("\tErreur: le parametre de retour \"info\" ne contient pas "
						 "la valeur attendue. Valeur attendue: %d, Valeur actuelle: %d\n",
						 infoPremierElement, infoRetour);
				testReussi = false;
			} else {
				insererEnTete(liste, &infoPremierElement);
				insererEnTete(liste, &infoDeuxiemeElement);
				supprimerEnQueue(liste, &infoRetour);
				if (liste->queue->info != infoDeuxiemeElement) {
					printf("\tErreur: le cas de la liste de taille 2 n'est pas traite "
							 "correctement.\n");
					testReussi = false;
				}// on vérifie pour une liste de 2 éléments (cas général)
			}
		}
	}
	vider(liste, 0);
	free(liste);
	return testReussi;
}

bool testSupprimerSelonCritere(void) {
	printf("%s:\n", __func__);
	Liste *liste = initialiser();
	Liste *listeAttendue = initialiser();
	bool testReussi = true;
	remplirListe(liste, 5);
	remplirSelonCritere(listeAttendue, 5, (bool (*)(size_t, const Info *))
		impairOuEntre1et4);
	supprimerSelonCritere(liste, (bool (*)(size_t, const Info *)) impairOuEntre1et4);

	if (!sontEgales(liste, listeAttendue)) {
		printf("\tErreur: liste attendue et liste ne sont pas egales\n");
		printf("\t\tliste attendue: ");
		afficher(listeAttendue, FORWARD);
		printf("\t\tliste recue: ");
		afficher(liste, FORWARD);
		testReussi = false;
	}
	vider(liste, 0);
	vider(listeAttendue, 0);
	free(liste);
	free(listeAttendue);
	return testReussi;
}

bool testVider(void) {
	printf("%s:\n", __func__);
	bool testReussi = true;
	Liste *liste = initialiser();
	Liste *listeAttendue = initialiser();

	const size_t TAILLE_REMPLISSAGE = 5;
	for (size_t i = 0; i < 3; i++) {
		remplirListe(liste, TAILLE_REMPLISSAGE);
		remplirListe(listeAttendue, i);
		vider(liste, i);
		if (!sontEgales(liste, listeAttendue)) {
			printf("\tErreur: listeAttendue et liste ne sont pas égales pour vider "
					 "depuis l'élément %zu\n", i);
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
	printf("%s:\n", __func__);
	bool testReussi = true;
	Liste *liste1 = initialiser();
	Liste *liste2 = initialiser();

	if (!sontEgales(liste1, liste2)) {
		printf("\tErreur: Mauvais resultat quand les deux listes sont vides\n");
		testReussi = false;
	}
	//Teste si la liste 1 est plus grande que la 2 renvoie false
	Info valeur = 10;
	insererEnTete(liste1, &valeur);
	if (sontEgales(liste1, liste2)) {
		printf("\tErreur: Quand liste 1 plus grande que liste 2:\n");
		testReussi = false;
	}
	//Teste si la liste 1 et la liste 2 sont égales et renvoie true
	insererEnTete(liste2, &valeur);
	if (!sontEgales(liste1, liste2)) {
		//printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
		printf("\tErreur: Mauvais resultat quand les deux listes sont égales\n");
		testReussi = false;
	}
	//Teste quand liste 1 et liste 2 ont la meme taille, mais pas les mêmes éléments
	supprimerEnQueue(liste2, NULL);
	valeur = 20;
	insererEnTete(liste2, &valeur);
	if (sontEgales(liste1, liste2)) {
		// printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
		printf("\tErreur : Mauvais resultats quand les listes ont la meme taille "
				 "mais pas le meme nombre d'elements.\n");
		testReussi = false;
	}

	//Teste quand la liste 2 est plus grande que la liste 1 renvoie false
	insererEnTete(liste2, &valeur);
	if (sontEgales(liste1, liste2)) {
		//printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
		printf("\tErreur: Mauvais resultat quand la liste 2 est plus grande que la "
				 "liste 1\n");
		testReussi = false;
	}

	vider(liste1, 0);
	vider(liste2, 0);
	free(liste2);
	free(liste1);
	return testReussi;
}
