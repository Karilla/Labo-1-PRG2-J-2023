/*
 -----------------------------------------------------------------------------------
 Nom du fichier : fonctions_de_tests.h
 Auteur(s)      : <A compléter>
 Date creation  : 30.04.2023

 Description    : <A compléter>

 Remarque(s)    : <A compléter>

 Compilateur    : Mingw-w64 gcc 9.0
 -----------------------------------------------------------------------------------
*/

#ifndef LABO_1_PRG2_J_2023_FONCTIONS_DE_TESTS_H
#define LABO_1_PRG2_J_2023_FONCTIONS_DE_TESTS_H

#include "listes_dynamiques.h"
#include <stdlib.h>
#include <stdbool.h>

void remplirListe(Liste *liste, int taille);

bool valeurEtPositionPaires(size_t position, const Info *info);

void testInitialiser(void);

void testEstVide(void);

void testLongueur(void);

void testAfficher(void);

void testInsererEnTete(void);

void testInsererEnQueue(void);

void testSupprimerEnTete(void);

void testSupprimerEnQueue(void);

void testSupprimerSelonCritere(void);

void testVider(void);

bool testSontEgales(void);

#endif //LABO_1_PRG2_J_2023_FONCTIONS_DE_TESTS_H
