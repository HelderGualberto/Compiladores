//
//  lista_atomo.h
//  Anal
//
//  Created by Joao Sisanoski on 4/27/16.
//  Copyright © 2016 Joao Sisanoski. All rights reserved.
//

#ifndef lista_atomo_h
#define lista_atomo_h

#include <stdio.h>
#include "atomo.h"
typedef struct _no_atomo{
    struct _no_atomo *prox;
    atomo_anasin *atomo;

}no_atomo;
typedef struct{
    no_atomo *inicio;
}lista_atomos;
//funcoes que manipulam as listas de parametro
lista_atomos *nova_lista_atomos();
void adiciona_atomo_lista_atomos(lista_atomos *, atomo_anasin *);
//void adiciona_parametro_lista_atomo(lista_atomos *, parametro *);
//void adiciona_procedimento_lista_atomo(lista_atomos *, procedimento *);
//void adiciona_variavel_lista_atomo(lista_atomos *, variavel *);
//void adiciona_funcao_lista_atomo(lista_atomos *, funcao *);
#endif /* lista_atomo_h */
