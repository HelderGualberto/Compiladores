#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//definicoes dos indices referentes a tabela de transicoes

/**
    DESENVOLVIDO POR HELDER RODRIGUES
    ENGENHARIA DA COMPUTACAO
    SETIMO SEMESTRE
**/


#define ESTADO 0
#define LEITURA 1
#define GRAVAR 2
#define MOVER 3
#define NOVO_ESTADO 4


int* getString(FILE* mt){
    char c = getc(mt);
    char *num = malloc(sizeof(char)*2);
    int *out = malloc(sizeof(int)*5);
    int i = 0;
    while(c != '\n' && i < 5){
        if(isdigit(c)){
            num[0] = c;
            c = fgetc(mt);
            if(isdigit(c)){
                num[1] = c;
                out[i] = atoi(num);
            }
            else{
                out[i] = num[0] - '0';
                if(c == '\n')
                    break;
            }
            i++;
        }

        if(isalpha(c) || c=='-'){
            out[i] = c;
            i++;
        }

        c = fgetc(mt);
    }
    /*
    for(i=0;i<5;i++)
        printf("%d ",out[i]);
    printf("\n");
*/
    return out;
}

char * getFita(FILE * mt){
    char c;
    char * fita = calloc(101,sizeof(char));
    int i = 0;
    while(i < 100){
        c = getc(mt);
        if(c == '\n' || c == EOF){
            fita[i] = '-'; //configura o elemento final da fita
            fita[i+1] = '\0';
            return fita;
        }
        else{
            fita[i] = c;
            i++;
        }
    }
    printf("Falha ao construir fita\n");
    exit(EXIT_FAILURE);
}



int main(int argv, char *argc[])
{
    FILE *mt = fopen(argc[1],"r");
    char alfabeto[31];
    int estado_final;
    char c[5];

    //obtem o alfabeto
    memset(alfabeto,'\0',31);
    fgets(alfabeto,30,mt);

    //obtem o numero total de estados
    fgets(c,5,mt);
    estado_final = atoi(c);
    printf("Estado final: %d\n",estado_final);
    //obtem o numero de transicoes para alocacao da tabela de transicoes
    fgets(c,5,mt);
    int ntr = atoi(c);

    int *transicoes[ntr];
    int i;

    //constroi a tabela de transicoes concatenando os simbolos
    for(i = 0;i < ntr;i++){
        transicoes[i] = getString(mt);
    }
    fgets(c,5,mt);

    //npf e numero de palavras para serem detectadas
    int npf = atoi(c);
    char * palavras_fita[npf];

    //for para obter as palavras para deteccao
    //ja efetua a troca do ultimo simbolo (remove \n,\r, mas mantém \0 para faciliat debug) para o simbolo especial '-'
    for(i=0;i<npf;i++){
        palavras_fita[i] = getFita(mt);
    }

    int p = 0;

    //loop para efetuar a validacao de todas as palavras de entrada no arquivo.
    while(p < npf){
        //obtem qual o primeiro estado passado pela tabela de transicoes
        int estado_atual = transicoes[0][0];

        //Faz uma referencia para o inicio da fita
        char *fita = palavras_fita[p];

        //imprime o corpo inicial da mensagem, depois aplica a condicao OK ou NOT OK
        //Essa malandragem evita a alocacao de outra variavel, ou a copia da string

        printf("%d: %s ",p+1,palavras_fita[p]);

        //flag para verificar se a palavra pertence a linguagem
        int pertence;

        PROXIMO_ESTADO:
            /**
                O loop abaixo tem a funcao de efetuar a validacao das palavras de entrada
                A iteracao vai ate percorrer toda a tabela de transicoes, caso nenhuma transicao seja encontrada
                a palavra e diretamente rejeitada.
                Caso seja encontrado inicia-se o procedimento descrito pela tabela de simbolos
            **/
            for(i = 0;i < ntr;i++){
                pertence = 0;
                if(estado_atual == estado_final){
                    pertence = 1;
                    break;
                }
                //busca as condicoes referente ao estado atual na tabela de transicoes
                if(transicoes[i][ESTADO] == estado_atual){

                    //verifica se o caractere esperado da tabela de transicoes e igual ao da posicao atual da fita
                    if((char)transicoes[i][LEITURA] == *fita){

                        //grava o simbolo an fita de acordo com a tabela de transicoes
                        *fita = (char)transicoes[i][GRAVAR];

                        //atualiza o estado atual de acordo com a tabela de transicoes
                        estado_atual = transicoes[i][NOVO_ESTADO];

                        //verifica o lado para que a fita deve seguir
                        if((char)transicoes[i][MOVER] == 'D')
                            fita++;
                        else if((char)transicoes[i][MOVER] == 'E')
                            fita--;
                        else{
                            printf("\nTabela de transicoes incorreta\n");
                            exit(EXIT_FAILURE);
                        }
                        //reprete o processo para o proximo caractere da fita
                        goto PROXIMO_ESTADO;
                    }
                }
            }
        /*
            OBS: A mensagem final impressa inclui o caractere de finalizacao da palavra '-'
            Portanto, uma palavra vazia imprimira apenas o simbolo '-'
        */
        if(pertence)
            printf("OK\n");
        else
            printf("NOT OK\n");

        p++;
    }
    return 0;
}
