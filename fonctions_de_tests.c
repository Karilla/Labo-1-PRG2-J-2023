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

// trouver un truc pour vérifier en cas de mémoire insuffisante
bool testInitialiser(void){
   Liste* liste = initialiser();
   if(liste->queue == NULL && liste->tete == NULL){
      return true;
   }
   return false;
}

bool testEstVide(void){

}

bool testLongueur(void){

}

bool testAfficher(void){

}

bool testInsererEnTete(void){

}

bool testInsererEnQueue(void){

}

bool testSupprimerEnTete(void){

}

bool testSupprimerEnQueue(void){

}

bool testSupprimerSelonCritere(void){

}

bool testVider(void){

}

bool testSontEgales(void){

}
