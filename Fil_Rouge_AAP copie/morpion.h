#ifndef MORPION_H
#define MORPION_H

#define MAXLEN 9

typedef enum {ROND , CROIX , VIDE} T_valeur;

typedef struct {
    T_valeur valeur; 
} T_case;

typedef struct {
    T_case cases[MAXLEN];
    T_valeur trait;
    int jeu_fini; //0 si le jeu n'est pas fini, 1 si les ronds ont gagnés, 2 si les croix ont gagnées, 3 si nul
} T_grille;

typedef struct {
    int score;
    int position;
} Coup;


char int_to_char(int k);
T_valeur oppose(T_valeur valeur);
T_valeur char_to_valeur (char valeur);
char valeur_to_char(T_valeur valeur);
T_grille coup(T_grille grille, int position, T_valeur coup_joue);
T_grille fen_to_grille(char * code_fen);
int eval_fin(T_grille grille);
void print_grille(T_grille grille);
int nbmarqueurs(T_grille grille, T_valeur valeur);
int max(int a, int b);
int min(int a, int b);
int evaluer(T_grille grille, T_valeur joueur);
int * genere_enfants(T_grille grille, T_valeur joueur, T_grille enfants[MAXLEN]);
int estNoeudTerminal(T_grille grille);
Coup negamax(T_grille node, int depth, int alpha, int beta, T_valeur joueur);
Coup minimax(T_grille node, int depth, T_valeur traitOrdi);
T_grille * genere_enfants_bis(T_grille grille, T_valeur joueur, T_grille enfants[]);
int g(T_grille grille, T_valeur joueur, T_grille enfants[]);
T_valeur char_to_valeur2(char valeur);
T_grille coup_bis(T_grille grille, int position, T_valeur coup_joue);
#endif