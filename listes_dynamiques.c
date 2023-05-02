/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      : Eva Ray, Benoît Delay, Rachel Tranchida
 Date creation  : 26.04.2023

 Description    : Ce programme permet de simuler des listes doublement chaînées non
 circulaires. Une liste doublement chaînée est une structure qui permet de
 représenter une liste de données ordonnées en utilisant une structure de maillon.
 Un maillon contient une valeur ainsi que deux pointeurs, un vers le maillon
 suivant et un vers le maillon précédent. Ce sont ces deux pointeurs qui
 permettent de mettre en place le chaînage et ainsi de créer une liste doublement
 chaînée. On appelle le premier maillon de la liste la "tête" et le dernier
 maillon de la liste la "queue". Ces listes ne sont pas circulaires, car on ne
 considère pas que la tête de la liste est le maillon suivant la queue de la liste
 (et vice-versa).
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

// ------------------------------------------------------------------------------
// Initialisation de la liste.
// N.B. Cette fonction doit obligatoirement être utilisée pour se créer une liste
// car elle garantit la mise à NULL des champs tete et queue de la liste
// Renvoie NULL en cas de mémoire insuffisante
Liste *initialiser(void) {
	Liste *liste = (Liste *) malloc(sizeof(Liste));
   // On vérifie que la mémoire soit suffisante pour créer la nouvelle liste
	if (liste == NULL) {
		return NULL;
	}
   // La tête et la queue d'une liste vide sont des pointeurs nuls
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
// Renvoie le nombre d'éléments d'une liste.
size_t longueur(const Liste *liste) {
	// On traite le cas d'une liste vide séparemment
	if (estVide(liste)) {
		return 0;
	}
	Element *courant = liste->tete;
	size_t longueur = 0;
	// On parcourt la liste entière et on incrémente la variable "longueur" à chaque
	// nouveau maillon rencontré.
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
	Element *nouvelElement = (Element *) malloc(sizeof(Element));
	// On vérifie que la mémoire soit suffisante pour créer le nouvel Element
	if (nouvelElement == NULL) {
		return MEMOIRE_INSUFFISANTE;
	}
	nouvelElement->info = *info;
	// Le nouvel élément devient la tête de la liste, le maillon suivant est donc
	// la tête de liste actuelle et le maillon précédent doit être le pointeur nul
	nouvelElement->suivant = liste->tete;
	nouvelElement->precedent = NULL;
	// Si la liste n'est pas vide, la tête actuelle devient le second élément et
	// son attribut "precedent" doit donc pointer sur le nouvel élément et non plus
	// être NULL
	if (!estVide(liste)) {
		liste->tete->precedent = nouvelElement;
	} else {
		// si la liste est vide, le nouvel élément doit être à la fois la tête et la
		// queue de la liste
		liste->queue = nouvelElement;
	}
	// on met le nouvel élément en tête de liste
	liste->tete = nouvelElement;
	return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en queue de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément.
Status insererEnQueue(Liste *liste, const Info *info) {
	Element *nouvelElement = (Element *) malloc(sizeof(Element));
	// On vérifie que la mémoire soit suffisante pour créer le nouvel Element
	if (nouvelElement == NULL) {
		return MEMOIRE_INSUFFISANTE;
	}
	nouvelElement->info = *info;
	// Le nouvel élément devient la queue de la liste, le maillon suivant est donc
	// le pointeur nul et le maillon précédent doit être la queue de liste actuelle
	nouvelElement->suivant = NULL;
	nouvelElement->precedent = liste->queue;
	// Si la liste n'est pas vide, la queue actuelle devient l'avant-dernier
	// élément et son attribut "suivant" doit donc pointer sur le nouvel élément
	// et non plus être NULL
	if (!estVide(liste)) {
		liste->queue->suivant = nouvelElement;
	} else {
		// si la liste est vide, le nouvel élément doit être à la fois la tête et la
		// queue de la liste
		liste->tete = nouvelElement;
	}
	//nouvelElement->precedent = liste->queue;
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
		// on teste le critere pour savoir si l'élément à l'indice indice et de
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
	// on supprime en queue jusqu'à la position que l'on veut supprimer comprise
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
	// si on a parcouru tous les éléments et qu'on n'a pas return, cela veut dire
   // qu'ils sont tous égaux, on return true
	return true;
}
