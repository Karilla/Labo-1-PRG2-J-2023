/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      : Eva Ray, Benoît Delay, Rschel Tranchida
 Date creation  : 26.04.2023

 Description    : Ce programme permet de simuler des listes doublement chaînées non
 circulaires. Une liste doublement chaînée est une structure qui permet de
 représenter une liste de données ordonnées en utilisant une structure de maillon.
 Un maillon contient une valeur ainsi que deux pointeurs, un vers le maillon
 suivant et un vers le maillon précédent. Ce sont ces deux pointeurs qui
 permettent de mettre en place le chaînage et ainsi de créer une liste doublement
 chaînée. On appelle le premier maillon de la liste la "tête" et le dernier
 maillon de la liste la "queue". Ces listes ne sont pas circulaires, car on ne
 considère pas que la tête de la liste est le maillon suivant la queue de la liste.
 Ce fichier contient la définition de toutes les fonctions déclarées dans le
 header listes_dynamiques.h permettant la manipulation et la gestion des listes
 doublement chaînées non circulaires.

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 9.0
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include <stdlib.h>
#include <stdio.h>

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
		// On initialise l'élément actuel (courant) avec le premier élément à
		// parcourir, queue pour BACKWARD et tete pour FORWARD
		Element *courant = mode == FORWARD ? liste->tete : liste->queue;
		//tant que courant n'est pas nul, i.e on a pas fini de parcourir la liste
		while (courant != NULL) {
			printf("%d", courant->info);
			// on met à jour courant avec la valeur suivante en fonction du mode
			switch (mode) {
				case FORWARD : // on prend l'élément suivant
					courant = courant->suivant;
					break;
				case BACKWARD : // on pend l'élément précédent
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
	// si la liste est vide on retourne le Status LISTE_VIDE, on ne peut rien
	// supprimer
	if (estVide(liste)) {
		return LISTE_VIDE;
	}
	Element* temp = liste->tete;
	// si info n'est pas NULL, on lui donne la valeur de l'élément que l'on supprime
	if (info) {
		*info = liste->tete->info;
	}

	// s'il n'y a qu'un seul élément
	if (liste->tete->suivant == NULL) {
		liste->queue = NULL; // on met la queue à NULL
	} else { // sinon on met le précédent de l'élément suivant à NULL
		liste->tete->suivant->precedent = NULL;

	}
	// la tete doit pointer sur l'élément suivant (le nouveau premier élément)
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
	// si la liste est vide on retourne le Status LISTE_VIDE, on ne peut rien
	// supprimer
	if (estVide(liste)) {
		return LISTE_VIDE;
	}
	Element* temp = liste->queue;
	// si info n'est pas NULL, on lui donne la valeur de l'élément que l'on supprime
	if (info) {
		*info = liste->queue->info;
	}


	// s'il n'y a qu'un seul élément
	if (liste->queue->precedent == NULL) {
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
		// on teste le critere pour savoir si l'élément à d'indice indice et de
		// valeur info est à supprimer
		if (critere(indice, (const Info *) &(courant->info))) {

			// si c'est le premier élément
			if (courant->precedent == NULL) {
				// on supprime l'élément en tête
				supprimerEnTete(liste, &(courant->info));
				// l'élément courant pointe sur la nouvelle tête
				courant = liste->tete;

				// si c'est le dernier élément
			} else if (courant->suivant == NULL) {
				// on supprime en queue
				supprimerEnQueue(liste, &(courant->info));
				return; // on return car on est au dernier élément
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
	//si la taille est plus petite ou égale à la position, la position est
	// invalide, on ne supprime rien et on return
	if (taille <= position) {
		return;
	}

	Info info = 0;
	for (size_t i = 0; i < taille - position; i++) {
		supprimerEnQueue(liste, NULL);
	}

}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste1 et liste2 sont égales (au sens mêmes infos et infos
// apparaissant dans le même ordre), false sinon.
// N.B. 2 listes vides sont considérées comme égales.
bool sontEgales(const Liste *liste1, const Liste *liste2) {
	//si les listes n'ont pas la même taille, elle ne sont pas égales et on return
	// false
	if (longueur(liste1) != longueur(liste2)) {
		return false;
	}
	//sinon on compare élément par élément
	Element *courant1 = liste1->tete;
	Element *courant2 = liste2->tete;
	while (courant1 != NULL) {
		//si deux éléments ne sont pas égaux on return false
		if (courant1->info != courant2->info) {
			return false;
		}
		courant1 = courant1->suivant;
		courant2 = courant2->suivant;
	}
	// si on a parcouru tous les éléments et qu'on a pas return, ils étaient tous
	// égaux, on return true
	return true;
}
