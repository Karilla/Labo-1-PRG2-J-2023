/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      : <A compléter>
 Date creation  : 26.04.2023

 Description    : <A compléter>

 Remarque(s)    : <A compléter>

 Compilateur    : Mingw-w64 gcc 9.0
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

Liste *initialiser(void) {
	Liste *liste = (Liste *) malloc(sizeof(Liste));
	if (liste == NULL) {
		return NULL;
	}
	liste->queue = NULL;
	liste->tete = NULL;

	return liste;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste est vide, false sinon.
bool estVide(const Liste *liste) {
	return liste->tete == NULL;
}
// ------------------------------------------------------------------------------


// ------------------------------------------------------------------------------
// Renvoie combien il y a d'éléments dans liste.
size_t longueur(const Liste *liste) {
	if (estVide(liste)) {
		return 0;
	}
	Element *courant = liste->tete;
	size_t longueur = 0;
	while (courant != NULL) {
		longueur++;
		courant = courant->suivant;
	}
	return longueur;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Affiche le contenu intégral de liste sous la forme : [info_1,info_2,...]
// Dans le cas d'une liste vide, affiche : []
// En mode FORWARD, resp. BACKWARD, l'affichage se fait en parcourant liste
// dans le sens tete -> queue, resp. queue -> tete.
void afficher(const Liste *liste, Mode mode) {
	printf("[");
	if (!estVide(liste)) {
		Element *courant = mode == FORWARD ? liste->tete : liste->queue;
		while (courant != NULL) {
			printf("%d", courant->info);
			switch (mode) {
				case FORWARD :
					courant = courant->suivant;
					break;
				case BACKWARD :
					courant = courant->precedent;
					break;
				default:
					return;
			}
			if (courant != NULL) {
				printf(",");
			}
//
		}
	}
	printf("]\n");
}

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en tête de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément.
Status insererEnTete(Liste *liste, const Info *info) {
	Element *element = (Element *) malloc(sizeof(Element));
	if (element == NULL) {
		return MEMOIRE_INSUFFISANTE;
	}
	element->info = *info;
	element->suivant = liste->tete;
	element->precedent = NULL;
	if (!estVide(liste)) {
		liste->tete->precedent = element;

	} else {
		liste->queue = element;
	}
	liste->tete = element;
	return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en queue de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément.
Status insererEnQueue(Liste *liste, const Info *info) {
	Element *nouvelElement = (Element *) malloc(sizeof(Element));
	if (nouvelElement == NULL) {
		return MEMOIRE_INSUFFISANTE;
	}
	nouvelElement->info = *info;
	nouvelElement->suivant = NULL;
	if (!estVide(liste)) {
		liste->queue->suivant = nouvelElement;

	} else {
		liste->tete = nouvelElement;
	}

	nouvelElement->precedent = liste->queue;
	liste->queue = nouvelElement;
	return OK;

}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en tête de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnTete(Liste *liste, Info *info) {
	if (estVide(liste)) {
		return LISTE_VIDE;
	}
	*info = liste->tete->info;
	Element* temp = liste->tete;

	// s'il n'y a qu'un seul élément
	if(liste->tete->suivant == NULL) {
		liste->queue = NULL; // on met la queue à NULL
	} else { // sinon on met le précédent de l'élément suivant à NULL
		liste->tete->suivant->precedent = NULL;

	}
	liste->tete = liste->tete->suivant;
	free(temp);
	return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en queue de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnQueue(Liste *liste, Info *info) {
	if (estVide(liste)) {
		return LISTE_VIDE;
	}
	Element* temp = liste->queue;

	// s'il n'y a qu'un seul élément
	if(liste->queue->precedent == NULL){
		liste->tete = NULL; // on met la tête à NULL
	} else { // sinon, on met le suivant de l'élément précédent à NULL
		liste->queue->precedent->suivant = NULL;
	}
	liste->queue = liste->queue->precedent;
	free(temp);

	return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste qui
// vérifient le critère passé en second paramètre.
// Exemple: on souhaite supprimer de la liste tous les éléments dont la position est
// impaire et pour lesquels info est compris dans un certain intervalle de valeurs
void supprimerSelonCritere(Liste *liste,
									bool (*critere)(size_t position, const Info *info)) {
	Element *courant = liste->tete;
	Element *suivant;
	size_t indice = 0;
	while (courant != NULL) {
		if (critere(indice, (const Info *) &(courant->info))) {

			if (courant->precedent == NULL) {
				supprimerEnTete(liste, &(courant->info));
				courant = liste->tete;
			} else if (courant->suivant == NULL) {
				supprimerEnQueue(liste, &(courant->info));
				return;
			} else {
				suivant = courant->suivant;
				courant->precedent->suivant = courant->suivant;
				courant->suivant->precedent = courant->precedent;

				free(courant);
				courant = suivant;
			}


		} else {
			courant = courant->suivant;
		}
		++indice;
	}

}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste
// à partir de la position position
// N.B. Vider à partir de la position 0 signifie vider toute la liste.
void vider(Liste *liste, size_t position) {

	size_t taille = longueur(liste);
	if (taille <= position) {
		return;
	}

	Info info = 0;
	for(size_t i = 0; i < taille-position; i++){
		supprimerEnQueue(liste, &info);
	}

}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste1 et liste2 sont égales (au sens mêmes infos et infos
// apparaissant dans le même ordre), false sinon.
// N.B. 2 listes vides sont considérées comme égales.
bool sontEgales(const Liste *liste1, const Liste *liste2) {
	if (liste1 == NULL || liste2 == NULL || longueur(liste1) != longueur(liste2)) {
		return false;
	}
	Element *courant1 = liste1->tete;
	Element *courant2 = liste2->tete;
	while (courant1 != NULL) {
		if (courant1->info != courant2->info) {
			return false;
		}
		courant1 = courant1->suivant;
		courant2 = courant2->suivant;
	}
	return true;
}
