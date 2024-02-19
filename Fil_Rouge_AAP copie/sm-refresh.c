#ifndef SM_R_C
#define SM_R_C

//#define MAIN2 //éxécuter seulement le programme 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morpion.h"
#include "super_morpion.h"
#include "sm-refresh.h"
#include "sm-bot.h"
#include "tttree.h"
#include "morpion.c"
#include "super_morpion.c"
#include "sm-bot.c"
#include "tttree.c"


void grille_to_dot_bis(T_grille grille,FILE * fichier) {
	fprintf(fichier,"<TD bgcolor='white'> <TABLE border='0' cellspacing='10' cellpadding='10' style='rounded' bgcolor='black'>\n");
	fprintf(fichier,"<TR>\n");
	for (int i=0; i<3; i++) {
		fprintf(fichier,"<TD bgcolor='white'>%c</TD>\n", valeur_to_char_bis((grille.cases)[i].valeur));
	}
	fprintf(fichier,"</TR>\n");
	fprintf(fichier,"<TR>\n");
	for (int i=3; i<6; i++) {
		fprintf(fichier,"<TD bgcolor='white'>%c</TD>\n", valeur_to_char_bis((grille.cases)[i].valeur));
	}
	fprintf(fichier,"</TR>\n");
	fprintf(fichier,"<TR>\n");
	for (int i=6; i<9; i++) {
		fprintf(fichier,"<TD bgcolor='white'>%c</TD>\n", valeur_to_char_bis((grille.cases)[i].valeur));
	}
	fprintf(fichier,"</TR>\n");
	fprintf(fichier,"</TABLE>\n");
	fprintf(fichier,"</TD>\n");
}

void grille_gagnee_to_dot_bis(T_grille grille, FILE * fichier) {
	if (grille.jeu_fini == 1) {
		fprintf(fichier,"<TD bgcolor='black'> <TABLE border='0' cellspacing='10' cellpadding='10' style='rounded' bgcolor='white'><TR> <TD bgcolor='white'>&nbsp;</TD> <TD bgcolor='white'>&nbsp;</TD> <TD bgcolor='white'>&nbsp;</TD> </TR> <TR> <TD bgcolor='white'>&nbsp;</TD> <TD bgcolor='white'>&nbsp;</TD> <TD bgcolor='white'>&nbsp;</TD> </TR> <TR> <TD bgcolor='white'>&nbsp;</TD> <TD bgcolor='white'>&nbsp;</TD> <TD bgcolor='white'>&nbsp;</TD> </TR> </TABLE> </TD>\n");
	}
	else if (grille.jeu_fini == 2) {
		fprintf(fichier,"<TD bgcolor='white'> <TABLE border='0' cellspacing='10' cellpadding='10' style='rounded' bgcolor='black'><TR> <TD bgcolor='black'>&nbsp;</TD> <TD bgcolor='black'>&nbsp;</TD> <TD bgcolor='black'>&nbsp;</TD> </TR> <TR> <TD bgcolor='black'>&nbsp;</TD> <TD bgcolor='black'>&nbsp;</TD> <TD bgcolor='black'>&nbsp;</TD> </TR> <TR> <TD bgcolor='black'>&nbsp;</TD> <TD bgcolor='black'>&nbsp;</TD> <TD bgcolor='black'>&nbsp;</TD> </TR> </TABLE> </TD>\n");
	}
}

void superGrille_to_dot(T_superGrille superGrille, FILE * fichier) {
	fprintf(fichier,"digraph  { a0 [shape=none label=<<TABLE border='0' cellspacing='10' cellpadding='10' style='rounded' bgcolor='black'> <TR>\n");
	for (int i=0; i<9; i++) {
		if (superGrille.grilles[i].jeu_fini ==1 || superGrille.grilles[i].jeu_fini ==2) {
			grille_gagnee_to_dot_bis(superGrille.grilles[i],fichier);
		}
		else {
			grille_to_dot_bis(superGrille.grilles[i],fichier);
			}
		if(i==2||i==5) {
			fprintf(fichier,"</TR>\n<TR>\n");
		}
	}
	fprintf(fichier,"  </TR> </TABLE> >]; }\n");
}

char * echecs_to_coup(char * echecs) {
	int i = echecs[0] - '0' -1;
	int j = echecs[2] - 'a';
	int k = echecs[3] - '0'-1;
	char * coup  = malloc(sizeof(char)*3);
	coup[0] = int_to_char(i);
	coup[1] = int_to_char(j+3*k);
	coup[2] = '\0';
	return coup;
}
	
	
#ifdef MAIN2
int main(int argc, char ** argv) {
	FILE * fichier = fopen("output.dot","a");
	int depth = argv[2][0] - '0';
	
	char * echecs = argv[1];
	char * coup = echecs_to_coup(echecs);
	int numero_grille = coup[0] - '0';
	int numero_case = coup[1] - '0';
	   
	
	static T_superGrille superGrille;
	for (int i=0; i<MAXLEN; i++) {
		for (int j=0; j<MAXLEN; j++) {
			superGrille.grilles[i].cases[j].valeur = VIDE;
		}
	}
	superGrille = coup_super_grille(&superGrille, numero_grille, numero_case, superGrille.trait); 
	
	char * coup_bot = strat(superGrille, oppose(superGrille.trait), depth);
	superGrille = coup_super_grille(&superGrille, coup_bot[0]-'0', coup_bot[1]-'0', oppose(superGrille.trait));
	
	print_super_grille(&superGrille);
	superGrille_to_dot(superGrille,fichier);
	system("dot output.dot -T png -o fichier.png"); 
	return 0;
}
#endif

#endif