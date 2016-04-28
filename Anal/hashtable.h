#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
/*1) Atributos gerais:
a) sequ�ncia de caracteres que gerou o �tomo IDENTIFICADOR;
b) A categoria do atributo (VARI�VEL GLOBAL, VARI�VEL LOCAL, PROCEDIMENTO, FUN��O ou PAR�METRO);
c) Atributos espec�ficos para Vari�veis locais e globais:
i) Tipo da vari�vel definido na produ��o tipo
ii) Ordem na declara��o
d) Atributos espec�ficos para Par�metros:
i) Tipo do par�metro definido na produ��o tipo_simples
ii) Ordem na declara��o
iii) Passagem (Valor ou refer�ncia).
e) Atributos espec�ficos para Procedimentos:
i) Lista de par�metros; e
ii) Lista de vari�veis locais;
f) Atributos espec�ficos para Fun��es:
i) Tipo de retorno da fun��o;
ii) Lista de par�metros; e
iii) Lista de vari�veis locais;
*/
#include "lista_atomo.h"
#include "procedimentos.h"
#include "funcoes.h"

typedef struct _hash {
    lista_atomos *atomos;
} hashnode;
typedef struct{
    hashnode *node;
} hashmap;


hashmap *cria_hash_map();
void adiciona_variavel_hash_map(hashmap *, variavel *);
void adiciona_parametro_hash_map(hashmap *, parametro *);

void imprime_hashtable(hashmap *);

#endif // HASHTsABLE_H_INCLUDED
