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

void remplirListe(Liste *liste, int taille) {
   for (int i = 0; i < taille; ++i) {
      insererEnTete(liste, &i);
   }
}

// trouver un truc pour vérifier en cas de mémoire insuffisante
bool testInitialiser(void){
   Liste* liste = initialiser();
   if(liste->queue == NULL && liste->tete == NULL){
      free(liste);
      return true;
   }
   free(liste);
   return false;
}

// le test d'inserererEnTete doit être fait avant celui de estVide car on utilise insererEnTete dans cette fct
bool testEstVide(void){
   Liste* liste = initialiser();
   bool testReussi = true;
   if(!estVide(liste)){ // on teste si une liste vide est bien vide
      testReussi = false;
   } else {
      Info info = 1;
      insererEnTete(liste, &info);
      if (estVide(liste)) { // on teste si une liste non vide est bien non vide
         testReussi = false;
      }
   }
   vider(liste, 0);
   free(liste);
   return testReussi;
}

// le test d'inserererEnTete doit être fait avant celui de longueur car on utilise insererEnTete dans cette fct
bool testLongueur(void){
   Liste* liste = initialiser();
   bool testReussi = true;
   if(longueur(liste) != 0){ // on vérifie que la longueur d'une liste vide est 0
      testReussi = false;
   } else {
      Info infoPremierElement = 1;
      insererEnTete(liste, &infoPremierElement);
      if(longueur(liste) != 1){ // on vérifie que la longueur d'une liste de 1 élément est 1
         testReussi = false;
      } else {
         Info infoDeuxiemeElement = 2;
         insererEnTete(liste, &infoDeuxiemeElement);
         if(longueur(liste) != 2){ // on vérifie que la longueur d'une liste de 2 éléments est 2 (cas général)
            testReussi = false;
         }
      }
   }
   vider(liste, 0);
   free(liste);
   return testReussi;
}

bool testAfficher(void){

}

void testInsererEnTete(void){
   Liste* liste = initialiser();
   Info info = 1;
   insererEnTete(liste, &info);
   assert(liste->tete->info == info);
   vider(liste, 0);
   free(liste);
}

void testInsererEnQueue(void){
   Liste* liste = initialiser();
   Info info = 1;
   insererEnTete(liste, &info);
   assert(liste->queue->info == info);
   vider(liste, 0);
   free(liste);
}

// tester insererEnTete avant
bool testSupprimerEnTete(void){


}

bool testSupprimerEnQueue(void){

}

bool testSupprimerSelonCritere(void){

}

void testVider(void){
   Liste* liste = initialiser();
   Liste* listeVide = initialiser();
   remplirListe(liste, 5);
   vider(liste, 0);
   assert(sontEgales(liste, listeVide));
   free(liste);
   free(listeVide);
}

bool testSontEgales(void){

}
