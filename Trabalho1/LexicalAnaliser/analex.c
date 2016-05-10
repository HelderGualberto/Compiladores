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


#include "analex.h"
/*
    Todas as definicoes, unioes e estruturas estao localizadas no arquivo definitions.h
*/
// Definicao de uma estrutura enumeracao para as constantes dos atomos (Tokens)


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
    "VETOR",
    "ERRO LEXICO",
    "IDENTIFICADOR",
    "CONSTANTE INTEIRO",
    "CONSTANTE REAL",
    "FIM DE BUFFER",
    "OPERADOR RELACIONAL",
    "COMENTARIO 1",
    "COMENTARIO 2",
    "SUBTRACAO",
    "ADICAO",
    "MULTIPLICACAO",
    "ABRE PARENTESES",
    "ATRIBUICAO",
    "FECHA PARENTESES",
    "PONTO VIRGULA",
    "PONTO PONTO",
    "ABRE COLCHETES",
    "FECHA COLCHETES",
    "CONSTANTE STRING",
};
// funcao principal do analisador lexico, retorna o atomo reconhecido
// com seus atributos
TInfoAtomo AnaLex(void);

// variaveis globais
char *buffer;
char *end_;
int linha=1;

// abrir arquivo
// alocar o buffer_global em funcao do tamanho do arquivo de entrada

char * read_file(FILE* input){

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
    return buffer;
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
    if (*buffer == ','){
        buffer++;
        goto NUM_REAL;
    }
    if (*buffer == '^'){
        buffer++;
        goto CONSTANTE_INTEIRO;
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
    if (*buffer == '^'){
        buffer++;
        goto CONSTANTE_INTEIRO;
    }
    if(!isalpha(*buffer)){
        end_ = buffer;
        return NUM_REAL;
    }

CONSTANTE_INTEIRO:

    if (*buffer == '+' || isdigit(*buffer) || *buffer == '-'){
        buffer++;
        goto CONSTANTE_INTEIRO;

    }
    if(!isalpha(*buffer)){
        end_ = buffer;
        return NUM_INT;
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

//Funcao que verifica se o atomo detectado È uma plavra reservada ou nao
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
TAtomo reconheceAtomoSimples(){
    buffer--;
    if (*buffer == '=') return ATRIBUICAO;
    else if (*buffer == '.')  return PONTO_PONTO;
    else if (*buffer == '(') return ABRE_PAR;
    else if (*buffer == ')') return FECHA_PAR;
    else if (*buffer == '[') return ABRE_COLCHETES;
    else if (*buffer == ']') return FECHA_COLCHETES;
    else if (*buffer == ';') return PONTO_VIRGULA;
    return ERRO;
}

//Funcao que verifica se o lexema analisado È um operador relacional
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

//Funcao que verifica se o lexema È um operador aritmetico
int isOpAritmetico(char c){
    if(c == '+' || c == '-' || c == '*'){
        return 1;
    }
    return 0;
}

//Reconhece qual o operador aritmetico encontrado
TAtomo reconheceOpAritmetico(){
    buffer--;
    if(*buffer == '+') return ADICAO;
    else if (*buffer == '-') return SUBTRACAO;
    else if (*buffer == '*') return MULTIPLICACAO;
    return ERRO;
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
TAtomo reconheceComentario(){
    buffer--;

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
        buffer++;
        return COMENTARIO_1;
    }
    else{
        buffer++;
        if(*buffer == '\n' || *buffer == '\r')
            linha++;
        goto COMENT_1;
    }


COMENT_2:

    if(*buffer != '}'){
        buffer++;
        goto COMENT_2;
    }
    else{
        buffer++;
        return COMENTARIO_2;
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
        if((end_-init) > 16)
            info_atomo.atomo = ERRO;
        else{
            char tmp[16];
            strncpy(tmp,init,(end_ - init));
            tmp[end_ - init] = 0;
            int pr = verifica_palavra_reservada(tmp);
            //Soma-se 1 na condicao pois o retorno da funcao
            //e referente ao indice da palavra reservada encontrada
            //Desta forma ao nao encontrar nenhuma palavra reservada, retorna-se -1
            if(pr+1){
                info_atomo.atomo = pr;
            }
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
        else if (info_atomo.atomo == NUM_INT){
            strncpy(info_atomo.atributo.str_id,init,(end_ - init));

            char *a = info_atomo.atributo.constante;
            char base[16];
            char expoente[16];
            int x = 0;
            while(*a != 0){
                if(*a == ','){
                    a++;
                    base[x] = '.';
                    x++;
                    info_atomo.atomo = NUM_REAL;
                }
                if (*a == '^'){
                    a++;
                    break;
                }
                base[x] = *a;
                x++;
                a++;
            }
            x = 0;
            while(*a != 0){
                expoente[x] = *a;
                x++;
                a++;
            }
            int expoente_int = atoi(expoente);

            if (info_atomo.atomo == NUM_REAL){
                float base_float = atof(base);
                info_atomo.atributo.valor_real = pow(base_float, expoente_int);

            }
            else {
                int base_int = atoi(base);
                info_atomo.atributo.valor_inteiro = pow(base_int, expoente_int);

            }
            //AJUSTAR O CODIGO AQUI
        }
        else{
            char tmp[17];
            strncpy(tmp,init,(end_ - init));
            tmp[end_ - init] = 0;
            info_atomo.atributo.valor_real = (float)atof(tmp);
        }
    }
    else if(isComentario(c)){
        info_atomo.atomo = reconheceComentario();
        buffer++;
    }
    else if(isAtomoSimples(c)){
        info_atomo.atomo = reconheceAtomoSimples();
        buffer++;
    }
    else if(isOpRelacional(c)){
        info_atomo.atomo = OP_RELACIONAL;
        info_atomo.atributo.op_relac = reconheceOpRelacional();
        buffer++;
    }
    else if(isOpAritmetico(c)){
        info_atomo.atomo = reconheceOpAritmetico();
        buffer++;
    }
    else if (c == '"'){
        //string para uma constante do tipo string
        int x = 0 ;
        do {
            if (c == '\n' || x >= 32){
                info_atomo.atomo = ERRO;
                break;
            }

            info_atomo.atributo.constante[x] = *buffer;
            x++;
            buffer++;
        }while (*buffer != '"');
        if (x < 32){
            info_atomo.atomo = CONSTANTE_STRING;
        }
        buffer++;
    } else if (c == 39){
        info_atomo.atomo = CARACTERE;
        info_atomo.atributo.constante_char = *buffer;
        buffer++;
        if (*buffer != '\''){
            info_atomo.atomo = ERRO;
        }
        buffer++;

    }
    else if( c == '\0' )
        info_atomo.atomo = EOS;

    return info_atomo;
}



