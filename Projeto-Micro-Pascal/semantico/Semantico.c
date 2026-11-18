// Responsavel: Breno - organizacao da analise semantica e integracao com o parser
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include "Semantico.h"
#include "TabelaSimbolos.h"
#include "VerificadorLogico.h"



#define TAMANHO_TABELA 211   

static Hash *tabela = NULL;

static int tsExiste(const char *nome) {
    Simbolos s;
    return consultar(tabela, (char *)nome, &s);
}

static TipoSemantico tsTipo(const char *nome) {
    Simbolos s;
    if (!consultar(tabela, (char *)nome, &s)) return TIPO_ERRO;
    return s.tipo;
}

#define TS_INICIALIZAR()   do { if (tabela) liberar(tabela); tabela = criar(TAMANHO_TABELA); } while (0)
#define TS_INSERIR(n, t)   inserir(tabela, (char *)(n), (t))
#define TS_EXISTE(n)       tsExiste(n)
#define TS_TIPO(n)         tsTipo(n)

static int numErros = 0;

void inicializarSemantico(void) { numErros = 0; TS_INICIALIZAR(); }
int  houveErroSemantico(void)   { return numErros > 0; }
int  totalErrosSemanticos(void) { return numErros; }

void erroSemantico(int linha, const char *fmt, ...) {
    va_list ap;
    numErros++;
    fprintf(stderr, "Erro semantico (linha %d): ", linha);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
}



TipoSemantico tipoDeNome(const char *n) {
    if (!n) return TIPO_ERRO;
    if (strcasecmp(n, "integer") == 0) return TIPO_INTEGER;
    if (strcasecmp(n, "real") == 0) return TIPO_REAL;
    if (strcasecmp(n, "char") == 0 || strcasecmp(n, "character") == 0) return TIPO_CHARACTER;
    return TIPO_ERRO; 
}

void declararVariavel(const char *nome, TipoSemantico tipo, int linha) {
    if (tipo == TIPO_ERRO) { erroSemantico(linha, "tipo invalido na declaracao de '%s'", nome); return; }
    int r = TS_INSERIR(nome, tipo);
    if (r == 0)      erroSemantico(linha, "variavel '%s' ja declarada", nome);
    else if (r < 0)  erroSemantico(linha, "tabela de simbolos cheia ao declarar '%s'", nome);
}

TipoSemantico tipoDaVariavel(const char *nome, int linha) {
    if (!TS_EXISTE(nome)) {
        erroSemantico(linha, "variavel '%s' nao declarada", nome);
        return TIPO_ERRO;
    }
    return TS_TIPO(nome);
}



static const char *simbolo(OperadorSem op) {
    switch (op) {
        case OP_SOMA: return "+";   case OP_SUB: return "-";
        case OP_MULT: return "*";   case OP_DIV_INT: return "div";
        case OP_DIV_REAL: return "/";
        case OP_MENOR: return "<";  case OP_MENOR_IGUAL: return "<=";
        case OP_MAIOR: return ">";  case OP_MAIOR_IGUAL: return ">=";
        case OP_IGUAL: return "=";  case OP_DIFERENTE: return "<>";
        case OP_AND: return "and";  case OP_OR: return "or";
    }
    return "?";
}

static TipoSemantico aritmetico(OperadorSem op, TipoSemantico e, TipoSemantico d) {
    switch (op) {
        case OP_SOMA: case OP_SUB:
            if (e == TIPO_INTEGER && d == TIPO_INTEGER) return TIPO_INTEGER;
            if (e == TIPO_REAL    && d == TIPO_REAL)    return TIPO_REAL;
            if (e == TIPO_CHARACTER && d == TIPO_INTEGER) return TIPO_CHARACTER;
            return TIPO_ERRO;
        case OP_MULT:
            if (e == TIPO_INTEGER && d == TIPO_INTEGER) return TIPO_INTEGER;
            if (e == TIPO_REAL    && d == TIPO_REAL)    return TIPO_REAL;
            return TIPO_ERRO;
        case OP_DIV_INT:
            return (e == TIPO_INTEGER && d == TIPO_INTEGER) ? TIPO_INTEGER : TIPO_ERRO;
        case OP_DIV_REAL:
            return (e == TIPO_REAL && d == TIPO_REAL) ? TIPO_REAL : TIPO_ERRO;
        default: return TIPO_ERRO;
    }
}

TipoSemantico tipoBinario(OperadorSem op, TipoSemantico e, TipoSemantico d, int linha) {
    TipoSemantico r;
    if (e == TIPO_ERRO || d == TIPO_ERRO) return TIPO_ERRO; 
    switch (op) {
        case OP_SOMA: case OP_SUB: case OP_MULT: case OP_DIV_INT: case OP_DIV_REAL:
            r = aritmetico(op, e, d); break;
        case OP_MENOR: case OP_MENOR_IGUAL: case OP_MAIOR: case OP_MAIOR_IGUAL:
            r = verificarComparacaoRelacional(e, d); break;
        case OP_IGUAL: case OP_DIFERENTE:
            r = verificarComparacaoIgualdade(e, d); break;
        case OP_AND: case OP_OR:
            r = verificarOperacaoLogica(e, d); break;
        default: r = TIPO_ERRO;
    }
    if (r == TIPO_ERRO)
        erroSemantico(linha, "operador '%s' nao se aplica a %s e %s", simbolo(op), nomeTipo(e), nomeTipo(d));
    return r;
}

TipoSemantico tipoMenosUnario(TipoSemantico t, int linha) {
    if (t == TIPO_ERRO) return TIPO_ERRO;
    if (!tipoNumerico(t)) {
        erroSemantico(linha, "menos unario nao se aplica a %s", nomeTipo(t));
        return TIPO_ERRO;
    }
    return t;
}

TipoSemantico tipoNot(TipoSemantico t, int linha) {
    if (t == TIPO_ERRO) return TIPO_ERRO;
    if (t != TIPO_BOOLEAN) {
        erroSemantico(linha, "'not' so se aplica a boolean, mas o operando e %s", nomeTipo(t));
        return TIPO_ERRO;
    }
    return TIPO_BOOLEAN;
}



void checarAtribuicao(const char *nomeVar, TipoSemantico tipoExpr, int linha) {
    TipoSemantico tv = tipoDaVariavel(nomeVar, linha);
    if (tv == TIPO_ERRO || tipoExpr == TIPO_ERRO) return;
    if (!verificarAtribuicao(tv, tipoExpr))  
        erroSemantico(linha, "atribuicao incompativel: '%s' e %s, expressao e %s",
                      nomeVar, nomeTipo(tv), nomeTipo(tipoExpr));
}

void checarCondicao(TipoSemantico t, const char *comando, int linha) {
    if (t == TIPO_ERRO) return;
    if (!verificarCondicao(t))                
        erroSemantico(linha, "condicao do '%s' deve ser boolean, mas e %s", comando, nomeTipo(t));
}
