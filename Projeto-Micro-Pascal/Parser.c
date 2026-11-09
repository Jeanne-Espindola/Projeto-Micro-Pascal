#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>

static void avancar(Parser* p);
static void erroSintaxe(Parser* p);
static void consumir(Parser* p, TipoDoToken tipoEsperado);

static void programa(Parser* p);
static void secaoVar(Parser* p);
static void declVar(Parser* p);
static void tipo(Parser* p);
static void bloco(Parser* p);
static void listaComandos(Parser* p);
static void comando(Parser* p);
static void atribuicao(Parser* p);
static void iteracao(Parser* p);
static void decisao(Parser* p);
static void escrita(Parser* p);

static void expressao(Parser* p);
static void exprLogica(Parser* p);
static void exprRelacional(Parser* p);
static void exprAditiva(Parser* p);
static void exprMultiplicativa(Parser* p);
static void exprFator(Parser* p);
static void exprBasica(Parser* p);



void parser_init(Parser* p, const char* codigoFonte) {
    p->fonte = codigoFonte;
    p->posicao = 0;
    p->linha = 1;
    avancar(p);
}

void parser_analisar(Parser* p) {
    programa(p);
    if (p->tokenAtual.tipo != TOKEN_EOF) {
        erroSintaxe(p);
    }
}


static void avancar(Parser* p) {
    p->tokenAtual = proximoToken(p->fonte, &p->posicao, &p->linha);
    if (p->tokenAtual.tipo == TOKEN_ERRO) {
        printf("Erro léxico no caracter [%s]\n", p->tokenAtual.texto);
        exit(1);
    }
}

static void erroSintaxe(Parser* p) {
    printf("Erro de sintaxe no token [%s]\n", p->tokenAtual.texto);
    exit(1);
}

static void consumir(Parser* p, TipoDoToken tipoEsperado) {
    if (p->tokenAtual.tipo == tipoEsperado) {
        avancar(p);
    } else {
        erroSintaxe(p);
    }
}



static void programa(Parser* p) {
    consumir(p, TOKEN_PROGRAM);
    consumir(p, TOKEN_IDENTIFICADOR);
    consumir(p, TOKEN_PONTO_VIRGULA);
    secaoVar(p);
    bloco(p);
    consumir(p, TOKEN_PONTO);
}

static void secaoVar(Parser* p) {
    if (p->tokenAtual.tipo == TOKEN_VAR) {
        consumir(p, TOKEN_VAR);
        while (p->tokenAtual.tipo == TOKEN_IDENTIFICADOR) {
            declVar(p);
        }
    }
}

static void declVar(Parser* p) {
    consumir(p, TOKEN_IDENTIFICADOR);
    while (p->tokenAtual.tipo == TOKEN_VIRGULA) {
        consumir(p, TOKEN_VIRGULA);
        consumir(p, TOKEN_IDENTIFICADOR);
    }
    consumir(p, TOKEN_DOIS_PONTOS);
    tipo(p);
    consumir(p, TOKEN_PONTO_VIRGULA);
}

static void tipo(Parser* p) {
    if (p->tokenAtual.tipo == TOKEN_INTEGER ||
        p->tokenAtual.tipo == TOKEN_REAL ||
        p->tokenAtual.tipo == TOKEN_CHAR) {
        avancar(p);
    } else {
        erroSintaxe(p);
    }
}

static void bloco(Parser* p) {
    consumir(p, TOKEN_BEGIN);
    listaComandos(p);
    consumir(p, TOKEN_END);
}

static void listaComandos(Parser* p) {
    while (p->tokenAtual.tipo == TOKEN_BEGIN ||
           p->tokenAtual.tipo == TOKEN_IDENTIFICADOR ||
           p->tokenAtual.tipo == TOKEN_WHILE ||
           p->tokenAtual.tipo == TOKEN_REPEAT ||
           p->tokenAtual.tipo == TOKEN_IF ||
           p->tokenAtual.tipo == TOKEN_WRITE) {
        comando(p);
    }
}



static void comando(Parser* p) {
    if (p->tokenAtual.tipo == TOKEN_BEGIN) {
        bloco(p);
        consumir(p, TOKEN_PONTO_VIRGULA);
    } else if (p->tokenAtual.tipo == TOKEN_IDENTIFICADOR) {
        atribuicao(p);
    } else if (p->tokenAtual.tipo == TOKEN_WHILE || p->tokenAtual.tipo == TOKEN_REPEAT) {
        iteracao(p);
    } else if (p->tokenAtual.tipo == TOKEN_IF) {
        decisao(p);
    } else if (p->tokenAtual.tipo == TOKEN_WRITE) {
        escrita(p);
    } else {
        erroSintaxe(p);
    }
}

static void atribuicao(Parser* p) {
    consumir(p, TOKEN_IDENTIFICADOR);
    consumir(p, TOKEN_ATRIBUICAO);
    expressao(p);
    consumir(p, TOKEN_PONTO_VIRGULA);
}

static void iteracao(Parser* p) {
    if (p->tokenAtual.tipo == TOKEN_WHILE) {
        consumir(p, TOKEN_WHILE);
        expressao(p);
        consumir(p, TOKEN_DO);
        comando(p);
    } else if (p->tokenAtual.tipo == TOKEN_REPEAT) {
        consumir(p, TOKEN_REPEAT);
        while (p->tokenAtual.tipo != TOKEN_UNTIL && p->tokenAtual.tipo != TOKEN_EOF) {
            comando(p);
        }
        consumir(p, TOKEN_UNTIL);
        expressao(p);
        consumir(p, TOKEN_PONTO_VIRGULA);
    }
}

static void decisao(Parser* p) {
    consumir(p, TOKEN_IF);
    expressao(p);
    consumir(p, TOKEN_THEN);
    comando(p);
    if (p->tokenAtual.tipo == TOKEN_ELSE) {
        consumir(p, TOKEN_ELSE);
        comando(p);
    }
}

static void escrita(Parser* p) {
    consumir(p, TOKEN_WRITE);
    consumir(p, TOKEN_ABRE_PAR);
    expressao(p);
    consumir(p, TOKEN_FECHA_PAR);
    consumir(p, TOKEN_PONTO_VIRGULA);
}


static void expressao(Parser* p) {
    exprLogica(p);
}

static void exprLogica(Parser* p) {
    exprRelacional(p);
    while (p->tokenAtual.tipo == TOKEN_OR || p->tokenAtual.tipo == TOKEN_AND) {
        avancar(p);
        exprRelacional(p);
    }
}

static void exprRelacional(Parser* p) {
    exprAditiva(p);
    while (p->tokenAtual.tipo == TOKEN_IGUAL || p->tokenAtual.tipo == TOKEN_DIFERENTE ||
           p->tokenAtual.tipo == TOKEN_MENOR_IGUAL || p->tokenAtual.tipo == TOKEN_MENOR ||
           p->tokenAtual.tipo == TOKEN_MAIOR_IGUAL || p->tokenAtual.tipo == TOKEN_MAIOR) {
        avancar(p);
        exprAditiva(p);
    }
}

static void exprAditiva(Parser* p) {
    exprMultiplicativa(p);
    while (p->tokenAtual.tipo == TOKEN_MAIS || p->tokenAtual.tipo == TOKEN_MENOS) {
        avancar(p);
        exprMultiplicativa(p);
    }
}

static void exprMultiplicativa(Parser* p) {
    exprFator(p);
    while (p->tokenAtual.tipo == TOKEN_MULT || p->tokenAtual.tipo == TOKEN_DIV_REAL ||
           p->tokenAtual.tipo == TOKEN_DIV_INT) {
        avancar(p);
        exprFator(p);
    }
}

static void exprFator(Parser* p) {
    if (p->tokenAtual.tipo == TOKEN_NOT) {
        avancar(p);
        exprFator(p);
    } else {
        exprBasica(p);
    }
}

static void exprBasica(Parser* p) {
    if (p->tokenAtual.tipo == TOKEN_ABRE_PAR) {
        consumir(p, TOKEN_ABRE_PAR);
        expressao(p);
        consumir(p, TOKEN_FECHA_PAR);
    } else if (p->tokenAtual.tipo == TOKEN_LITERAL_INTEIRO ||
               p->tokenAtual.tipo == TOKEN_LITERAL_REAL ||
               p->tokenAtual.tipo == TOKEN_LITERAL_CHAR ||
               p->tokenAtual.tipo == TOKEN_IDENTIFICADOR) {
        avancar(p);
    } else {
        erroSintaxe(p);
    }
}