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

char * strat(T_superGrille super_grille, T_valeur joueur) {
    char * res = malloc(sizeof(char)*3);
    int k = super_grille.dernier_coup_joue % 10  -1 ;
    if(eval_fin(super_grille.grilles[k])== 0) {
        res[0] = int_to_char(k+1);
        res[1] = int_to_char(negamax(super_grille.grilles[k],10,INT_MIN,INT_MAX,joueur).position + 1);
    }

    else {
        int p = negamax(super_grille.grilles[MAXLEN],10,INT_MIN,INT_MAX,joueur).position;
        if (eval_fin(super_grille.grilles[p])==3) {
            for(int i=0;i<MAXLEN;i++) {
                if(eval_fin(super_grille.grilles[i])==0) {
                    super_grille.grilles[i] = coup(super_grille.grilles[i],negamax(super_grille.grilles[i],10,INT_MIN,INT_MAX,joueur).position,joueur);
                    res[0] = int_to_char(i+ 1);
                    res[1] = int_to_char(negamax(super_grille.grilles[i],10,INT_MIN,INT_MAX,joueur).position + 1);
                } 
            }
    }
        else {
        res[0] = int_to_char(p+ 1);
        res[1] = int_to_char(negamax(super_grille.grilles[p],10,INT_MIN,INT_MAX,joueur).position + 1);
        }
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
#endif