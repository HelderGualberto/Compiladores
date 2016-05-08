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
        /*
        do{
            printf("Entre com o caminho do arquivo\nCaminho: ");
            scanf("%s",caminho_entrada);
            arquivo_entrada = fopen(caminho_entrada,"r");
            if(arquivo_entrada == NULL)
                printf("Caminho nao encontrado!\n");
        }while(arquivo_entrada == NULL);
        */
        read_file(arquivo_entrada);

   // buffer = "314^567";
    TInfoAtomo info_atomo;
    printf("Analisador Lexico versao 1.0\n");

    do{
        info_atomo = AnaLex();
        if( info_atomo.atomo == ID )
            printf("reconhecido %s - atributo=%s\n", msg_atomo[info_atomo.atomo], info_atomo.atributo.str_id);
        else if( info_atomo.atomo == NUM_REAL )
            printf("reconhecido %s - atributo=%.2f\n", msg_atomo[info_atomo.atomo], info_atomo.atributo.valor_real);
        else if(info_atomo.atomo == NUM_INT)
            printf("reconhecido %s - atributo=%d\n",msg_atomo[info_atomo.atomo],info_atomo.atributo.valor_inteiro);
        else if(info_atomo.atomo == ERRO)
            printf("%s\n",msg_atomo[info_atomo.atomo]);
        else if(info_atomo.atomo == OP_RELACIONAL)
            printf("reconhecido Operador relacional - atributo: %s\n", msg_op_relacional[info_atomo.atributo.op_relac]);
        else if (info_atomo.atomo >= ALGORITMO && info_atomo.atomo <= VETOR)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == ADICAO)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == SUBTRACAO)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == MULTIPLICACAO)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == ABRE_COLCHETES)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == FECHA_COLCHETES)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == ABRE_PAR)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == FECHA_PAR)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == ATRIBUICAO)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == PONTO_PONTO)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == PONTO_VIRGULA)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == COMENTARIO_1)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if (info_atomo.atomo == COMENTARIO_2)
            printf("reconhecido %s\n",msg_atomo[info_atomo.atomo]);
        else if(info_atomo.atomo == CONSTANTE_STRING)
            printf("reconhecido CONSTANTE_STRING - atributo: %s\n", info_atomo.atributo.constante);\
        else if(info_atomo.atomo == CONSTANTE_CHAR)
            printf("reconhecido CONSTANTE_CHAR - atributo: %c\n", info_atomo.atributo.constante_char);
        else if (info_atomo.atomo == CONSTANTE_INTEIRO)
            printf("reconhecido CONSTANTE_INTEIRO - atributo: %d\n", info_atomo.atributo.constante_inteiro);
        else if (info_atomo.atomo == CONSTANTE_REAL)
            printf("reconhecido CONSTANTE_REAL - atributo: %f\n", info_atomo.atributo.valor_real);

    }while( info_atomo.atomo != EOS && info_atomo.atomo != ERRO );
    return 0;
}
