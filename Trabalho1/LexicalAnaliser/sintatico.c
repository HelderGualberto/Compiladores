#include "sintatico.h"
#include "analex.h"

TAtomo lookahead;

void consome(TAtomo atomoEsperado){
    if(atomoEsperado == lookahead){
        TInfoAtomo info_atomo = AnaLex();
        lookahead = info_atomo.atomo;
    }

    else{
        printf("Erro sintatico:[%d] -  Atomo esperado: %s - Atomo recebido: %s",linha,msg_atomo[atomoEsperado],msg_atomo[lookahead]);
        exit(EXIT_FAILURE);
    }
}

void programa(){

}

void AnaSintatico(){

    initTabSimbolos();

    programa();

}
