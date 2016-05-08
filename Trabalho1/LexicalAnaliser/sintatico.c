#include "sintatico.h"
#include "analex.h"

TAtomo lookahead;

void consome(TAtomo atomoEsperado){
    if(atomoEsperado == lookahead){
        TInfoAtomo info_atomo = AnaLex();
        lookahead = info_atomo.atomo;
    }
    else{
        printf("Erro sintatico! Atomo esperado: %s - Atomo recebido: %s",msg_atomo[atomoEsperado],msg_atomo[lookahead]);
        exit(EXIT_FAILURE);
    }

}

void AnaSintatico(){

}
