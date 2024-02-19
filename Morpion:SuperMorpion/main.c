#include "morpion.h"
#include "morpion.c"
#include "super_morpion.h"
#include "super_morpion.c"
#include "sm-bot.h"
#include "sm-bot.c"



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
    printf("%s\n",strat(super_grille,super_grille.trait));
    return 0;
}