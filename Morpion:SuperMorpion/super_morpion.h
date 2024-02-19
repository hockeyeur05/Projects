#ifndef SUPER_MORPION_H
#define SUPER_MORPION_H

#include "morpion.h"

typedef struct {
    T_grille grilles[MAXLEN+1];
    int dernier_coup_joue;
    int super_jeu_fini;
    T_valeur trait;
 } T_superGrille; // 9 grilles de morpions classiques 
                                  // + 1 grille servant de "grande grille" pour jouer au super morpion


typedef struct {
    int score;
    int position;
} SuperCoup;

T_superGrille coup_super_grille(T_superGrille * super_grille, int numero_grille, int position, T_valeur coup_joue);
T_superGrille super_coup(T_superGrille super_grille);
int eval_fin_super_grille(T_superGrille super_grille);
int puissance(char car);
int l(char * mot);
char * concat(char * mot1, char * mot2);
char ** decoupe(char * code_fen, char trait);
char ** decoupe_bis(char * code_fen, char trait);
char * coupe(char * mot, int debut, int fin);
T_superGrille fen_to_super_grille(char * code_fen);
void print_super_grille(T_superGrille * super_grille);
char * char_to_string(char trait);
T_superGrille fen_to_super_grille_bis(char * code_fen);
#endif