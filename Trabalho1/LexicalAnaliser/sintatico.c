#include "sintatico.h"
#include "analex.h"

TInfoAtomo lookahead;

int ordemVar=0;
int ordemParam=0;
void lista_expressao();
void expressao();
int comando();
void declaracao_de_variaveis(TAtomo , TListaTabSimbolos *);
void initTabSimbolos();
int declaracao_de_procedimento();
int declaracao_de_funcao();

void ErroSintaticoComposto(TAtomo * atomos){
    printf("Erro sintatico:[%d] -  Atomo recebido: %s\n",linha,msg_atomo[lookahead.atomo]);
    while(*atomos != ERRO){
        printf("Atomo esperado: %s\n",msg_atomo[*atomos]);
        atomos++;
    }
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
    while(lookahead.atomo == COMENTARIO_1 ||
          lookahead.atomo == COMENTARIO_2   ){
        lookahead = AnaLex();
    }

    if(atomoEsperado == lookahead.atomo){
        printf("Consumido: %s\n",msg_atomo[lookahead.atomo]);
        lookahead = AnaLex();
    }
    else if(lookahead.atomo == ERRO){
        ErroLexico();
    }

    else
        ErroSintatico(atomoEsperado);

}

int consomeSemErro(TAtomo atomoEsperado){
   while(lookahead.atomo == COMENTARIO_1 ||
          lookahead.atomo == COMENTARIO_2   ){
        lookahead = AnaLex();
   }
   if(atomoEsperado == lookahead.atomo){
        printf("Consumido: %s\n",msg_atomo[lookahead.atomo]);
        lookahead = AnaLex();
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
    else if(consomeSemErro(COMENTARIO_2));
    else if(consomeSemErro(COMENTARIO_1));
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

void parametros_formais(TListaTabSimbolos *listaSimbolos){
    int isRef = 0;
    do{
        parametro *par = novo_parametro();
        TNoIdentificador *novo_no = novo_TNoIdentificador();
        if (lookahead.atomo == REF){
            isRef = 1;
        }
        consomeSemErro(REF);
        strcpy (novo_no->identificador,lookahead.atributo.str_id);
        consome(ID);
    if (isRef){
        par->passagem = REF;
    } else {
        par->passagem = ERRO;

    }

    par->tipo_parametro =lookahead.atomo;

    v_tipo_simples();
    novo_no->conjunto_atributos.par = par;
    novo_no->tipo_atributo = CAT_PARAMETRO;
    adiciona_atomo_lista_atomos(listaSimbolos, novo_no);
    }while(consomeSemErro(PONTO_VIRGULA));
}

int operador_adicao(){
    if(consomeSemErro(ADICAO));
    else if(consomeSemErro(SUBTRACAO));
    else if(consomeSemErro(MOD));
    else if(consomeSemErro(COMENTARIO_2));
    else if(consomeSemErro(COMENTARIO_1));
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
        TAtomo atomos[7] = {NUM_INT,NUM_REAL,CARACTERE,CONSTANTE_STRING,FALSO,NAO,ERRO};
        ErroSintaticoComposto(atomos);
    }
}
void termo(){
    fator();
    while(operador_multiplicacao()){
        fator();
    }
}

void declaracao_de_rotina(){
    if(declaracao_de_procedimento());
    else if(declaracao_de_funcao());
    else{
        TAtomo atomos[3]= {FUNCAO,PROCEDIMENTO,ERRO};
        ErroSintaticoComposto(atomos);
    }
}

int declaracao_de_procedimento(){

    /*

    ADICIONAR DECLARACAO DE PROCEDIMENTO DETRO DO HASH
    INCLUIR LISTA DE PARAMETROS
    INCLUIR LISTA DE VARIAVEIS

    */
    if(consomeSemErro(PROCEDIMENTO)){
            procedimento *proc = novo_procedimento();
        if (lookahead.atomo == ID){
            TNoIdentificador *id_var = novo_TNoIdentificador();
            procedimento *proc = novo_procedimento();
            id_var->tipo_atributo = CAT_PROCEDIMENTO;
            strcpy (id_var->identificador,lookahead.atributo.str_id);
            id_var->conjunto_atributos.procedimento = proc;

        }
        consome(ID);
        consome(ABRE_PAR);
        parametros_formais(proc->listaParametros);
        consome(FECHA_PAR);
        declaracao_de_variaveis(CAT_VARIAVEL_LOCAL, proc->listaVariaveis);
        consome(INICIO);
        while(comando());
        consome(FIM);
        consome(PROCEDIMENTO);
        return 1;
    }
    return 0;
}

void lista_expressao(){
    expressao();
    while(consomeSemErro(PONTO_VIRGULA)){
        expressao();
    }
}

void expressao_simples(){
    if(consomeSemErro(ADICAO));
    else consomeSemErro(SUBTRACAO);
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

void comando_atribuicao(){
    consome(ATRIBUICAO);
    expressao();
    consome(PONTO_VIRGULA);
}

int chamada_procedimento(){
    consome(ABRE_PAR);
    lista_expressao();
    consome(FECHA_PAR);
    consome(PONTO_VIRGULA);
    return 1;
}

void comando_se(){
    expressao();
    consome(ENTAO);
    while(comando());
    if(consomeSemErro(SENAO))
        while(comando());
    consome(FIM);
    consome(SE);
}

void comando_enquanto(){
    expressao();
    consome(FACA);
    while(comando());
    consome(FIM);
    consome(ENQUANTO);
}

int comando(){
    if(consomeSemErro(ID)){
        if(lookahead.atomo == ATRIBUICAO){
            comando_atribuicao();
        }
        else if(lookahead.atomo == ABRE_PAR){
            chamada_procedimento();
        }
        else{
            TAtomo atomos[3] = {ATRIBUICAO,ABRE_PAR,ERRO};
            ErroSintaticoComposto(atomos);
        }
        return 1;
    }
    else if(consomeSemErro(SE)){
        comando_se();
        return 1;
    }
    else if(consomeSemErro(ENQUANTO)){
        comando_enquanto();
        return 1;
    }
    return 0;
}
int declaracao_de_funcao(){
    //Criar no identificador
    //criar lista de simbolos

    /*
        INCLUIR A LISTA DE PARAMETROS NO HASH
    */


    if(consomeSemErro(FUNCAO)){
        TAtomo atomos[5] = {NUM_INT,NUM_REAL,CARACTERE,LOGICO,0};
        TNoIdentificador *id_var = novo_TNoIdentificador();
        funcao *func = nova_funcao();
        id_var->tipo_atributo = CAT_FUNCAO;
        strcpy (id_var->identificador,lookahead.atributo.str_id);
        id_var->conjunto_atributos.func = func;
        consome(ID);
        consome(ABRE_PAR);

        //adicionar identificador para no identificador
        parametros_formais(func->listaParametros);
        //adicionar lista de parametros
        consome(FECHA_PAR);
        consome(PONTO_VIRGULA);
        switch (lookahead.atomo){
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
        func->tipo_de_retorno = lookahead.atomo;
        consome(lookahead.atomo);
        break;
        default:
            ErroSintaticoComposto(atomos);
        break;
        }
        declaracao_de_variaveis(CAT_VARIAVEL_LOCAL, func->listaVariaveis);
        id_var->conjunto_atributos.func = func;
        adiciona_atomo_lista_hash(id_var);

        //adicionar tipo de retorno a funcao

        //adicionar tipo lista de variaveis a funcao

        consome(INICIO);
        while(comando()){}
        consome(FIM);
        consome(FUNCAO); // consome o fim da funcao - nao pode remover
        return 1;
    }
    return 0;
}

void declaracao_de_variaveis(TAtomo localORglobal, TListaTabSimbolos *lista){
    if(consomeSemErro(VARIAVEIS)){
        do {
            TNoIdentificador *id_var = novo_TNoIdentificador();
            variavel *var = nova_variavel();
            var->ordem_declaracao = ordemVar++;
            strcpy (id_var->identificador,lookahead.atributo.str_id);
            consome(ID);
            var->tipo_variavel = lookahead.atomo;

            tipos();

            id_var->tipo_atributo = localORglobal;
            id_var->conjunto_atributos.var = var;

            consome(PONTO_VIRGULA);
            if (lista == NULL){
                adiciona_atomo_lista_hash(id_var);
            }else {
                adiciona_atomo_lista_atomos(lista, id_var);

            }

        }while(lookahead.atomo == ID);
    }
}
void bloco(){
    declaracao_de_variaveis(CAT_VARIAVEL_GLOBAL, NULL);
    while(declaracao_de_funcao());
    consome(INICIO);
    while(comando());
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
