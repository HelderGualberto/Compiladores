#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

char palavras_reservadas[24][17] = {
    "ALGORITMO",
    "CARACTERE",
    "DIV",
    "E",
    "ENQUANTO",
    "ENTAO",
    "FACA",
    "FALSO",
    "FIM",
    "FUNCAO",
    "INICIO",
    "INTEIRO",
    "LOGICO",
    "MOD",
    "NADA",
    "NAO",
    "OU",
    "PROCEDIMENTO",
    "REAL",
    "REF",
    "SE",
    "SENAO",
    "VARIAVEIS",
    "VETOR"
};

// Mensagens para referenciar o operador relacional identificado
char *msg_op_relacional[]={
    "ME",
    "MEI",
    "IG",
    "DI",
    "MA",
    "MAI"
};

// Mensagens do compilador indexadas pelos atomos (tokens)
char *msg_atomo[]={
    "Palavra reservada ALGORITMO",
    "Palavra reservada CARACTERE",
    "Palavra reservada DIV",
    "Palavra reservada E",
    "Palavra reservada ENQUANTO",
    "Palavra reservada ENTAO",
    "Palavra reservada FACA",
    "Palavra reservada FALSO",
    "Palavra reservada FIM",
    "Palavra reservada FUNCAO",
    "Palavra reservada INICIO",
    "Palavra reservada INTEIRO",
    "Palavra reservada LOGICO",
    "Palavra reservada MOD",
    "Palavra reservada NADA",
    "Palavra reservada NAO",
    "Palavra reservada OU",
    "Palavra reservada PROCEDIMENTO",
    "Palavra reservada REAL",
    "Palavra reservada REF",
    "Palavra reservada SE",
    "Palavra reservada SENAO",
    "Palavra reservada VARIAVEIS",
    "Palavra reservada VETOR",
    "Erro Lexico",
    "Identificador",
    "Constante Inteiro",
    "Constante Real",
    "Fim de Buffer",
    "Operador relacional",
    "Comentario 1",
    "Comentario 2",
    "Subtracao",
    "Adicao",
    "Multiplicacao",
    "Abre Parenteses",
    "Atribuicao",
    "Fecha parenteses",
    "Ponto e virgula",
    "Ponto ponto",
    "Abre colchetes",
    "Fecha colchetes",
    "Constante inteiro",
    "Constante string",
    "Constante char",
    "Constante flutuante"
};
// Definicao de uma estrutura enumeracao para as constantes dos atomos (Tokens)
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

#endif // DEFINITIONS_H_INCLUDED
