#ifndef SM_B_C
#define SM_B_C

#define MAIN3 //éxécuter seulement le programme 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "super_morpion.h"
#include "sm-bot.h"
#include "morpion.h"
#include "morpion.c"
#include "super_morpion.c"
#include "math.h"


int valeur_case(int position) { //cases plus importantes que d'autres
    switch(position) {
        case 0 : return 5;
        case 1 : return 2;
        case 2 : return 5;
        case 3 : return 2;
        case 4 : return 10;
        case 5 : return 2;
        case 6 : return 5;
        case 7 : return 2;
        case 8 : return 5;
        default : return 0;
    }
}

/*
SuperCoup strategie(T_superGrille super_grille, T_valeur joueur, int depth) {
    //int score_total = 0;
    SuperCoup super_coup = {INT_MIN,-1};
    int scores[MAXLEN] = {0};
    for(int i = 0;i<MAXLEN;i++) {
        //score_total = score_total + valeur_case(i) * minimax(super_grille.grilles[i],2,super_grille.trait).score * negamax(super_grille.grilles[i],depth,INT_MIN, INT_MAX,joueur).score;
        scores[i] = valeur_case(i) * negamax(super_grille.grilles[i],depth,INT_MIN, INT_MAX,joueur).score *minimax(super_grille.grilles[i],2,super_grille.trait).score;
        if(scores[i] > super_coup.score) {
            super_coup.score = scores[i];
            super_coup.position = i;
        }
    }
    return super_coup;
}

char * meilleur_coup(T_superGrille super_grille, T_valeur joueur,int depth) {
    char * res = malloc(sizeof(char)*3);
    SuperCoup coup = strategie(super_grille, joueur, depth);
    T_grille meilleure_grille = super_grille.grilles[(coup.position)];
    int meilleure_case = negamax(meilleure_grille,depth, INT_MIN, INT_MAX,joueur).position;
    res[0] = int_to_char(coup.position)+1;
    res[1] = int_to_char(meilleure_case)+1;
    res[2] = '\0';
    return res;
} */

char * strat(T_superGrille super_grille, T_valeur joueur) {
    char * res = malloc(sizeof(char)*3);
    int k = super_grille.dernier_coup_joue % 10  -1 ;
    if(eval_fin(super_grille.grilles[k])== 0) {
        res[0] = int_to_char(k+1);
        //res[1] = int_to_char(minimax(super_grille.grilles[k],2,joueur).position + 1);
        res[1] = int_to_char(negamax(super_grille.grilles[k],10,INT_MIN,INT_MAX,joueur).position + 1);
    }

    else {
        //res[0] = int_to_char(minimax(super_grille.grilles[MAXLEN],2,joueur).position + 1);
        //res[1] = int_to_char(minimax(super_grille.grilles[MAXLEN],2,joueur).position + 1);
        int p = negamax(super_grille.grilles[MAXLEN],10,INT_MIN,INT_MAX,joueur).position;
        res[0] = int_to_char(p+ 1);
        res[1] = int_to_char(negamax(super_grille.grilles[p],10,INT_MIN,INT_MAX,joueur).position + 1);
    }
    return res;
} 

int puis(int a, int b);
int puis(int a, int b) {
    int res = 1;
    int i;
    for(i=0;i<b;i++) {
        res*=a;
    }
    return res;
}


#ifdef MAIN3
int main(int argc, char * argv[]) {
    if(argc!=3) {
        fprintf(stderr,"nombre incorrect de paramètres");
        return -1;
    }
    char * fen = argv[1];
    int time = 0;
    int i=0;
    int len = l(argv[2]);
    for(i=0;i<len;i++) {
        time = time + puis(10,i) * argv[2][len-i-1];
    }
    if(time <= 0) {
        fprintf(stderr,"temps écoulé\n");
        return 0;
    }
    T_superGrille super_grille = fen_to_super_grille_bis(fen);
    //char * best_coup = meilleur_coup(super_grille,super_grille.trait,2);
    printf("%s\n",strat(super_grille,super_grille.trait));
    return 0;
}
#endif

#endif