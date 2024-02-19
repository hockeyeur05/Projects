#include "morpion.h"
#include "super_morpion.h"

SuperCoup strategie(T_superGrille super_grille, T_valeur joueur, int depth);
int valeur_case(int position);
char * meilleur_coup(T_superGrille super_grille, T_valeur joueur, int depth);
char * strat(T_superGrille super_grille, T_valeur joueur);