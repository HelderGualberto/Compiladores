
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
TListaTabSimbolos **tabela_simbolos;


int hashpjw( char * s )
{
    char* p;

    unsigned h = 0, g;
     p = s;

     int x ;
    for (x = 0; x < strlen(s); x++){
        h = ( h << 4 ) + (*p);
        if ( (g = h&0xf0000000) ){
            h = h ^ ( g >> 24 );
            h = h ^ g;
        }
        p = p + 1;
    }
    return h % PRIME_NUMBER;
}

void initTabSimbolos(){
    // coloca null em todas as posicoes da tabela
    int x ;
    tabela_simbolos =  malloc(sizeof(TListaTabSimbolos *)* PRIME_NUMBER);
    for (x = 0 ; x < PRIME_NUMBER ; x++){
        tabela_simbolos[x] = malloc(sizeof(TListaTabSimbolos *));
        memset(tabela_simbolos[x],0,sizeof(tabela_simbolos[x]));

    }

}

// adiciona na tabela simbolos
void adiciona_atomo_lista_atomos(TListaTabSimbolos *lista, TNoIdentificador *NoIdentificador){

    TNoTabSimbolos *atual = lista->cabeca;
    TNoTabSimbolos *anterior = NULL;
    while (atual != NULL) {
        int compare = strcmp(atual->NoIdentificador->identificador, NoIdentificador->identificador);
        if (compare == 0){
            printf("Identificador ja utilizado: %s\n", NoIdentificador->identificador);
            exit(EXIT_FAILURE);
        }
        anterior = atual;
        atual = atual->prox;
    }
    TNoTabSimbolos *novoNo = malloc(sizeof(TNoTabSimbolos));
    novoNo->NoIdentificador = NoIdentificador;
    novoNo->prox = NULL;
    if (anterior == NULL){ // lista vazia
        lista->cabeca = novoNo;
    } else {
        anterior->prox = novoNo;
    }
}void imprime_tabela_simbolos();


void adiciona_atomo_lista_hash(TNoIdentificador *NoIdentificador){
    int idxHash = hashpjw(NoIdentificador->identificador);
    adiciona_atomo_lista_atomos(tabela_simbolos[idxHash], NoIdentificador);

}
void imprime_tabela_simbolos(){
    int x;
    for (x = 0 ; x < PRIME_NUMBER; x++){
        TListaTabSimbolos *tabSimbolo =  tabela_simbolos[x];
        printf("posicao %d da tabela de espalhamento \n", x);
        imprime_lista_simbolos(tabSimbolo);
    }
}
void imprime_lista_simbolos(TListaTabSimbolos *tabSimbolos){
    TNoTabSimbolos *atual = tabSimbolos->cabeca;
    while(atual != NULL){
    switch (atual->NoIdentificador->tipo_atributo){
        case(CAT_VARIAVEL_GLOBAL):
            printf("variavel global ");
            break;
        case(CAT_VARIAVEL_LOCAL):
            printf("variavel local ");
            break;
        case(CAT_PROCEDIMENTO):
            printf("procedimento ");
            break;
        case(CAT_FUNCAO):
            printf("funcao ");
            break;
        case(CAT_PARAMETRO):
            printf("parametro ");
            break;
    }
     printf("parametro %s ", atual->NoIdentificador->identificador);
    atual = atual->prox;
    }
}
