//
//  main.c
//  Anal
//
//  Created by Joao Sisanoski on 4/26/16.
//  Copyright © 2016 Joao Sisanoski. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "sintatico.h"
#include "tabsimbolo.h"
/*
#include "hashtable.h"
#include "analex.h"

atomo_anasin *inicia_variavel( TInfoAtomo *atomo){
    atomo_anasin *atomo_anasim = malloc(sizeof(atomo_anasin *));
    atomo_anasim->identificador = atomo->atributo.constante;
    return atomo_anasim;
}
*/
//TInfoAtomo *lookahead;
/*void consome(TAtomo atomoEsperado){
    if( lookahead->atomo == atomoEsperado){
        free(lookahead);
        lookahead = avanca_um(buffer);
    }
    else{
        char msgErro[100];
        sprintf(msgErro,"Esperado [%c] encontrado [%c] \n\n",atomoEsperado, lookahead);
        Erro(msgErro);
    }

}
void declaracao_variavel(){
    atomo_anasin *atomo = inicia_variavel(lookahead);
    consome(lookahead->atomo);

}
void bloco(){
    if (lookahead->atomo == VARIAVEIS){
        declaracao_variavel();
    }
    if (lookahead->atomo == FUNCAO){
        while (lookahead->atomo == FUNCAO) {
            consome(FUNCAO);
        }
    }
    else {
        printf("erro sintatico");
    }
}
void algorirtmo(){
    consome(ALGORITMO);
    consome(ID);
    bloco();
}
*/
int main(int argc, const char * argv[]) {
//    if (argc < 2)
//    {
//        exit(EXIT_FAILURE);
//    }

    //buffer = carrega_buffer("/Volumes/JOAO-LUCAS/Facul/Anal/teste.txt");
    //lookahead = avanca_um(buffer);
    //algorirtmo();
    printf("Hello, World!\n");
    return 0;
}
