#include "sintatico.h"
#include "analex.h"

TInfoAtomo lookahead;

int ordemVar=0;
int ordemParam=0;
void ErroSintaticoComposto(TAtomo * atomos){
    printf("Erro sintatico:[%d] -  Atomo recebido: %s\n",linha,msg_atomo[lookahead.atomo]);
    printf("Atomos esperados: ");
    while(*atomos++ != 0)
        printf(",%s",*atomos);

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
    if(consomeSemErro(NUM_INT));
    else if(consomeSemErro(NUM_REAL));
    else if(consomeSemErro(CARACTERE));
    else if(consomeSemErro(LOGICO));
    else
        ErroSintatico(NUM_INT);
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

}

int operador_adicao(){
    if(consomeSemErro(ADICAO));
    else if(consomeSemErro(SUBTRACAO));
    else if(consomeSemErro(MOD));
    else if(consomeSemErro(OU));
    else{
        TAtomo* atomos = {ADICAO,SUBTRACAO,MOD,OU,0};
        ErroSintaticoComposto(atomos);
    }
    return 1;
}

int oprador_multiplicacao(){
    if(consomeSemErro(MULTIPLICACAO));
    else if(consomeSemErro(DIV));
    else if(consomeSemErro(E));
    else {
        TAtomo* atomos = {MULTIPLICACAO,DIV,E,0};
        ErroSintaticoComposto(atomos);
    }
}

void termo(){
    fator();

}
void expressao_simples(){
    int add = 0;
    if(consomeSemErro(ADICAO));
    else consomeSemErro(SUBTRACAO);
    termo();
    do{
        add = operador_adicao();
        termo();
    }while()
}

void expressao(){
    expressao_simples();
    if(consomeSemErro(OP_RELACIONAL)){
        expressao_simples();
    }
}

int comando_atribuicao(){
    if(consomeSemErro(ID)){
        if(consomeSemErro(ATRIBUICAO)){
            expressao();
            consome(PONTO_VIRGULA);
            return 1;
        }
        return 0;
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

    if(comando_atribuicao() ||
       chamada_procedimento() ||
       comando_se() ||
       comando_enquanto()
       );
        comando(obrigatorio+1);

    if(obrigatorio == 0){
        TAtomo *atomos = {ID,SE,ENQUANTO,0};
        ErroSintaticoComposto(atomos);
    }
}
void declaracao_de_funcao(int obrigatoria){
    //Criar no identificador
    TNoIdentificador id_funcao;
    funcao func;
    adiciona_atomo_lista_atomos(func.listaVariaveis,id_funcao)
    //criar lista de simbolos
    if (obrigatoria == 0){
        consome(FUNCAO);
    }
    else{
        if(consomeSemErro(FUNCAO));
        else
            return;
    }
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
    declaracao_de_funcao(obrigatoria+1);
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
        while(consomeSemErro(VARIAVEIS));
    }
}
void bloco(){
    declaracao_de_variaveis(CAT_VARIAVEL_GLOBAL);
    if (lookahead == FUNCAO){
        do{
            declaracao_de_funcao(0);
        }while (lookahead == FUNCAO)
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
