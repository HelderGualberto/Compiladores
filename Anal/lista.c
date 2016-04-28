//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//#include "lista.h"
//#include "atomo.h"
//// lista de parametros
//no_parametro *cria_no_parametro(parametro *par){
//    no_parametro *novo_no = malloc(sizeof(no_parametro *));
//    novo_no->par = par;
//    novo_no->prox = NULL;
//    return novo_no;
//}
//
//void adiciona_parametro_lista(lista_parametros *lista, parametro *par){
//    no_parametro *atual = lista->inicio;
//    no_parametro *ultimo = NULL;
//    
//    while (atual != NULL) {
//        if (strcmp(atual->par->identificador, par->identificador) == 0){
//            exit(EXIT_FAILURE);
//        }
//        ultimo = atual;
//        atual = atual->prox;
//    }
//    no_parametro *novo_no = cria_no_parametro(par);
//    if (ultimo == NULL){
//        lista->inicio = novo_no;
//    } else {
//        ultimo->prox = novo_no;
//    }
//}
//
//lista_parametros *nova_lista_parametro(){
//    lista_parametros *nova_lista = malloc(sizeof(lista_parametros *));
//    if (nova_lista){
//        nova_lista->inicio = NULL;
//    }
//    return nova_lista;
//}
//// finaliza lista de parametros, inicia a lista de variaveis
//
//no_variavel *cria_no_variavel(variavel *var){
//    no_variavel *novo_no = malloc(sizeof(no_variavel *));
//    novo_no->par = var;
//    novo_no->prox = NULL;
//    return novo_no;
//}
//lista_variavel *nova_lista_variavel(){
//    lista_variavel *nova_lista = malloc(sizeof(lista_variavel *));
//    if (nova_lista){
//        nova_lista->inicio = NULL;
//    }
//    return nova_lista;
//}
//void adiciona_variavel_lista(lista_variavel *lista, variavel *var){
//    no_variavel *atual = lista->inicio;
//    no_variavel *ultimo = NULL;
//    
//    while (atual != NULL) {
//        if (strcmp(atual->par->identificador, var->identificador) == 0){
//            exit(EXIT_FAILURE);
//        }
//        ultimo = atual;
//        atual = atual->prox;
//    }
//    no_variavel *novo_no = cria_no_variavel(var);
//    if (ultimo == NULL){
//        lista->inicio = novo_no;
//    } else {
//        ultimo->prox = novo_no;
//    }
//
//}