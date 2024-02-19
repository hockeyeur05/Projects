#ifndef PROG1_H
#define PROG1_H
#include "morpion.h"
#include "super_morpion.h"

void grille_to_dot_bis(T_grille grille, FILE * fichier);
void grille_gagnee_to_dot_bis(T_grille grille, FILE * fichier);
void superGrille_to_dot(T_superGrille superGrille, FILE * fichier);
char * echecs_to_coup(char * echecs); 
#endif