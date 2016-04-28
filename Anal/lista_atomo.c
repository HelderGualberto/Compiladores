//
//  lista_atomo.c
//  Anal
//
//  Created by Joao Sisanoski on 4/27/16.
//  Copyright © 2016 Joao Sisanoski. All rights reserved.
//

#include "lista_atomo.h"
#include <stdlib.h>
#include <string.h>
void adicionaAtomoLista(lista_atomos *, no_atomo *);

no_atomo *cria_no_atomo(atomo_anasin *atomo){
    no_atomo *novo_no = malloc(sizeof(no_atomo *));
    novo_no->atomo = atomo;
    return novo_no;
}

//void adiciona_funcao_lista_atomo(lista_atomos *lista, funcao *func){
//    no_atomo *novo_no = cria_no_atomo(CAT_FUNCAO);
//    novo_no->atomo->conjunto_atributos.func = func;
//    adicionaAtomoLista(lista, novo_no);
//
//}
//void adiciona_variavel_lista_atomo(lista_atomos *lista, variavel *var){
//    no_atomo *novo_no;
//    if (var->global){
//        novo_no = cria_no_atomo(CAT_VARIAVEL_GLOBAL);
//    } else {
//        novo_no = cria_no_atomo(CAT_VARIAVEL_LOCAL);
//    }
//    novo_no->atomo->conjunto_atributos.var = var;
//    adicionaAtomoLista(lista, novo_no);
//
//
//}
//void adiciona_procedimento_lista_atomo(lista_atomos *lista, procedimento *proc){
//    no_atomo *novo_no = cria_no_atomo(CAT_PROCEDIMENTO);
//    novo_no->atomo->conjunto_atributos.procedimento = proc;
//    adicionaAtomoLista(lista, novo_no);
//
//
//
//}
//void adiciona_parametro_lista_atomo(lista_atomos *lista, parametro *par){
//    no_atomo *novo_no = cria_no_atomo(CAT_PARAMETRO);
//    novo_no->atomo->conjunto_atributos.par = par;
//    adicionaAtomoLista(lista, novo_no);
//
//}
void adicionaAtomoLista(lista_atomos *lista, no_atomo *atomo){
    no_atomo *atual = lista->inicio;
    no_atomo *ultimo = NULL;
    while (atual != NULL) {
        int compare = strcmp(atual->atomo->identificador, atomo->atomo->identificador);
        if (compare == 0){
            exit(EXIT_FAILURE);
        } else if (compare > 1){

            break;
        }
        ultimo = atual;
        atual = atual->prox;
    }

    if (ultimo == NULL){
        lista->inicio = atomo;
    } else {
        ultimo->prox = atomo;
        atomo->prox = atual;
    }
}
void adiciona_atomo_lista_atomos(lista_atomos *lista, atomo_anasin *atomo){

    adicionaAtomoLista(lista, cria_no_atomo(atomo));
}

lista_atomos *nova_lista_atomos(){
    lista_atomos *nova_lista = malloc(sizeof(lista_atomos *));
    if (nova_lista){
        nova_lista->inicio = NULL;
    }
    return nova_lista;
}
