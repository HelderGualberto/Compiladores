#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Mensagens do compilador indexadas pelos atomos (tokens)
char *msg_atomo[]={
		"Erro Lexico",
		"Identificador",
		"Numero Inteiro",
		"Numero Real",
		"Fim de Buffer",
		"Abre parenteses",
        "Atribuicao",
        "Fecha parenteses",
        "Ponto e virgula",
        "Ponto e ponto",
        "Abre colchetes",
        "Fecha colchetes",
        "Subtracao",
        "Adicao",
        "Multiplicacao"
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

// Mensagens para referenciar o operador Aritimetico identificado
char *msg_op_aritimetico[]={
        "SUBTRACAO",
        "ADICAO",
        "MULTIPLICACAO"
};

// Mensagens para referenciar o atomo simples identificado
char *msg_atomo_simples[]={
    "ABRE_PAR",
	"ATRIBUICAO",
	"FECHA_PAR",
	"PONTO_VIRGULA",
	"PONTO_PONTO",
	"ABRE_COLCHETES",
	"FECHA_COLCHETES"
};

char *msg_comentario[]={
    "COMENTARIO_1",
	"COMENTARIO_2"
};

// Definicao de uma estrutura enumeracao para as constantes dos atomos (Tokens)
typedef enum{
	ERRO,     // erro lexico
	ID,       // identificador
	NUM_INT,  // numero inteiro
	NUM_REAL, // numero real
	EOS, // fim de string
	ATOMO_SIMPLES,
	OP_ARITIMTICA,
	OP_RELACIONAL,
	COMENTARIO

}TAtomo;

//Define os tipos de Operacoes aritimeticas simples
typedef enum{
    ERRO_ARITMETICO,
	SUBTRACAO,
	ADICAO,
	MULTIPLICACAO
}AtrOpAritmetica;

//Define os tipos de Atomos simples possiveis
typedef enum{
    ABRE_PAR,
	ATRIBUICAO,
	FECHA_PAR,
	PONTO_VIRGULA,
	PONTO_PONTO,
	ABRE_COLCHETES,
	FECHA_COLCHETES
}AtrAtomoSimples;

//Define os tipos de comentarios possiveis
typedef enum{
    COMENTARIO_1,
	COMENTARIO_2
}TipoDeComentario;

//Definicao de um enum para referenciar os operadores relacionais
typedef enum{
    ME,
    MEI,
    IG,
    DI,
    MA,
    MAI
}AtrOpRelacional;

//DEFINICAO DE UMA ESTRUTURA PARA MANTER UM COMENTARIO
typedef struct {
    TipoDeComentario tipo_coment;
    int num_de_linhas;
}Coment;

// definicao de uma estrutura union para os atributos do atomo (Tokens)
typedef union
{
	char str_id[17];//16+1 para guardar o \0
	int valor_inteiro;
	float valor_real;
	Coment comentario;
	AtrOpRelacional op_relac;
    AtrOpAritmetica op_arit;
    AtrAtomoSimples atm_simples;

}TAtributo;

// definição de uma estrutura para retornar as informações do atomo
// Atomo (token), numero da linha e atributo
typedef struct{
	TAtomo atomo; //Constante representando o átomo
	int linha; //Número da linha onde o átomo foi encontrado
	TAtributo atributo; // atributos para os átomos
}TInfoAtomo;


// funcao principal do analisador lexico, retorna o atomo reconhecido
// com seus atributos
TInfoAtomo AnaLex(void);

// variaveis globais
char *buffer;
char *end_;
int linha=1;

 // abrir arquivo
 // alocar o buffer_global em funcao do tamanho do arquivo de entrada

void read_file(FILE* input){

    fseek(input, 0, SEEK_END); // Envia a referencia de leitura do arquivo para o fim do arquivo
    int fsize = ftell(input); // retorna o numero de caracteres ate o ponto atual do arquivo
    fseek(input, 0, SEEK_SET);// retorna para o inicio do arquivo
    printf("Tamanho: %d\n",fsize);

    buffer = malloc(sizeof(char)*(fsize));
    int i=0;int n_carbit = 0;
    char c = fgetc(input);
    while(c != EOF){
        buffer[i] = c;
        i++;
        if(c == '\n')
            n_carbit++;
        c = fgetc(input);
    }
    buffer[fsize - n_carbit] = 0;
}



int main( int narg, char ** args)
{
    //codigo para entrada do caminho do arquivo via linha de comando
    char * caminho_entrada = malloc(sizeof(char)*30);
    FILE* arquivo_entrada;
    do{
        printf("Entre com o caminho do arquivo\nCaminho: ");
        scanf("%s",caminho_entrada);
        arquivo_entrada = fopen(caminho_entrada,"r");
        if(arquivo_entrada == NULL)
            printf("Caminho nao encontrado!\n");
    }while(arquivo_entrada == NULL);

    read_file(arquivo_entrada);

	TInfoAtomo info_atomo;

	printf("Analisador Lexico versao 1.0\n");

	do{
		info_atomo = AnaLex();
		if( info_atomo.atomo == ID )
            printf("[%d]reconhecido %s - atributo=%s\n", linha,msg_atomo[info_atomo.atomo], info_atomo.atributo.str_id);
        else if( info_atomo.atomo == NUM_REAL )
            printf("[%d]reconhecido %s - atributo=%.2f\n", linha,msg_atomo[info_atomo.atomo], info_atomo.atributo.valor_real);
        else if(info_atomo.atomo == NUM_INT)
            printf("[%d]reconhecido %s - atributo=%d\n",linha,msg_atomo[info_atomo.atomo],info_atomo.atributo.valor_inteiro);
        else if(info_atomo.atomo == ERRO)
            printf("[%d]%s\n",info_atomo.linha,msg_atomo[info_atomo.atomo]);
        else if(info_atomo.atomo == OP_RELACIONAL)
            printf("[%d]reconhecido Operador relacional - atributo: %s\n", linha,msg_op_relacional[info_atomo.atributo.op_relac]);
        else if(info_atomo.atomo == OP_ARITIMTICA)
            printf("[%d]reconhecido Operador aritimetico - atributo: %s\n", linha,msg_op_aritimetico[info_atomo.atributo.op_arit]);
        else if(info_atomo.atomo == ATOMO_SIMPLES)
            printf("[%d]reconhecido Atomo simples - atributo: %s\n", linha,msg_atomo_simples[info_atomo.atributo.atm_simples]);
        else if(info_atomo.atomo == COMENTARIO)
            printf("[%d]reconhecido %s - Numero de linhas: %d\n", linha,msg_comentario[info_atomo.atributo.comentario.tipo_coment],info_atomo.atributo.comentario.num_de_linhas);
	}while( info_atomo.atomo != EOS && info_atomo.atomo != ERRO );
    return 0;
}
/*
 Reconhece um IDENTIFICADOR
*/
TAtomo reconhece_id()
{

R_ID:
	if(isalpha(*buffer) || isdigit(*buffer) || *buffer == '_'){
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
//funcao para obtero tamanho de uma string
int get_size(char *palavra){
    int s = 0;
    while(palavra[s] != 0)
        s++;
    return s;
}

//compara duas strings sem considerar o caso. Alem disso retorna um inteiro para cada condicao, ou seja, -1 para que a palavra
//analisada tenha posicao alfabetica inferior a palavra referencia, 0 para palavras iguais e 1 para que a palavra analisada tenha
// posicao alfabetica superior a palavra referencia. Onde s2 deve ser a palavra referencia
int cmp_string(char *s1,char* s2){
    int i=0;
    char std_char;

    while(s1[i] != 0 || s2[i] != 0){
        if(s1[i] > 90)
            std_char = s1[i]-32;
        else
            std_char = s1[i];

        if(s1[i] == s2[i] || (s1[i]-32) == s2[i]);
        else
            if(std_char > s2[i])
                return 1;
            else return -1;
        i++;
    }
    return 0;
}

//Funcao que verifica se o atomo detectado é uma plavra reservada ou nao
int verifica_palavra_reservada(char *palavra){
    int inf=0;
    int sup=23;
    int index;
    //loop para execucao de busca binaria
    while(1){
        index =(sup+inf)/2;
        //compara as palavras
        int cmp = cmp_string(palavra,palavras_reservadas[index]);
        if(!cmp)
        //Se a palavra e reservada, retorna-se asua posicao no vetor de palavras reservadas
            return index;
        if(sup<inf)
            break;
        else if(cmp == 1){
            inf = index+1;
        }
        else if(cmp == -1)
            sup=index-1;
    }
    //se a palavra nao e reservada, retorna-se -1
    return -1;
}

//Funcao que verifica se o lexema pertence a um atomo simples
int isAtomoSimples(char c){
    if(c == '(' ||
       c == ')' ||
       c == '[' ||
       c == ']' ||
       c == ';'){
        return 1;
       }

    if(c == ':'){
        if(*buffer == '='){
            buffer++;
            return 1;
        }
    }
    if(c == '.'){
        if(*buffer == '.'){
            buffer++;
            return 1;
        }
    }
    return 0;
}

//Funcao para reconhecer qual o atomo simples foi detectado, e retorna o respectivo TAtomo
AtrAtomoSimples reconheceAtomoSimples(){
    buffer--;
    if (*buffer == '=') return ATRIBUICAO;
    else if (*buffer == '.')  return PONTO_PONTO;
    else if (*buffer == '(') return ABRE_PAR;
    else if (*buffer == ')') return FECHA_PAR;
    else if (*buffer == '[') return ABRE_COLCHETES;
    else if (*buffer == ']') return FECHA_COLCHETES;
    else if (*buffer == ';') return PONTO_VIRGULA;
    return -1;
}

//Funcao que verifica se o lexema analisado é um operador relacional
int isOpRelacional(char c){

    if(c == '<' && *buffer == '='){
        buffer++;
        return 1;
    }
    if(c == '>' && *buffer == '='){
        buffer++;
        return 1;
    }

    if(c == '<' ||
       c == '=' ||
       c == '#' ||
       c == '>') {
        return 1;
       }
    return 0;
}

//Reconhece qual o operador relacional encontrado
AtrOpRelacional reconheceOpRelacional(){
    buffer--;
    if(*buffer == '='){
        buffer--;
        if(*buffer == '>'){
            buffer++;
            return MAI;
        }
        else if(*buffer == '<'){
            buffer++;
            return MEI;
        }
        buffer++;
    }
    if(*buffer == '<') return ME;
    else if(*buffer == '>') return MA;
    else if(*buffer == '=') return IG;
    else if(*buffer == '#') return DI;
    return -1;
}

//Funcao que verifica se o lexema é um operador aritmetico
int isOpAritmetico(char c){
    if(c == '+' || c == '-' || c == '*'){
        return 1;
    }
    return 0;
}

//Reconhece qual o operador aritmetico encontrado
AtrOpAritmetica reconheceOpAritmetico(){
    buffer--;
    if(*buffer == '+') return ADICAO;
    else if (*buffer == '-') return SUBTRACAO;
    else if (*buffer == '*') return MULTIPLICACAO;
    return -1;
}

//verifica se o atomo e referente a um comentario
int isComentario(char c){
    if(c == '{')
        return 1;
    if(c == '(' && *buffer == '*'){
        buffer++;
        return 1;
    }
    return 0;
}

//reconhece o tipo de comentario
Coment reconheceComentario(){
    buffer--;
    Coment c;

    memset(&c,0,sizeof(Coment));
    int lines = 1;

    if(*buffer == '*') {
        buffer++;
        goto COMENT_1;
    }
    if(*buffer == '{'){
        buffer++;
        goto COMENT_2;
    }

    COMENT_1:

        if (*buffer++ == '*' && *buffer == ')'){
            c.num_de_linhas = lines;
            c.tipo_coment = COMENTARIO_1;
            buffer++;
            return c;
        }
        else{
            buffer++;
            if(*buffer == '\n' || *buffer == '\r')
                lines++;
            goto COMENT_1;
        }


    COMENT_2:

        if(*buffer != '}'){
            buffer++;
            goto COMENT_2;
        }
        else{
            buffer++;
            c.num_de_linhas = lines;
            c.tipo_coment = COMENTARIO_2;
            return c;
        }
    c.tipo_coment = -1;
    return c;

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
		if((end_-init) > 16)
            info_atomo.atomo = ERRO;
        else{
            char tmp[16];
            strncpy(tmp,init,(end_ - init));
            tmp[end_ - init] = 0;
            int pr = verifica_palavra_reservada(tmp);
            if(pr+1)
                strncpy(info_atomo.atributo.str_id,palavras_reservadas[pr],17);

            else{
                strncpy(info_atomo.atributo.str_id,init,(end_ - init));
                info_atomo.atributo.str_id[end_ - init] = 0;
            }
        }
	}
	else if(isdigit(c)){ // [0-9]
		info_atomo.atomo = reconhece_num();
		if((end_-init) > 16)
            info_atomo.atomo = ERRO;

        else if(info_atomo.atomo == NUM_INT){
            char tmp[17];
            strncpy(tmp,init,(end_ - init));
            tmp[end_ - init] = 0;
            info_atomo.atributo.valor_inteiro = atoi(tmp);
        }
        else{
            char tmp[17];
            strncpy(tmp,init,(end_ - init));
            tmp[end_ - init] = 0;
            info_atomo.atributo.valor_real = (float)atof(tmp);
        }
	}
    else if(isComentario(c)){
        Coment com = reconheceComentario();
        if(com.tipo_coment == -1)
            info_atomo.atomo = ERRO;
        else{
            info_atomo.atomo = COMENTARIO;
            info_atomo.atributo.comentario = com;
            buffer++;
        }

    }
    else if(isAtomoSimples(c)){
        info_atomo.atomo = ATOMO_SIMPLES;
        info_atomo.atributo.atm_simples = reconheceAtomoSimples();
        buffer++;
    }
    else if(isOpRelacional(c)){
        info_atomo.atomo = OP_RELACIONAL;
        info_atomo.atributo.op_relac = reconheceOpRelacional();
        buffer++;
    }
    else if(isOpAritmetico(c)){
        info_atomo.atomo = OP_ARITIMTICA;
        info_atomo.atributo.op_arit = reconheceOpAritmetico();
        buffer++;
    }
    else if( c == '\0' )
    	info_atomo.atomo = EOS;

	return info_atomo;
}



