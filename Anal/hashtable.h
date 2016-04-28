#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
/*1) Atributos gerais:
a) sequência de caracteres que gerou o átomo IDENTIFICADOR;
b) A categoria do atributo (VARIÁVEL GLOBAL, VARIÁVEL LOCAL, PROCEDIMENTO, FUNÇÃO ou PARÂMETRO);
c) Atributos específicos para Variáveis locais e globais:
i) Tipo da variável definido na produção tipo
ii) Ordem na declaração
d) Atributos específicos para Parâmetros:
i) Tipo do parâmetro definido na produção tipo_simples
ii) Ordem na declaração
iii) Passagem (Valor ou referência).
e) Atributos específicos para Procedimentos:
i) Lista de parâmetros; e
ii) Lista de variáveis locais;
f) Atributos específicos para Funções:
i) Tipo de retorno da função;
ii) Lista de parâmetros; e
iii) Lista de variáveis locais;
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
