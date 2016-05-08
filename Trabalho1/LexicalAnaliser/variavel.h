//
//  variavel.h
//  Anal
//
//  Created by Joao Sisanoski on 4/27/16.
//  Copyright © 2016 Joao Sisanoski. All rights reserved.
//

#ifndef variavel_h
#define variavel_h

#include <stdio.h>

typedef enum{
    TIPO_SIMPLES,
    TIPO_COMPOSTO
}TVariavel;


typedef struct{
    TVariavel tipo_variavel;
    int ordem_declaracao;
    int global;
    char *identificador;
}variavel;

#endif /* variavel_h */
