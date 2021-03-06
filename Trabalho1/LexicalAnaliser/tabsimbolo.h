#ifndef TABSIMBOLO_H_INCLUDED
#define TABSIMBOLO_H_INCLUDED
#define PRIME_NUMBER 211
#include "analex.h"

struct _no_tabsimbolos;
struct _lista_tabsimbolos;
typedef enum{
    CAT_VARIAVEL_GLOBAL,
    CAT_VARIAVEL_LOCAL,
    CAT_PROCEDIMENTO,
    CAT_FUNCAO,
    CAT_PARAMETRO
}TCatAtributo;

typedef struct{
    TAtomo tipo_variavel; // inteiro | real | caractere | logico | vetor
    int ordem_declaracao;
}variavel;

typedef struct {
    TAtomo tipo_parametro; // inteiro | real | caractere | logico
    int ordem_declaracao;
    TAtomo passagem; // ref / valor = nada
}parametro;

typedef struct {
    struct _lista_tabsimbolos  *listaParametros;
    struct _lista_tabsimbolos  *listaVariaveis;
}procedimento;

typedef struct{
    TAtomo tipo_de_retorno; // inteiro | real | caractere | logico
    struct _lista_tabsimbolos  *listaParametros;
    struct _lista_tabsimbolos  *listaVariaveis;
}funcao;

typedef struct{
    char identificador[17];
    TCatAtributo tipo_atributo;
    union {
        variavel *var;
        parametro *par;
        procedimento *procedimento;
        funcao *func;
    }conjunto_atributos;

}TNoIdentificador;

typedef struct _no_tabsimbolos{
    TNoIdentificador *NoIdentificador;
    struct _no_tabsimbolos *prox;

}TNoTabSimbolos;

typedef struct _lista_tabsimbolos{
    TNoTabSimbolos *cabeca;

}TListaTabSimbolos;




/*
typedef struct{
    TNoTabSimbolos tabela_simbolos[]];
}TabSimbolos;
*/

funcao *nova_funcao();
variavel *nova_variavel();
parametro *novo_parametro();
procedimento *novo_procedimento();
TNoIdentificador *novo_TNoIdentificador();
//funcoes que manipulam as listas de parametro
void adiciona_atomo_lista_atomos(TListaTabSimbolos *lista, TNoIdentificador *NoIdentificador);
void adiciona_atomo_lista_hash(TNoIdentificador *);
void imprime_lista_simbolos(TListaTabSimbolos *);
void imprime_tabela_simbolos();
#endif // TABSIMBOLO_H_INCLUDED
