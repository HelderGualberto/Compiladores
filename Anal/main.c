//
//  main.c
//  Anal
//
//  Created by Joao Sisanoski on 4/26/16.
//  Copyright © 2016 Joao Sisanoski. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "sintatico.h"
#include "tabsimbolo.h"

int main(int argc, const char * argv[]) {
/*
    para fazer o analisador léxico, lembre-se de:
    alocar uma variável do tipo TNoIdentificador.
    Colocar os atributos respectivos .
     char identificador[MAX_ID]; - > variavel que representa o string que identificou o atomo.
     TCatAtributo tipo_atributo -> olhar enum no arquivo tabsimbolo.h, basicamente representa os tipos de atomos.
     union conjunto_atributos -> valor utilizado para representar  os tipos da variavel.



     TOMAR MUITO CUIDADO COM OS PONTEIROS.



*/
    printf("Hello, World!\n");
    return 0;
}
