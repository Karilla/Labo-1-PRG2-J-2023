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
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void remplirListe(Liste *liste, int taille) {
   for (int i = 0; i < taille; ++i) {
      insererEnTete(liste, &i);
   }
}

bool valeurEtPositionPaires(size_t position, const Info *info) {
   if (((*info % 2) == 1) || ((position % 2) == 1)) {
      return false;
   }
   return true;
}


// trouver un truc pour vérifier en cas de mémoire insuffisante
void testInitialiser(void){
   Liste* liste = initialiser();
   assert(liste->queue == NULL && liste->tete == NULL);
   free(liste);
}

// le test d'inserererEnTete doit être fait avant celui de estVide car on utilise insererEnTete dans cette fct
void testEstVide(void){
   Liste* liste = initialiser();
   assert(estVide(liste)); // on teste si une liste vide est bien vide
   Info info = 1;
   insererEnTete(liste, &info);
   assert(!estVide(liste)); // on teste si une liste non vide est bien non vide
   vider(liste, 0);
   free(liste);
}

// le test d'inserererEnTete doit être fait avant celui de longueur car on utilise insererEnTete dans cette fct
void testLongueur(void){
   Liste* liste = initialiser();
   assert(longueur(liste) == 0); // on vérifie que la longueur d'une liste vide est 0
   Info infoPremierElement = 1;
   insererEnTete(liste, &infoPremierElement);
   assert(longueur(liste) == 1); // on vérifie que la longueur d'une liste de 1 élément est 1
   Info infoDeuxiemeElement = 2;
   insererEnTete(liste, &infoDeuxiemeElement);
   assert(longueur(liste) == 2); // on vérifie que la longueur d'une liste de 2 éléments est 2 (cas général)
   vider(liste, 0);
   free(liste);
}

void testAfficher(void){
   Liste* liste = initialiser();
   remplirListe(liste, 3);
   char* buffer;
   const char* affichageAttendu = "[0,1,2]";
   assert(strcmp(buffer, affichageAttendu));
   vider(liste,0);
   free(liste);
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
   insererEnQueue(liste, &info);
   assert(liste->queue->info == info);
   vider(liste, 0);
   free(liste);
}

// tester insererEnTete avant
void testSupprimerEnTete(void){
   Liste* liste = initialiser();
   Info infoPremierElement = 1;
   Info infoDeuxiemeElement = 2;
   Info infoRetour;
   assert(supprimerEnTete(liste, NULL) == LISTE_VIDE); // on vérifie le cas d'une liste vide
   insererEnTete(liste, &infoPremierElement);
   supprimerEnTete(liste, &infoRetour);
   assert(estVide(liste)); // on vérifie pour une liste de 1 élément
   assert(infoPremierElement == infoRetour);
   insererEnTete(liste, &infoPremierElement);
   insererEnTete(liste, &infoDeuxiemeElement);
   supprimerEnTete(liste, &infoRetour);
   assert(liste->tete->info == infoPremierElement); // on vérifie pour une liste de 2 éléments (cas général)
   assert(infoDeuxiemeElement == infoRetour);
   vider(liste, 0);
   free(liste);
}

void testSupprimerEnQueue(void){
   Liste* liste = initialiser();
   Info infoPremierElement = 1;
   Info infoDeuxiemeElement = 2;
   Info infoRetour;
   assert(supprimerEnQueue(liste, NULL) == LISTE_VIDE); // on vérifie le cas d'une liste vide
   insererEnTete(liste, &infoPremierElement);
   supprimerEnQueue(liste, &infoRetour);
   assert(estVide(liste)); // on vérifie pour une liste de 1 élément
   assert(infoPremierElement == infoRetour);
   insererEnTete(liste, &infoPremierElement);
   insererEnTete(liste, &infoDeuxiemeElement);
   supprimerEnQueue(liste, &infoRetour);
   assert(liste->queue->info == infoDeuxiemeElement); // on vérifie pour une liste de 2 éléments (cas général)
   assert(infoPremierElement == infoRetour);
   vider(liste, 0);
   free(liste);
}

void testSupprimerSelonCritere(void){
   Liste* liste = initialiser();
   remplirListe(liste, 5); // [4,3,2,1,0]
   Liste* listeAttendue = initialiser();
   const Info infoListeAttendue[] = {3,1};
   insererEnQueue(listeAttendue, &infoListeAttendue[0]);
   insererEnQueue(listeAttendue, &infoListeAttendue[1]); // [3,1]
   supprimerSelonCritere(liste, valeurEtPositionPaires);
   assert(sontEgales(listeAttendue, liste));
   vider(listeAttendue, 0);
   free(listeAttendue);
   vider(liste, 0);
   free(liste);
}

// j'utilise pas estVide car testEstVide utilise Vider
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
   printf("Fonction de test pour la fonction sontEgales....\n");
   bool testOk = true;
   Liste* liste1 = initialiser();
   Liste* liste2 = initialiser();

   printf("Test quand les 2 listes sont vides: ");
   //Test si les 2 listes sont vides la fonction nous renvoie true
   if(sontEgales(liste1,liste2) != true){
      printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
      testOk = false;
   }
   else{
      printf(ANSI_COLOR_GREEN"reussite\n"ANSI_COLOR_RESET);
   }


   //Test si la liste 1 est plus grande que la 2 renvoie false
   printf("Test quand la liste 1 est plus grande que la liste 2: ");
   Info valeur = 10;
   insererEnTete(liste1, &valeur);
   if(sontEgales(liste1, liste2) != false){
      printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
      testOk = false;
   }else{
      printf(ANSI_COLOR_GREEN"reussite\n"ANSI_COLOR_RESET);
   }

   //Test si la liste 1 et la liste 2 sont egales et renvoie true
   printf("Test quand les 2 listes sont bien egales: ");
   insererEnTete(liste2, &valeur);
   if(sontEgales(liste1, liste2) != true){
      printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
      testOk = false;
   }else{
      printf(ANSI_COLOR_GREEN"reussite\n"ANSI_COLOR_RESET);
   }

   //Test quand liste 1 et liste 2 ont la meme taille mais pas les meme elements
   printf("Test quand les 2 listes ont la meme taille mais pas les memes elements: ");
   supprimerEnQueue(liste2, NULL);
   valeur = 20;
   insererEnTete(liste2,&valeur);
   if(sontEgales(liste1, liste2) != false){
      printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
      testOk = false;
   }else{
      printf(ANSI_COLOR_GREEN"reussite\n"ANSI_COLOR_RESET);
   }

   //Test quand la liste 2 est plus grande que la liste 1 renvoie false
   printf("Test quand la liste 2 est plus grande que la liste 1: ");
   insererEnTete(liste2, &valeur);
   if(sontEgales(liste1, liste2) != false){
      printf(ANSI_COLOR_RED"echec\n"ANSI_COLOR_RESET);
      testOk = false;
   }else{
      printf(ANSI_COLOR_GREEN"success\n"ANSI_COLOR_RESET);
   }

   vider(liste1,0);
   vider(liste2, 0);

   free(liste2);
   free(liste1);
   return testOk;
}
