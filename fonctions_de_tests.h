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

void remplirListe(Liste *liste, size_t taille);

bool testInitialiser(void);

bool testEstVide(void);

bool testLongueur(void);

void testAfficher(void);

bool testInsererEnTete(void);

bool testInsererEnQueue(void);

void testSupprimerEnTete(void);

void testSupprimerEnQueue(void);

bool testSupprimerSelonCritere(void);

bool testVider(void);

bool testSontEgales(void);

#endif //LABO_1_PRG2_J_2023_FONCTIONS_DE_TESTS_H
