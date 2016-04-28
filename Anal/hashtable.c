#define PRIME_NUMBER 211
#define EOS '\x0'
#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
//
hashnode *cria_hashnode();
TNoIdentificador *hashTable[PRIME_NUMBER];
//
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
hashmap *cria_hash_map(){
    int x;
    hashmap *has = malloc(sizeof(hashmap *));
    has->node = malloc(PRIME_NUMBER *sizeof(hashnode));
    for (x = 0 ; x < PRIME_NUMBER ; x++){
        has->node[x] = *cria_hashnode();PRIME_NUMBER
    }
    return has;
}
hashnode *cria_hashnode(){
    hashnode *novo_node = malloc(sizeof(hashnode *));
    novo_node->atomos = nova_lista_atomos();

    return novo_node;

}
void adiciona_atomo_hash_map(hashmap *hash, atomo_anasin *atomo){
    int indice = hashpjw(atomo->identificador);
    lista_atomos *atomos =  hash->node[indice].atomos;
    adiciona_atomo_lista_atomos(atomos, atomo);
}

















//void adiciona_variavel_hash_map(hashmap *hash, variavel *var){
//    int indice = hashpjw(var->identificador);
//    lista_atomos *atomos =  hash->node[indice].atomos;
//    adiciona_variavel_lista_atomo(atomos, var);
//}
//void adiciona_parametro_hash_map(hashmap *hash, parametro *par){
//    int indice = hashpjw(par->identificador);
//    lista_atomos *atomos =  hash->node[indice].atomos;
//    adiciona_parametro_lista_atomo(atomos, par);
//
//}
//
//void adiciona_procedimento_hash_map(hashmap *hash, procedimento *proc){
//    int indice = hashpjw(proc->identificador);
//    lista_atomos *atomos =  hash->node[indice].atomos;
//    adiciona_variavel_lista_atomo(atomos, var);
//}
//void adiciona_parametro_hash_map(hashmap *hash, parametro *par){
//    int indice = hashpjw(par->identificador);
//    lista_atomos *atomos =  hash->node[indice].atomos;
//    adiciona_parametro_lista_atomo(atomos, par);
//
//}
