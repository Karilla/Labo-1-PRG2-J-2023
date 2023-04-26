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

int main(void) {

   Liste *liste = initialiser();

   printf("Est-ce que la liste est vide : %d \n", estVide(liste));

   for(int i = 0; i < 5; ++i){
      insererEnTete(liste, &i);
   }

   printf("taille liste: %zu\n", longueur(liste));

   afficher(liste, FORWARD);
   afficher(liste, BACKWARD);
   return EXIT_SUCCESS;
}
