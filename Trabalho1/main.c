#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definicao de uma estrutura enumeracao para as constantes dos atomos (Tokens)
typedef enum{
	ERRO,     // erro lexico
	ID,       // identificador
	NUM_INT,  // numero inteiro
	NUM_REAL, // numero real
	EOS       // fim de string
}TAtomo;

// definicao de uma estrutura union para os atributos do atomo (Tokens)
typedef union
{
	char str_id[17];//16+1 para guardar o \0
	int valor_inteiro;
	float valor_real;
}TAtributo;

// definição de uma estrutura para retornar as informações do atomo
// Atomo (token), numero da linha e atributo
typedef struct{
	TAtomo atomo; //Constante representando o átomo
	int linha; //Número da linha onde o átomo foi encontrado
	TAtributo atributo; // atributos para os átomos
}TInfoAtomo;

// Mensagens do compilador indexadas pelos atomos (tokens)
char *msg_atomo[]={
		"Erro Lexico",
		"Identificador",
		"Numero Inteiro",
		"Numero Real",
		"Fim de Buffer"};


// funcao principal do analisador lexico, retorna o atomo reconhecido
// com seus atributos
TInfoAtomo AnaLex(void);

// variaveis globais
char *buffer="\n\n\n     fabio \nlubacheski \n123.1";
char *end_;

int linha=1;

int main( int narg, char ** args)
{
	TInfoAtomo info_atomo;

    // abrir arquivo
    // alocar o buffer_global em funcao do tamanho do arquivo de entrada

	printf("Analisador Lexico versao 1.0\n");

	do{
		info_atomo = AnaLex();
		if( info_atomo.atomo == ID )
            printf("[%d]reconhecido %s - atributo=%s\n", linha,msg_atomo[info_atomo.atomo], info_atomo.atributo.str_id);
        if( info_atomo.atomo == NUM_REAL )
            printf("[%d]reconhecido %s - atributo=%.2f\n", linha,msg_atomo[info_atomo.atomo], info_atomo.atributo.valor_real);
	}while( info_atomo.atomo != EOS && info_atomo.atomo != ERRO );

}
/*
 Reconhece um IDENTIFICADOR
*/
TAtomo reconhece_id()
{

R_ID:

	if(isalpha(*buffer) || isdigit(*buffer)){
		buffer++;
		goto R_ID;
    }

    end_ = buffer;
	return ID;
}
/*
 Reconhece um NUMERO INTEIRO E NUMERO REAL
*/
TAtomo reconhece_num(void)
{
    NUM:
        if (isdigit(*buffer)){
            buffer++;
            goto NUM;
        }
        if (*buffer == '.'){
            buffer++;
            goto NUM_REAL;
        }
        if(!isalpha(*buffer)){
            end_ = buffer;
            return NUM_INT;
        }

    NUM_REAL:
        if(isdigit(*buffer)){
            buffer++;
            goto NUM_REAL;
        }
        if(!isalpha(*buffer)){
            end_ = buffer;
            return NUM_REAL;
        }

	return ERRO;
}
/*
 funcao principal do analisador lexico, retorna o atomo reconhecido
 com seus atributos
*/
TInfoAtomo AnaLex(void)
{
	char c;
	char *init;
	TInfoAtomo info_atomo;

    // ja seta info_atomo com ERRO
	memset(&info_atomo,0,sizeof(info_atomo));

	// trata os caracteres de controle
	while( *buffer==' ' || *buffer=='\n' || *buffer=='\r' ){
		if(*buffer=='\n')
			linha++;

		buffer++;
	}
	info_atomo.linha = linha;

	c = *buffer++;
    init = buffer-1;

	if(isalpha(c)){//[A-Za-z]
		info_atomo.atomo = reconhece_id();
        strncpy(info_atomo.atributo.str_id,init,(end_ - init));
        info_atomo.atributo.str_id[init-end_] = 0;
	}
	else if(isdigit(c)){ // [0-9]
		info_atomo.atomo = reconhece_num();
        if(info_atomo.atomo == NUM_INT){
            char tmp[16];
            strncpy(tmp,init,(end_ - init));
            tmp[end_ - init] = 0;
            info_atomo.atributo.valor_inteiro = atoi(tmp);
        }
        else{
            char tmp[16];
            strncpy(tmp,init,(end_ - init));
            tmp[end_ - init] = 0;
            info_atomo.atributo.valor_real = (float)atof(tmp);
        }

    }
	else if( c == '\0' )
    	info_atomo.atomo = EOS;


	return info_atomo;
}
