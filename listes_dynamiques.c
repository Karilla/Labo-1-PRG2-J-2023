/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      : Eva Ray, Benoît Delay, Rachel Tranchida
 Date creation  : 26.04.2023

 Description    : Ce programme permet de simuler des listes doublement chaînées non
                  circulaires. Une liste doublement chaînée est une structure qui
                  permet de représenter une liste de données ordonnées en utilisant
                  une structure de maillon. Un maillon contient une valeur ainsi que
                  deux pointeurs; un vers le maillon suivant et un vers le maillon
                  précédent. Ce sont ces deux pointeurs qui permettent de mettre en
                  place le chaînage et ainsi de créer une liste doublement chaînée.
                  On appelle le premier maillon de la liste la "tête" et le dernier
                  maillon de la liste la "queue". Ces listes ne sont pas circulaires,
                  car on ne considère pas que la tête de la liste est le maillon
                  suivant la queue de la liste (et vice-versa).
                  Ce fichier contient la définition de toutes les fonctions
                  déclarées dans le header listes_dynamiques.h permettant la
                  manipulation et la gestion des listes doublement chaînées non
                  circulaires.

 Remarque(s)    : Certaines fonctions renvoient un statut du type énuméré "Status"
                  défini dans le fichier listes_dynamiques. Ce statut donne une
                  information sur le déroulement de la fonction en question et peut
                  être utilisé par l'utilisateur pour implémenter un traitement
                  d'exceptions.

 Compilateur    : Mingw-w64 gcc 9.0
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include <stdlib.h>
#include <stdio.h>

Liste *initialiser(void) {
	Liste *liste = (Liste *) malloc(sizeof(Liste));
   // On vérifie que la mémoire est suffisante pour créer la nouvelle liste
	if (liste == NULL) {
		return NULL;
	}
   // La tête et la queue d'une liste vide sont des pointeurs nuls
	liste->queue = NULL;
	liste->tete = NULL;

	return liste;
}

bool estVide(const Liste *liste) {
	return liste->tete == NULL;
}

size_t longueur(const Liste *liste) {
	// On traite le cas d'une liste vide séparément
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

void afficher(const Liste *liste, Mode mode) {
	printf("[");
	if (!estVide(liste)) {
		// On initialise l'élément actuel (courant) avec le premier élément à
		// parcourir, queue pour BACKWARD et tete pour FORWARD
		Element *courant = mode == FORWARD ? liste->tete : liste->queue;
		// Tant que courant n'est pas nul, i.e on n'a pas fini de parcourir la liste
		while (courant != NULL) {
			printf("%d", courant->info);
			// On met à jour courant avec la valeur suivante en fonction du mode
			switch (mode) {
				case FORWARD : // On prend l'élément suivant
					courant = courant->suivant;
					break;
				case BACKWARD : // On prend l'élément précédent
					courant = courant->precedent;
					break;
				default:
					return;
			}
			if (courant != NULL) {
				printf(",");
			}
		}
	}
	printf("]\n");
}

Status insererEnTete(Liste *liste, const Info *info) {
	Element *nouvelElement = (Element *) malloc(sizeof(Element));
	// On vérifie que la mémoire est suffisante pour créer le nouvel Element
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
		// Si la liste est vide, le nouvel élément doit être à la fois la tête et la
		// queue de la liste
		liste->queue = nouvelElement;
	}
	// On met le nouvel élément en tête de liste
	liste->tete = nouvelElement;
	return OK;
}

Status insererEnQueue(Liste *liste, const Info *info) {
	Element *nouvelElement = (Element *) malloc(sizeof(Element));
	// On vérifie que la mémoire est suffisante pour créer le nouvel Element
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
		// Si la liste est vide, le nouvel élément doit être à la fois la tête et la
		// queue de la liste
		liste->tete = nouvelElement;
	}
	// On met le nouvel élément en queue de liste
	liste->queue = nouvelElement;
	return OK;
}

Status supprimerEnTete(Liste *liste, Info *info) {
	// Si la liste est vide on retourne le Status LISTE_VIDE, il n'y a rien à
	// supprimer
	if (estVide(liste)) {
		return LISTE_VIDE;
	}
	Element *temp = liste->tete;
	// Si info n'est pas NULL, on lui donne la valeur de l'élément que l'on supprime
	if (info) {
		*info = liste->tete->info;
	}

	// S'il n'y a qu'un seul élément
	if (liste->tete->suivant == NULL) {
		liste->queue = NULL; // On met la queue à NULL
	} else { // Sinon on met le précédent de l'élément suivant à NULL
		liste->tete->suivant->precedent = NULL;

	}
	// La tete doit pointer sur l'élément suivant (le nouveau premier élément)
	liste->tete = liste->tete->suivant;
	free(temp);
	return OK;
}

Status supprimerEnQueue(Liste *liste, Info *info) {
	// Si la liste est vide on retourne le Status LISTE_VIDE, il n'y a rien
	// à supprimer
	if (estVide(liste)) {
		return LISTE_VIDE;
	}
	Element *temp = liste->queue;
	// Si info n'est pas NULL, on lui donne la valeur de l'élément que l'on supprime
	if (info) {
		*info = liste->queue->info;
	}
	// S'il n'y a qu'un seul élément
	if (liste->queue->precedent == NULL) {
		liste->tete = NULL; // On met la tête à NULL
	} else { // Sinon, on met le suivant de l'élément précédent à NULL
		liste->queue->precedent->suivant = NULL;
	}
	liste->queue = liste->queue->precedent;
	free(temp);
	return OK;
}

void supprimerSelonCritere(Liste *liste,
									bool (*critere)(size_t position, const Info *info)) {
	Element *courant = liste->tete;
	Element *suivant;
	size_t indice = 0;
	while (courant != NULL) {
		// On teste le critère pour savoir si l'élément à l'indice indice et de
		// valeur info est à supprimer
		if (critere(indice, (const Info *) &(courant->info))) {

			// Si c'est le premier élément
			if (courant->precedent == NULL) {
				// On supprime l'élément en tête
				supprimerEnTete(liste, &(courant->info));
				// L'élément courant pointe sur la nouvelle tête
				courant = liste->tete;
				// Si c'est le dernier élément
			} else if (courant->suivant == NULL) {
				// On supprime en queue
				supprimerEnQueue(liste, &(courant->info));
				return; // On retourne, car on est au dernier élément
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

void vider(Liste *liste, size_t position) {

	size_t taille = longueur(liste);
	// Si la taille est plus petite ou égale à la position, la position est
	// invalide, on ne supprime rien et on retourne
	if (taille <= position) {
		return;
	}
	// On supprime en queue jusqu'à la position que l'on veut supprimer comprise
	for (size_t i = 0; i < taille - position; i++) {
		supprimerEnQueue(liste, NULL);
	}
}

bool sontEgales(const Liste *liste1, const Liste *liste2) {
	// Si les listes n'ont pas la même taille, elles ne sont pas égales et on retourne
	// false
	if (longueur(liste1) != longueur(liste2)) {
		return false;
	}
	// Sinon on compare élément par élément
	Element *courant1 = liste1->tete;
	Element *courant2 = liste2->tete;
	while (courant1 != NULL) {
		// Si deux éléments ne sont pas égaux on retourne false
		if (courant1->info != courant2->info) {
			return false;
		}
		courant1 = courant1->suivant;
		courant2 = courant2->suivant;
	}
	// Si on a parcouru tous les éléments et qu'on n'a encore rien retourné, cela veut dire
   // qu'ils sont tous égaux, on retourne true
	return true;
}
