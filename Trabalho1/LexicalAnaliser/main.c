/**
    PROGRAMA DESENVOLVIDO PELOS AUTORES HELDER RODRIGUES E JOAO SISANOSKI
    DO CURSO DE ENGENHARIA DA COMPUTACAO
**/

/*
    O CODIGO A SEGUIR E REFERENTE A IMPLEMENTACAO DE UM ANALISADOR LEXICO
    ONDE A FUNCAO AnaLex TEM A FUNCAO PRINCIPAL DE IDENTIFICAR OS ATMOS DA
    LINGUAGEM DEFINIDA.
    POSTERIORMENTE A FUNCAO SERA UTILIZADA COMO ENTRADA PARA UM ANALISADOR SINTATICO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "analex.h"


int main( int narg, char ** args)
{
    //codigo para entrada do caminho do arquivo via linha de comando
        char * caminho_entrada = malloc(sizeof(char)*30);
        FILE* arquivo_entrada;

        if(narg > 1){
            printf("%s",args[1]);
            caminho_entrada = args[1];
        }

        arquivo_entrada = fopen(caminho_entrada,"r");
        if(arquivo_entrada == NULL){
            printf("Caminho nao encontrado!\n");
            exit(EXIT_FAILURE);
        }

        read_file(arquivo_entrada);

   // buffer = "314^567";
    printf("Analisador Lexico versao 1.0\n");

    AnaSintatico();
    //imprime_tabela_simbolos();
    return 0;
}
