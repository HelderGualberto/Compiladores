#include "sintatico.h"
#include "analex.h"

TInfoAtomo lookahead;

int ordemVar=0;
int ordemParam=0;
void lista_expressao();
void expressao();
void comando(int);
void declaracao_de_variaveis(TAtomo);
void initTabSimbolos();

void ErroSintaticoComposto(TAtomo * atomos){
    printf("Erro sintatico:[%d] -  Atomo recebido: %s\n",linha,msg_atomo[lookahead.atomo]);
    while(*atomos++ != -1)
        if(*atomos != -1)
        printf("Atomo esperado: %s\n",msg_atomo[*atomos]);

    exit(EXIT_FAILURE);
}

void ErroSintatico(TAtomo atomoEsperado){
    printf("Erro sintatico:[%d] -  Atomo esperado: %s - Atomo recebido: %s\n",linha,msg_atomo[atomoEsperado],msg_atomo[lookahead.atomo]);
    exit(EXIT_FAILURE);
}
void ErroLexico(){
    printf("Erro Lexico:[%d]\n",linha);
    exit(EXIT_FAILURE);
}

void consome(TAtomo atomoEsperado){
    if(atomoEsperado == lookahead.atomo){
        lookahead = AnaLex();
        printf("Consumido: %s\n",msg_atomo[lookahead.atomo]);
    }
    else if(lookahead.atomo == ERRO){
        ErroLexico();
    }
    else
        ErroSintatico(atomoEsperado);
}

int consomeSemErro(TAtomo atomoEsperado){
   if(atomoEsperado == lookahead.atomo){
        lookahead = AnaLex();
        printf("Consumido: %s\n",msg_atomo[lookahead.atomo]);
        return 1;
    }
    else if(lookahead.atomo == ERRO){
        ErroLexico();
    }
    return 0;
}

void v_tipo_simples(){
    if(consomeSemErro(INTEIRO));
    else if(consomeSemErro(REAL));
    else if(consomeSemErro(CARACTERE));
    else if(consomeSemErro(LOGICO));
    else{
        TAtomo atomos[5] = {NUM_INT,NUM_REAL,CARACTERE,LOGICO,0};
        ErroSintaticoComposto(atomos);
    }
}

int v_tipo_composto(){
    if(consomeSemErro(VETOR)){
        consome(ABRE_COLCHETES);
        consome(NUM_INT);
        consome(PONTO_PONTO);
        consome(NUM_INT);
        consome(FECHA_COLCHETES);
        v_tipo_simples();
        return 1;
    }
    return 0;
}


void tipos(){
    if(v_tipo_composto()) return;
    v_tipo_simples();
}
void parametros_formais(){
    do{
        consomeSemErro(REF);
        consome(ID);
        v_tipo_simples();
    }while(consomeSemErro(PONTO_VIRGULA));
}

int operador_adicao(){
    if(consomeSemErro(ADICAO));
    else if(consomeSemErro(SUBTRACAO));
    else if(consomeSemErro(MOD));
    else if(consomeSemErro(OU));
    else{
       return 0;
    }
    return 1;
}

int operador_multiplicacao(){
    if(consomeSemErro(MULTIPLICACAO));
    else if(consomeSemErro(DIV));
    else if(consomeSemErro(E));
    else {
        return 0;
    }
    return 1;
}

void fator(){
    if(consomeSemErro(ID)){
        if(lookahead.atomo == ABRE_PAR){
            consome(ABRE_PAR);
            lista_expressao();
            consome(FECHA_PAR);
            return;
        }
    }
    else if(consomeSemErro(NUM_INT));
    else if(consomeSemErro(NUM_REAL));
    else if(consomeSemErro(CARACTERE));
    else if(consomeSemErro(CONSTANTE_STRING));
    else if(consomeSemErro(FALSO));
    else if(consomeSemErro(NAO));
    else if(consomeSemErro(ABRE_PAR)){
        expressao();
        consome(FECHA_PAR);
    }
    else{
        TAtomo atomos[7] = {NUM_INT,NUM_REAL,CARACTERE,CONSTANTE_STRING,FALSO,NAO,-1};
        ErroSintaticoComposto(atomos);
    }
}


void termo(){
    fator();
    if(!operador_multiplicacao()){
        TAtomo atomos[4] = {MULTIPLICACAO,DIV,E,-1};
        ErroSintaticoComposto(atomos);
    }
    fator();
    while(operador_multiplicacao()){
        fator();
    }
}

void lista_expressao(){
    expressao();
    while(lookahead.atomo == PONTO_VIRGULA){
        consome(PONTO_VIRGULA);
        expressao();
    }
}

void expressao_simples(){
    if(consomeSemErro(ADICAO));
    else consomeSemErro(SUBTRACAO);
    termo();
    if(!operador_adicao()){
        TAtomo atomos[5] = {ADICAO,SUBTRACAO,MOD,OU,-1};
        ErroSintaticoComposto(atomos);
    }
    termo();
    while(operador_adicao()){
        termo();
    }
}

void expressao(){
    expressao_simples();
    if(consomeSemErro(OP_RELACIONAL)){
        expressao_simples();
    }
}

int comando_atribuicao(){
    if(consomeSemErro(ATRIBUICAO)){
        expressao();
        consome(PONTO_VIRGULA);
        return 1;
    }
    return 0;
}

int chamada_procedimento(){
    consome(ABRE_PAR);
    lista_expressao();
    consome(PONTO_VIRGULA);
    return 1;
}
int comando_se(){
    if(consomeSemErro(SE)){
        expressao();
        consome(ENTAO);
        comando(0);
        if(consomeSemErro(SENAO))
            comando(0);
        consome(FIM);
        consome(SE);
        return 1;
    }
    return 0;
}
int comando_enquanto(){
    if(consomeSemErro(ENQUANTO)){
        expressao();
        consome(FACA);
        comando(0);
        consome(FIM);
        consome(ENQUANTO);
        return 1;
    }
    return 0;
}
void comando(int obrigatorio){
    if(lookahead.atomo == ID){
        consome(ID);
        if(lookahead.atomo == ATRIBUICAO){
            comando_atribuicao();
            comando(obrigatorio+1);
        }
        else{
            chamada_procedimento();
            comando(obrigatorio+1);
        }
    }
    else if(lookahead.atomo == SE){
        comando_se();
        comando(obrigatorio+1);
    }
    else if(lookahead.atomo == ENQUANTO){
        comando_enquanto();
        comando(obrigatorio+1);
    }
    else if(obrigatorio == 0){
        TAtomo atomos[4] = {ID,SE,ENQUANTO,-1};
        ErroSintaticoComposto(atomos);
    }
}
void declaracao_de_funcao(int obrigatoria){
    //Criar no identificador
    //criar lista de simbolos
    consome(FUNCAO);
    consome(ID);
    consome(ABRE_PAR);
    //adicionar identificador para no identificador

    parametros_formais();
    //adicionar lista de parametros

    consome(FECHA_PAR);
    consome(PONTO_VIRGULA);

    v_tipo_simples();
    //adicionar tipo de retorno a funcao

    declaracao_de_variaveis(CAT_VARIAVEL_LOCAL);
    //adicionar tipo lista de variaveis a funcao

    consome(INICIO);
    comando(0);
    consome(FIM);
    consome(FUNCAO);
}

void declaracao_de_variaveis(TAtomo localORglobal){
    if(consomeSemErro(VARIAVEIS)){
        do {
            TNoIdentificador id_var;
            variavel var;
            var.ordem_declaracao = ordemVar++;

            consome(ID);
            id_var.identificador = lookahead.atributo.str_id;
            tipos();
            var.tipo_variavel = lookahead.atomo;

            id_var.tipo_atributo = localORglobal;
            id_var.conjunto_atributos.var = var;

            consome(PONTO_VIRGULA);
            adiciona_atomo_lista_hash(&id_var);
        }while(lookahead.atomo == ID);
    }
}
void bloco(){
    declaracao_de_variaveis(CAT_VARIAVEL_GLOBAL);
    if (lookahead.atomo == FUNCAO){
        do{
            declaracao_de_funcao(0);
        }while (lookahead.atomo == FUNCAO);
    }
    consome(INICIO);
    comando(0);
    consome(FIM);
}
void programa(){
    consome(ALGORITMO);
    consome(ID);
    bloco();
    consome(EOS);
}


void AnaSintatico(){

    initTabSimbolos();
    lookahead = AnaLex();
    programa();

}
