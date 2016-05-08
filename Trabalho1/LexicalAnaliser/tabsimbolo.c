
//
//  lista_atomo.c
//  Anal
//
//  Created by Joao Sisanoski on 4/27/16.
//  Copyright © 2016 Joao Sisanoski. All rights reserved.
//

#include "tabsimbolo.h"
#include <stdlib.h>
#include <string.h>

// Tabela de simbolos global
TListaTabSimbolos tabela_simbolos[PRIME_NUMBER];


int hashpjw( char * s )
{
    char* p;
    unsigned h = 0, g;
    for ( p = s; *p != EOS; p = p + 1 ){
        h = ( h << 4 ) + (*p);
        if ( (g = h&0xf0000000) ){
            h = h ^ ( g >> 24 );
            h = h ^ g;
        }
    }
    return h % PRIME_NUMBER;
}

void initTabSimbolos(){
    // coloca null em todas as posicoes da tabela
    memset(tabela_simbolos,0,sizeof(tabela_simbolos));

}

// adiciona na tabela simbolos
void adiciona_atomo_lista_atomos(TListaTabSimbolos *lista, TNoIdentificador *NoIdentificador){
    TNoTabSimbolos *atual = lista->cabeca;
    TNoTabSimbolos *anterior = NULL;
    while (atual != NULL) {
        int compare = strcmp(atual->NoIdentificador->identificador, NoIdentificador->identificador);
        if (compare == 0)
            exit(EXIT_FAILURE);

        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL){ // lista vazia
        lista->cabeca = NoIdentificador;
    } else {
        anterior->prox = NoIdentificador;
    }
}

void adiciona_atomo_lista_hash(TNoIdentificador *NoIdentificador){
    int idxHash = hashpjw(NoIdentificador->identificador);
    adiciona_atomo_lista_atomos(&tabela_simbolos[idxHash], NoIdentificador);

}
