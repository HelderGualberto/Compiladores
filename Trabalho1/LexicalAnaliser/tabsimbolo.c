
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
        tabela_simbolos[x] = calloc(1,sizeof(TListaTabSimbolos *));
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
    printf("\n\n\n --------------------------------------------\n\n");
    for (x = 0 ; x < PRIME_NUMBER; x++){
        TListaTabSimbolos *tabSimbolo =  tabela_simbolos[x];
        imprime_lista_simbolos(tabSimbolo);
    }
}
void imprime_lista_simbolos(TListaTabSimbolos *tabSimbolos){
    TNoTabSimbolos *atual = tabSimbolos->cabeca;
    procedimento *proc;
    funcao *func;
    while(atual != NULL){
    switch (atual->NoIdentificador->tipo_atributo){
        case(CAT_VARIAVEL_GLOBAL):
            if (atual->NoIdentificador->identificador != NULL){
                printf("Variavel global %s - Tipo %s\n", atual->NoIdentificador->identificador, msg_atomo[atual->NoIdentificador->conjunto_atributos.var->tipo_variavel]);
            }
            break;
        case(CAT_VARIAVEL_LOCAL):
            if (atual->NoIdentificador->identificador != NULL){
                printf("--Variavel local %s - Tipo %s\n", atual->NoIdentificador->identificador, msg_atomo[atual->NoIdentificador->conjunto_atributos.var->tipo_variavel]);
            }
            break;
        case(CAT_PROCEDIMENTO):

            break;
        case(CAT_FUNCAO):
            if (atual->NoIdentificador->identificador != NULL){
                printf("Funcao %s - Tipo %s\n", atual->NoIdentificador->identificador, msg_atomo[atual->NoIdentificador->conjunto_atributos.func->tipo_de_retorno]);
                imprime_lista_simbolos(atual->NoIdentificador->conjunto_atributos.func->listaParametros);
                imprime_lista_simbolos(atual->NoIdentificador->conjunto_atributos.func->listaVariaveis);

            }
            break;
        case(CAT_PARAMETRO):
            break;
    }
    atual = atual->prox;
    }
}
funcao *nova_funcao(){
    funcao *novafunc = malloc(sizeof(funcao));
    novafunc->listaParametros = malloc(sizeof(TListaTabSimbolos));
    novafunc->listaParametros->cabeca = NULL;
    novafunc->listaVariaveis = malloc(sizeof(TListaTabSimbolos));
    novafunc->listaVariaveis->cabeca = NULL;

    return novafunc;
}
variavel *nova_variavel(){
    return  calloc(1, sizeof(variavel));

}
parametro *novo_parametro(){
    return  calloc(1, sizeof(parametro));

}
procedimento *novo_procedimento(){
    return  calloc(1, sizeof(procedimento));

}
TNoIdentificador *novo_TNoIdentificador(){
        return  calloc(1, sizeof(TNoIdentificador));

}
