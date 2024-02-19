#ifndef TTTREE_H
#define TTTREE_H
#include "morpion.h"
//#include "morpion.c"

void generate_dot_rec(T_grille grille, int noeud, T_valeur joueur, T_grille grille_initiale);
void grille_to_dot(T_grille grille);
char valeur_to_char_bis(T_valeur valeur);
int maxdepth(T_grille grille, T_valeur joueur);
int depth(T_grille grille,T_grille grille_initiale);
int nbmarqueurs_bis(T_grille grille);
int generate_dot(T_grille grille, int noeud, T_valeur joueur, int *nb_noeuds);
#endif