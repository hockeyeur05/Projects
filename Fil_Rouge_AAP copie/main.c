#include "morpion.h"
#include "morpion.c"
#include "super_morpion.h"
#include "super_morpion.c"
//#include "tttree.h"
//#include "tttree.c"



int main(int argc, char *argv[]) {

    //#define GRILLE // à décommenter si l'on veut jouer une partie de morpion

    #define SUPERGRILLE // à décommenter si l'on veut jouer une partie de super morpion

    //#define PROG1

    #ifdef GRILLE 
    T_grille grille = fen_to_grille("4o4 x");
    grille = coup(grille,2,CROIX);
    grille = coup(grille,0,ROND);
    grille = coup(grille,5,CROIX);
    //grille = coup(grille,8,ROND);
   // grille = coup(grille,3,CROIX);
    //grille = coup(grille,1,ROND);
    //grille = coup(grille,7,CROIX);
   // grille = coup(grille,6,ROND);
    print_grille(grille);
    printf("%c\n",valeur_to_char(grille.trait));
    printf("%d\n",eval_fin(grille));
    printf("%d\n",grille.jeu_fini);
    printf("%d %d \n",negamax(grille, 2, INT_MIN, INT_MAX,ROND).score,negamax(grille, 2, INT_MIN, INT_MAX,ROND).position);
    printf("%d %d \n",minimax(grille, 1, ROND).score,minimax(grille, 1, ROND).position);
    return 0;
    #endif

    #ifdef SUPERGRILLE 
    T_superGrille s = fen_to_super_grille_bis("XoxoooxxoxOox3x3Xoo7Oox1x5oxo1x4 82 o");
    print_super_grille(&s);
    /*T_superGrille s = fen_to_super_grille_bis("6xoxOOOX2xo1ox1oXx2xo4oox4ox 84 o");
    print_super_grille(&s);
    T_superGrille super_grille = coup_super_grille(&s,5,0,s.grilles[0].trait);
    print_super_grille(&super_grille);
    printf("%d\n",eval_fin(fen_to_grille("o1xo1ox1o x")));
    T_superGrille s_g = coup_super_grille(&super_grille,7,8,super_grille.grilles[0].trait);
    print_super_grille(&s_g);
       T_superGrille s_gg = coup_super_grille(&s_g,8,4,s_g.grilles[0].trait);
    print_super_grille(&s_gg);*/
    /*char ** res = decoupe("6xoxOOOX2xo1ox1oXx2xo4oox4ox 84 o\0",'o');
    for(int i=0;i<MAXLEN;i++) {
        printf("%s\n",decoupe("6xoxOOOX2xo1ox1oXx2xo4oox4ox 84 o\0",'o')[i]);
    }*/
    //print_s_g(fen_to_super_grille("999999994o4 95 x\0"));
    /*int i;
    for(i=0;i<MAXLEN;i++) {
    printf("%s\n",decoupe("999999994o4 95 x",'x')[i]);
    }
    //int k=7;
    //printf("%d",k%3 +3*(k%3));*/
   /* T_superGrille super_grille;
    int i;
    int j;
    for(i=0;i<MAXLEN;i++) {
        for(j=0;j<MAXLEN;j++) {
            super_grille.grilles[i].cases[j].valeur = ROND;
        }
    }
    print_super_grille(super_grille);*/
    //print_grille(super_grille.grilles[0]);
    /*int k;
    T_superGrille super_grille;
    for(k=0;k<MAXLEN;k++) {
    super_grille.grilles[k] = fen_to_grille(decoupe("999999994o4 95 x",'x')[k]); }
    int i;
    int j;
    for(j=0;j<MAXLEN;j++) {
        for(i=0;i<MAXLEN;i++) {
            switch((super_grille.grilles[i]).cases[i].valeur) {
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
    int l;
    for(l=0;l<MAXLEN;l++) {
        switch(((super_grille.grilles[MAXLEN-1]).cases[k]).valeur) {
            case CROIX : printf("X  ");break;
            case ROND : printf("O  ");break;
            default : printf("•  ");break;
        }
        if ((i+1)%3==0) printf("\n");
    }*/
/*
T_superGrille super_grille;
char **grilles_fen = decoupe_bis("999999994o4 95 x", 'x');
if (grilles_fen) {
    for (int k = 0; k < MAXLEN; k++) {
        if (grilles_fen[k]) {
            super_grille.grilles[k] = fen_to_grille(grilles_fen[k]);
            free(grilles_fen[k]);
        }
    }
    free(grilles_fen);
}

for (int j = 0; j < MAXLEN; j++) {
    for (int i = 0; i < MAXLEN; i++) {
        T_valeur val = super_grille.grilles[j].cases[i].valeur;
        switch (val) {
            case CROIX: printf("x  "); break;
            case ROND: printf("o  "); break;
            default: printf("•  "); break;
        }
        if ((i + 1) % 3 == 0) printf("\n");
    }
    if ((j + 1) % 3 == 0) printf("\n\n");
}
*/
    return 0;

    #endif


    #ifdef PROG1
	char *fen = argv[1];
	T_grille grille = fen_to_grille(fen);
	T_valeur joueur = grille.trait;

	if (grille.jeu_fini == -1) {
		fprintf(stderr, "Erreur lors de la conversion de la FEN en grille\n");
	}
	
	printf("digraph {\n");
	generate_dot_rec(grille, 0, joueur,fen_to_grille(fen));
	printf("}\n");

    return 0;


    #endif
}