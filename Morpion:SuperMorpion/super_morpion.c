#ifndef S_M_C
#define S_M_C



#include "super_morpion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


T_superGrille coup_super_grille(T_superGrille * super_grille, int numero_grille, int position, T_valeur coup_joue) {
    //coup dans la super grille
    int k = super_grille->dernier_coup_joue % 10 -1 ; //grille dans laquelle l'on doit jouer si elle n'est pas pleine ou gagnée
    if ( (numero_grille != k) && (eval_fin(super_grille->grilles[k]) == 0) ) {
        fprintf(stderr,"veuillez jouer dans la bonne grille\n");
        return *super_grille;
    }
    super_grille->grilles[numero_grille] = coup(super_grille->grilles[numero_grille], position, coup_joue);
    for (int i=0; i<MAXLEN;i++) {
        super_grille->grilles[i].trait = oppose(coup_joue);
    } 
    super_grille->dernier_coup_joue = 10*(numero_grille+1) + position+1;
    //convention de la notation 99 pour 9ème grille 9ème case
    super_grille->super_jeu_fini = eval_fin_super_grille(*super_grille);
    super_grille->trait = oppose(coup_joue);
    return super_coup(*super_grille); //au cas ou un des morpions est gagné (c'est un super_coup)
}

T_superGrille super_coup(T_superGrille super_grille) { 
    //Joue dans la grande grille si l'un des 9 morpions est gagné
    //Le trait de la grande grille est toujours vide
    int i;
    for(i=0;i<MAXLEN;i++) {
        switch(eval_fin(super_grille.grilles[i])) {
            case 1 : super_grille.grilles[MAXLEN] = coup_bis(super_grille.grilles[MAXLEN], i, ROND); 
                     super_grille.grilles[MAXLEN].trait = VIDE;  
                     super_grille.super_jeu_fini = eval_fin_super_grille(super_grille);
                     break;
            case 2 : super_grille.grilles[MAXLEN] = coup_bis(super_grille.grilles[MAXLEN], i, CROIX); 
                     super_grille.grilles[MAXLEN].trait = VIDE;
                     super_grille.super_jeu_fini = eval_fin_super_grille(super_grille);
                     break;
            case 3 : super_grille.grilles[MAXLEN] = coup_bis(super_grille.grilles[MAXLEN], i, VIDE); 
                     super_grille.grilles[MAXLEN].trait = VIDE;
                    super_grille.super_jeu_fini = eval_fin_super_grille(super_grille);
                     break;
            default :super_grille.grilles[MAXLEN] = coup_bis(super_grille.grilles[MAXLEN], i, VIDE); 
                     super_grille.grilles[MAXLEN].trait = VIDE;
                    super_grille.super_jeu_fini = eval_fin_super_grille(super_grille);
                     break;
    }
    }
    return  super_grille;
}

int eval_fin_super_grille(T_superGrille super_grille) { //répond au problème que pose le case 3 précédent 
                                                         //(comment voir si la partie est finie)
return eval_fin(super_grille.grilles[MAXLEN]);

}
int puissance(char car) {
    switch (car) {
        case 'O' : return 9;break;
        case 'X' : return 9;break;
        case 'x' : return 1;break;
        case 'o' : return 1;break;
        default : return car - '0';break; // si c'est un chiffre
    }
}

char *concat(char *mot1, char *mot2) {
    if (mot1 == NULL || mot2 == NULL) {
        return NULL;
    }

    int l1 = l(mot1); 
    int l2 = l(mot2);
    char *res = malloc((l1 + l2 + 1) * sizeof(char)); // +1 for the null terminator

    if (res == NULL) {
        return NULL;
    }

    int i;
    for (i = 0; i < l1; i++) {
        res[i] = mot1[i];
    }
    for (int j = 0; j < l2; j++) {
        res[l1 + j] = mot2[j];
    }
    res[l1 + l2] = '\0'; 

    return res;
}

char * char_to_string(char trait) {
    switch(trait) {
        case 'o' : return "o";break;
        case 'x' : return "x";break;
        default : return "vide";break;
    }
}


char ** decoupe(char * code_fen, char trait) {
    int compteur_puissance = 0;
    char ** res = malloc(sizeof(char *)*MAXLEN); 
    if(res==NULL) {
        fprintf(stderr,"res is NULL\n");
        return NULL;
    }
    int position = 0;
    int i = 0; //numero de la grille
    int debuts[MAXLEN+1] = {0}; //positions des débuts de grille dans le code_fen
    int fins[MAXLEN+1] = {0}; //positions des fins de grille dans le code_fen
    fins[MAXLEN-1] = l(code_fen) - 5;
    //on enleve le trait, le dernier coup et les deux espaces
    while ( (code_fen[position] != ' ') && (i<MAXLEN) && (position<MAXLEN*MAXLEN+5) ) {
        compteur_puissance = compteur_puissance + puissance(code_fen[position]);
        fins[i]++;
        if (compteur_puissance % 9 == 0) {
            debuts[i+1] = fins[i]; 
            fins[i+1] = debuts[i+1];
            res[i] = concat (concat(coupe(code_fen,debuts[i],fins[i]-1)," "),char_to_string(trait)); 
            //on rajoute l'espace et le trait à la fin du découpage
            i++;

        }
        position++;
    }
    return res;
        
}

char * coupe(char * mot, int debut, int fin) {
        if(mot==NULL) {
        fprintf(stderr,"erreur\n");
        return NULL;
    }
    char * res = malloc((fin - debut + 2) * sizeof(char));
 // +2 pour le caractère nul et l'espace
    int i;
    for (i = debut; i <= fin; i++) {
        res[i - debut] = mot[i];
    }
    res[i - debut] = '\0'; 
    return res;
}

int l(char * mot ) {
    if(mot==NULL) {
        fprintf(stderr,"erreur\n");
        return -1;
    }
    int i=0;
    while(mot[i]!='\0') {
        i++;
    }
    return i;
}

void print_super_grille(T_superGrille * super_grille) {
    int i;
    int j;
    for(j=0;j<MAXLEN;j++) {
        for(i=0;i<MAXLEN;i++) { if ((i/3 + 3* (j/3)>=MAXLEN) || (i%3 +3*(j%3)>=MAXLEN) ) {
            fprintf(stderr, "Error: Index out of bounds\n");
                return; }
                switch((super_grille->grilles[i/3 + 3* (j/3)]).cases[i%3 +3*(j%3)].valeur) {
                case CROIX : printf("x  ");break;
                case ROND : printf("o  ");break;
                default : printf("•  ");break;
            }
            }
        printf("\n"); 
    }
    printf("\n"); 
    //ensuite on affiche la grande grille en reprenant le code de print_grille 
    //pour une grille de morpion classique
    int k;
    for(k=0;k<MAXLEN;k++) {
        switch(((super_grille->grilles[MAXLEN]).cases[k]).valeur) {
            case CROIX : printf("X  ");break;
            case ROND : printf("O  ");break;
            default : printf("•  ");break;
        }
        if ((k+1)%3==0) printf("\n");
    }
} 

T_superGrille fen_to_super_grille_bis(char * code_fen) {
    if (code_fen == NULL) {  // Example validation
    fprintf(stderr, "Invalid input string\n");
    return (T_superGrille){0};  
    }
    int len = l(code_fen);
    char trait = code_fen[len-1];
    T_superGrille super_grille;
    super_grille.trait = char_to_valeur2(trait);
    super_grille.dernier_coup_joue = (code_fen[len-4] - '0') * 10 + code_fen[len-3] - '0';
    super_grille.super_jeu_fini = 0;

    for(int k=0;k<MAXLEN;k++) {
        char valeur = decoupe(code_fen,trait)[k][0];
        if ((valeur == 'O') || (valeur == 'X')) {
            for(int p=0;p<MAXLEN;p++) {
                super_grille.grilles[k].cases[p].valeur = char_to_valeur2(valeur);
            }
        }
        else {
            super_grille.grilles[k] = fen_to_grille(decoupe(code_fen,trait)[k]);
        }
    }
    super_grille.grilles[MAXLEN] = super_coup(super_grille).grilles[MAXLEN];
    super_grille.super_jeu_fini = eval_fin_super_grille(super_grille);
    return super_grille;
}

#endif