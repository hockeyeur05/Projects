#ifndef MORPION_C
#define MORPION_C


#include "morpion.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



T_valeur char_to_valeur(char valeur) {
    switch(valeur) {
        case('x') : return CROIX;
        case('o') : return ROND;
        default : return VIDE; //si c'est un chiffre
    }
}


T_valeur char_to_valeur2(char valeur) {
    switch(valeur) {
        case('X') : return CROIX;
        case('O') : return ROND;
        default : return VIDE; //si c'est un chiffre
    }
}

char int_to_char(int k) { //transforme un chiffre entre 0 et 9 
                          //en un caractère de ce même chiffre (pas besoin de plus pour un morpion classique)
    switch(k) {
        case 0 : return '0';break;
        case 1 : return '1';break;
        case 2 : return '2';break;
        case 3 : return '3';break;
        case 4 : return '4';break;
        case 5 : return '5';break;
        case 6 : return '6';break;
        case 7 : return '7';break;
        case 8 : return '8';break;
        case 9 : return '9';break;
        default : fprintf(stderr,"veuillez entrer un chiffre entre 0 et 9\n"); return -1;
    }
}

char valeur_to_char(T_valeur valeur) {
    static int compteur = 0; //nombre de cases vides d'affilé
    switch(valeur) {
        case CROIX : compteur = 0; return 'x';
        case ROND : compteur = 0; return 'o';
        case VIDE : compteur ++; return int_to_char(compteur);
    }
}

T_valeur oppose(T_valeur valeur) {
    switch(valeur) {
        case CROIX : return ROND;break;
        case ROND : return CROIX;break;
        default : return VIDE;break;
    }
}

T_grille coup(T_grille grille, int position, T_valeur coup_joue) {
    if (grille.jeu_fini != 0) {fprintf(stderr,"la partie est déjà terminée\n"); return grille;}
    if (grille.trait == oppose(coup_joue)) {fprintf(stderr,"c'est à l'adversaire de jouer\n"); return grille;}
    if (grille.cases[position].valeur != VIDE) {fprintf(stderr,"la case est déjà pleine\n"); return grille;}
    
    else {
        grille.cases[position].valeur = coup_joue;
        grille.jeu_fini = eval_fin(grille);
        grille.trait = oppose(coup_joue);
        return grille;
        }
}

T_grille coup_bis(T_grille grille, int position, T_valeur coup_joue) {
        grille.cases[position].valeur = coup_joue;
        grille.jeu_fini = eval_fin(grille);
        grille.trait = oppose(coup_joue);
        return grille;
        
}

T_grille fen_to_grille(char * code_fen) {
    T_grille grille;
    grille.trait = VIDE;
    grille.jeu_fini = 0;
    int position = 0;
    int compteur = 0; //nombre de cases vides que l'on  a rencontré
    int i = 0; //nb de chiffres ds le code fen
    int compteurs[MAXLEN] = {0}; //tableau de compteurs, compteurs[i] donne la valeur du ième compteur
    while( (code_fen[position] != ' ') && (position + compteur - i < MAXLEN) ) {
            (grille.cases[position+compteur-i]).valeur = char_to_valeur(code_fen[position]);
            if (char_to_valeur(code_fen[position]) != VIDE) {position++; }
            else {
                compteur++;
                compteurs[i]++;
                if (compteurs[i] == code_fen[position] - '0') {
                    position++;
                    i++;

                 }
            }

    }
    grille.trait = char_to_valeur(code_fen[position+1]);
    grille.jeu_fini = eval_fin(grille);
    return grille;
}

int valeur_to_int(T_valeur valeur) { //renvoie le chiffre correspondant pour grille.jeu_fini
    switch(valeur) {
        case VIDE : return 0;break; //pas réellement besoin de celui-ci
        case ROND : return 1;break;
        case CROIX : return 2;break;
        default : return -1;break;
    }
}

int eval_fin(T_grille grille) { //fonction que l'on peut largement améliorer
    if ( (grille.cases[1].valeur == grille.cases[0].valeur) && (grille.cases[2].valeur == grille.cases[0].valeur) 
        && (grille.cases[0].valeur != VIDE) )
        {return valeur_to_int(grille.cases[0].valeur);} // ooo
                                                        // ...
                                                        // ...
    if ( (grille.cases[3].valeur == grille.cases[0].valeur) && (grille.cases[6].valeur == grille.cases[0].valeur) 
        && (grille.cases[0].valeur != VIDE) )
        {return valeur_to_int(grille.cases[0].valeur);} //  o..
                                                        //  o..
                                                        //  o..

    if ( (grille.cases[4].valeur == grille.cases[0].valeur) && (grille.cases[8].valeur == grille.cases[0].valeur) 
        && (grille.cases[0].valeur != VIDE) )
         {return valeur_to_int(grille.cases[0].valeur);} //  o..
                                                         //  .o.    
                                                         //  ..o

    if ( (grille.cases[4].valeur == grille.cases[3].valeur) && (grille.cases[5].valeur == grille.cases[3].valeur) 
        && (grille.cases[3].valeur != VIDE) )
         {return valeur_to_int(grille.cases[3].valeur);} //  ...
                                                         //  ooo
                                                         //  ...

    if ( (grille.cases[7].valeur == grille.cases[6].valeur) && (grille.cases[8].valeur == grille.cases[6].valeur) 
        && (grille.cases[6].valeur != VIDE) )
         {return valeur_to_int(grille.cases[6].valeur);} //  ...
                                                         //  ...
                                                         //  ooo

    if ( (grille.cases[4].valeur == grille.cases[1].valeur) && (grille.cases[7].valeur == grille.cases[1].valeur) 
        && (grille.cases[1].valeur != VIDE) )
         {return valeur_to_int(grille.cases[1].valeur);} //  .o.
                                                         //  .o.
                                                         //  .o.

    if ( (grille.cases[5].valeur == grille.cases[2].valeur) && (grille.cases[8].valeur == grille.cases[2].valeur) 
        && (grille.cases[2].valeur != VIDE) )
         {return valeur_to_int(grille.cases[2].valeur);} //  ..o
                                                         //  ..o
                                                         //  ..o

    if ( (grille.cases[4].valeur == grille.cases[2].valeur) && (grille.cases[6].valeur == grille.cases[2].valeur) 
        && (grille.cases[2].valeur != VIDE) )
         {return valeur_to_int(grille.cases[2].valeur);} //  ..o
                                                         //  .o.
                                                         //  o..

    else {
        int i;
        int compteur = 0; //nombre de cases jouées
        for(i=0;i<MAXLEN;i++) {
            if(grille.cases[i].valeur!=VIDE) {compteur++;}
        }
        if(compteur == MAXLEN) {return 3;} //nul si toutes les cases sont jouées et que personne n'a gagné
        else {return 0;} //si toutes les cases ne sont pas remplies et que personne n'a encore gagné, le jeu continue
    }
}


void print_grille(T_grille grille) {
    int i;
    for(i=0;i<MAXLEN;i++) {
        switch((grille.cases[i]).valeur) {
            case CROIX : printf("x  ");break;
            case ROND : printf("o  ");break;
            default : printf("•  ");break;
        }
        if ((i+1)%3==0) printf("\n");
    }

}

int nbmarqueurs(T_grille grille, T_valeur valeur) {
    int i;
    int compteur = 0;
    for(i=0;i<MAXLEN;i++) {
        if (grille.cases[i].valeur == valeur) {
            compteur++;
        }
    }
    return compteur;
}

Coup negamax(T_grille node, int depth, int alpha, int beta, T_valeur joueur) {
    if (depth == 0 || estNoeudTerminal(node)) {
        return (Coup){evaluer(node, joueur), -1}; } // Position est -1 pour indiquer qu'aucun coup n'est associé.
    

    Coup val = {INT_MIN, -1};
    T_grille enfants[MAXLEN]; 
    int nombre_enfants = g(node, joueur, enfants);
    int * num_enfants = genere_enfants(node, joueur, enfants);

    for (int i = 0; i < nombre_enfants; i++) {
        if (-negamax(enfants[i], depth - 1, -beta, -alpha, oppose(joueur)).score > val.score) {
            val.score = -negamax(enfants[i], depth - 1, -beta, -alpha, oppose(joueur)).score;
            val.position = num_enfants[i]; 
        }

        if (val.score >= beta) {
            return val; // élagage beta.
        }
        
        alpha = max(alpha,val.score);
    }

    return val; 
} 

Coup minimax(T_grille node, int depth, T_valeur traitOrdi) {
    if (depth == 0 || estNoeudTerminal(node)) {
        return (Coup){evaluer(node, traitOrdi), -1}; } 
    Coup val;
    T_grille tab[MAXLEN];
    int nombre_enfants = g(node, traitOrdi, tab);
    T_grille * enfants = malloc(sizeof(T_grille) * nombre_enfants);
    enfants = genere_enfants_bis(node,traitOrdi, enfants);
    int * num_enfants = genere_enfants(node, traitOrdi, tab);

    if(traitOrdi == node.trait) {
        val.position = -1;
        val.score = INT_MIN;
        int i;
        for(i=0;i<nombre_enfants;i++) {
            if (val.score < minimax(enfants[i],depth - 1, traitOrdi).score) {
                val.score = minimax(enfants[i],depth - 1, traitOrdi).score;
                val.position = num_enfants[i];
            }
        }
    }
    

    else {
        val.position = -1;
        val.score = INT_MAX;
        enfants = genere_enfants_bis(node,traitOrdi, enfants);
        int i;
        for(i=0;i<nombre_enfants;i++) {
            if (val.score > minimax(enfants[i],depth - 1, traitOrdi).score) {
                val.score = minimax(enfants[i],depth - 1, traitOrdi).score;
                val.position = num_enfants[i];
            }
        }
    }
    return val;
}


int estNoeudTerminal(T_grille grille) {
    int resultat = eval_fin(grille);
    return resultat != 0;
}

int evaluer(T_grille grille, T_valeur joueur) {
    int res = eval_fin(grille);
    if (res == valeur_to_int(joueur)) {
        return 10 + nbmarqueurs(grille,joueur) - nbmarqueurs(grille,oppose(joueur)); // c'est gagné
    } else if (res == valeur_to_int(oppose(joueur))) {
        return -10 + nbmarqueurs(grille,joueur) - nbmarqueurs(grille,oppose(joueur)); // c'est perdu
    } else {
        return nbmarqueurs(grille,joueur) - nbmarqueurs(grille,oppose(joueur)); 
    }
}

int * genere_enfants(T_grille grille, T_valeur joueur, T_grille enfants[]) {
    // Génère tous les coups possibles à partir de la grille actuelle pour le joueur 'joueur'
    // et les stocke dans le tableau 'enfants'. Met à jour 'nombre_enfants' avec le nombre d'enfants générés.
    // renvoie un tableau contenant les numéros des cases ayant donné lieu à un enfant (si différent de -1)
    int nombre_enfants = 0;
    int * res = malloc(sizeof(int)*MAXLEN);
    for (int p=0;p<MAXLEN;p++){
        res[p] = -1;
    }
    int k = 0;
    for (int i = 0; i < MAXLEN; ++i) { // au max 9 enfants
        if (grille.cases[i].valeur == VIDE) {
            res[k] = i;
            k++;
            enfants[nombre_enfants] = grille;
            enfants[nombre_enfants].cases[i].valeur = joueur;
            nombre_enfants++;
        }
    }
    return res;
}

T_grille * genere_enfants_bis(T_grille grille, T_valeur joueur, T_grille enfants[]) {
    // Génère tous les coups possibles à partir de la grille actuelle pour le joueur 'joueur'
    // et les stocke dans le tableau 'enfants'. Met à jour 'nombre_enfants' avec le nombre d'enfants générés.
    // renvoie les enfants
    int nombre_enfants = 0;
    int res[MAXLEN] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int k = 0;
    for (int i = 0; i < MAXLEN; ++i) { // au max 9 enfants
        if (grille.cases[i].valeur == VIDE) {
            res[k] = k;
            k++;
            enfants[nombre_enfants] = grille;
            enfants[nombre_enfants].cases[i].valeur = joueur;
            enfants[nombre_enfants].trait = oppose(joueur);
            nombre_enfants++;
        }
    }
    return enfants;
}

int g(T_grille grille, T_valeur joueur, T_grille enfants[]) {
    // Génère tous les coups possibles à partir de la grille actuelle pour le joueur 'joueur'
    // et les stocke dans le tableau 'enfants'. Met à jour 'nombre_enfants' avec le nombre d'enfants générés.
    // renvoie les enfants
    int nombre_enfants = 0;
    int res[MAXLEN] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int k = 0;
    for (int i = 0; i < MAXLEN; ++i) { // au max 9 enfants
        if (grille.cases[i].valeur == VIDE) {
            res[k] = k;
            k++;
            enfants[nombre_enfants] = grille;
            enfants[nombre_enfants].cases[i].valeur = joueur;
            enfants[nombre_enfants].trait = oppose(joueur);
            nombre_enfants++;
        }
    }
    return nombre_enfants;
}

int max(int a, int b) {
    if(a>b) return a;
    else return b;
}

int min(int a, int b) {
    if(a<b) return a;
    else return b;
}

#endif