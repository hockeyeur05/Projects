#ifndef TTTREE_C
#define TTTREE_C

//#define MAIN1 //éxécuter seulement le programme 3


#include "tttree.h"

void grille_to_dot(T_grille grille) {
	static int nb_noeuds = 0;
	printf("m%d [shape=none label=<<TABLE border='0' cellspacing='10' cellpadding='10' style='rounded' 		bgcolor='black'>", nb_noeuds);
	printf("<TR>\n");
	for (int i=0; i<3; i++) {
		printf("<TD bgcolor='white'>%c</TD>\n", valeur_to_char_bis((grille.cases)[i].valeur));
	}
	printf("</TR>\n");
	printf("<TR>\n");
	for (int i=3; i<6; i++) {
		printf("<TD bgcolor='white'>%c</TD>\n", valeur_to_char_bis((grille.cases)[i].valeur));
	}
	printf("</TR>\n");
	printf("<TR>\n");
	for (int i=6; i<9; i++) {
		printf("<TD bgcolor='white'>%c</TD>\n", valeur_to_char_bis((grille.cases)[i].valeur));
	}
	printf("</TR>\n");
	if (grille.trait == ROND) printf("<TR><TD bgcolor='red' colspan='3'>m%d</TD></TR></TABLE>>];\n", nb_noeuds);
	if (grille.trait == CROIX) printf("<TR><TD bgcolor='green' colspan='3'>m%d</TD></TR></TABLE>>];\n", nb_noeuds);
	nb_noeuds++;
}



char valeur_to_char_bis(T_valeur valeur) {
    switch(valeur) {
        case CROIX : return 'x';
        case ROND : return 'o';
        case VIDE : return '.';
    }
}


int nbmarqueurs_bis(T_grille grille) {
    int i;
    int compteur = 0;
    for(i=0;i<MAXLEN;i++) {
        if (grille.cases[i].valeur != VIDE) {
            compteur++;
        }
    }
    return compteur;
}


int maxdepth(T_grille grille,T_valeur joueur) {
	int d = 0;
	if(eval_fin(grille) != 0) return d;
	T_grille tab[MAXLEN];
	int nb_enfants = g(grille, joueur,tab);
	T_grille * enfants = malloc(sizeof(T_grille *) * nb_enfants);
	enfants = genere_enfants_bis(grille, joueur, tab);
	return maxdepth(enfants[0], oppose(joueur));

}

int depth(T_grille grille,T_grille grille_initiale) {
	return nbmarqueurs_bis(grille) - nbmarqueurs_bis(grille_initiale);
}
#ifdef MAIN1
int main(int argc, char *argv[]) {
	
	
	char *fen = argv[1];
	T_grille grille = fen_to_grille(fen);
	T_valeur joueur = grille.trait;

	if (grille.jeu_fini == -1) {
		fprintf(stderr, "Erreur lors de la conversion de la FEN en grille\n");
	}

	printf("digraph {\n");
	//gen_dot(grille, 0 , joueur);
	generate_dot_rec(grille, 0, joueur, grille);
	printf("}\n");
	return 0;
}*/
#endif


void generate_dot_rec(T_grille grille, int noeud, T_valeur joueur, T_grille grille_initiale) {
    grille_to_dot(grille);
	if (eval_fin(grille) != 0) {return;}
	T_grille tab[MAXLEN];
    int nb_enfants = g(grille,joueur,tab);;
    T_grille * enfants = malloc(nb_enfants * sizeof(T_grille));
    enfants = genere_enfants_bis(grille,joueur,tab);
	static int i = 0;
    while(eval_fin(enfants[i])==0) {
		printf("  m%d -> m%d;\n", noeud, noeud+i+1);
        generate_dot_rec(enfants[i], noeud+i+1, oppose(joueur), grille_initiale);
        i++;}
	
}

#endif