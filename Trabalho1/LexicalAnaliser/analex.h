#ifndef ANALEX_H_INCLUDED
#define ANALEX_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum{
    ALGORITMO,
    CARACTERE,
    DIV,
    E,
    ENQUANTO,
    ENTAO,
    FACA,
    FALSO,
    FIM,
    FUNCAO,
    INICIO,
    INTEIRO,
    LOGICO,
    MOD,
    NADA,
    NAO,
    OU,
    PROCEDIMENTO,
    REAL,
    REF,
    SE,
    SENAO,
    VARIAVEIS,
    VETOR,
    ERRO,     // erro lexico
    ID,       // identificador
    NUM_INT,  // numero inteiro
    NUM_REAL, // numero real
    EOS, // fim de string
    OP_RELACIONAL,
    COMENTARIO_1,
    COMENTARIO_2,
    SUBTRACAO,
    ADICAO,
    MULTIPLICACAO,
    ABRE_PAR,
    ATRIBUICAO,
    FECHA_PAR,
    PONTO_VIRGULA,
    PONTO_PONTO,
    ABRE_COLCHETES,
    FECHA_COLCHETES,
    CONSTANTE_INTEIRO,
    CONSTANTE_STRING,
    CONSTANTE_CHAR,
    CONSTANTE_REAL
}TAtomo;


//Definicao de um enum para referenciar os operadores relacionais
typedef enum{
    ME,
    MEI,
    IG,
    DI,
    MA,
    MAI
}AtrOpRelacional;


// definicao de uma estrutura union para os atributos do atomo (Tokens)
typedef union
{
    char str_id[17];//16+1 para guardar o \0
    int valor_inteiro;
    float valor_real;
    AtrOpRelacional op_relac;
    char constante[32];
    char constante_char;
    int constante_inteiro;
}TAtributo;

// defincao de uma estrutura para retornar as informacoes do atomo
// Atomo (token), numero da linha e atributo
typedef struct{
    TAtomo atomo; //Constante representando o ·tomo
    int linha; //N˙mero da linha onde o ·tomo foi encontrado
    TAtributo atributo; // atributos para os ·tomos
}TInfoAtomo;

char * read_file(FILE*);
TInfoAtomo AnaLex(void);

extern char * msg_atomo[];
extern char * msg_op_relacional[];
#endif // ANALEX_H_INCLUDED
