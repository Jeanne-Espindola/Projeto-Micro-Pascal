#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>

Parser::Parser(const char* codigoFonte) {
    fonte = codigoFonte;
    posicao = 0;
    linha = 1;
    avancar();
}

void Parser::avancar() {
    tokenAtual = proximoToken(fonte, &posicao, &linha);
    if (tokenAtual.tipo == TOKEN_ERRO) {
        printf("Erro léxico no caracter [%s]\n", tokenAtual.texto);
        exit(1);
    }
}

void Parser::erroSintaxe() {
    printf("Erro de sintaxe no token [%s]\n", tokenAtual.texto);
    exit(1);
}

void Parser::consumir(TipoDoToken tipoEsperado) {
    if (tokenAtual.tipo == tipoEsperado) {
        avancar();
    } else {
        erroSintaxe();
    }
}

void Parser::analisar() {
    programa();
    if (tokenAtual.tipo != TOKEN_EOF) {
        erroSintaxe();
    }
}

void Parser::programa() {
    consumir(TOKEN_PROGRAM);
    consumir(TOKEN_IDENTIFICADOR);
    consumir(TOKEN_PONTO_VIRGULA);
    secaoVar();
    bloco();
    consumir(TOKEN_PONTO);
}

void Parser::secaoVar() {
    if (tokenAtual.tipo == TOKEN_VAR) {
        consumir(TOKEN_VAR);
        while (tokenAtual.tipo == TOKEN_IDENTIFICADOR) {
            declVar();
        }
    }
}

void Parser::declVar() {
    consumir(TOKEN_IDENTIFICADOR);
    while (tokenAtual.tipo == TOKEN_VIRGULA) {
        consumir(TOKEN_VIRGULA);
        consumir(TOKEN_IDENTIFICADOR);
    }
    consumir(TOKEN_DOIS_PONTOS);
    tipo();
    consumir(TOKEN_PONTO_VIRGULA);
}

void Parser::tipo() {
    if (tokenAtual.tipo == TOKEN_INTEGER || 
        tokenAtual.tipo == TOKEN_REAL || 
        tokenAtual.tipo == TOKEN_CHAR) {
        avancar();
    } else {
        erroSintaxe();
    }
}

void Parser::bloco() {
    consumir(TOKEN_BEGIN);
    listaComandos();
    consumir(TOKEN_END);
}

void Parser::listaComandos() {
    while (tokenAtual.tipo == TOKEN_BEGIN ||
           tokenAtual.tipo == TOKEN_IDENTIFICADOR ||
           tokenAtual.tipo == TOKEN_WHILE ||
           tokenAtual.tipo == TOKEN_REPEAT ||
           tokenAtual.tipo == TOKEN_IF ||
           tokenAtual.tipo == TOKEN_WRITE) {
        comando();
    }
}

void Parser::comando() {
    if (tokenAtual.tipo == TOKEN_BEGIN) {
        bloco();
        consumir(TOKEN_PONTO_VIRGULA);
    } else if (tokenAtual.tipo == TOKEN_IDENTIFICADOR) {
        atribuicao();
    } else if (tokenAtual.tipo == TOKEN_WHILE || tokenAtual.tipo == TOKEN_REPEAT) {
        iteracao();
    } else if (tokenAtual.tipo == TOKEN_IF) {
        decisao();
    } else if (tokenAtual.tipo == TOKEN_WRITE) {
        escrita();
    } else {
        erroSintaxe();
    }
}

void Parser::atribuicao() {
    consumir(TOKEN_IDENTIFICADOR);
    consumir(TOKEN_ATRIBUICAO);
    expressao();
    consumir(TOKEN_PONTO_VIRGULA);
}

void Parser::iteracao() {
    if (tokenAtual.tipo == TOKEN_WHILE) {
        consumir(TOKEN_WHILE);
        expressao();
        consumir(TOKEN_DO);
        comando();
    } else if (tokenAtual.tipo == TOKEN_REPEAT) {
        consumir(TOKEN_REPEAT);
        while (tokenAtual.tipo != TOKEN_UNTIL && tokenAtual.tipo != TOKEN_EOF) {
            comando();
        }
        consumir(TOKEN_UNTIL);
        expressao();
        consumir(TOKEN_PONTO_VIRGULA);
    }
}

void Parser::decisao() {
    consumir(TOKEN_IF);
    expressao();
    consumir(TOKEN_THEN);
    comando();
    if (tokenAtual.tipo == TOKEN_ELSE) {
        consumir(TOKEN_ELSE);
        comando();
    }
}

void Parser::escrita() {
    consumir(TOKEN_WRITE);
    consumir(TOKEN_ABRE_PAR);
    expressao();
    consumir(TOKEN_FECHA_PAR);
    consumir(TOKEN_PONTO_VIRGULA);
}

// --- EXPRESSÕES ---

void Parser::expressao() {
    exprLogica();
}

void Parser::exprLogica() {
    exprRelacional();
    while (tokenAtual.tipo == TOKEN_OR || tokenAtual.tipo == TOKEN_AND) {
        avancar();
        exprRelacional();
    }
}

void Parser::exprRelacional() {
    exprAditiva();
    while (tokenAtual.tipo == TOKEN_IGUAL || tokenAtual.tipo == TOKEN_DIFERENTE ||
           tokenAtual.tipo == TOKEN_MENOR_IGUAL || tokenAtual.tipo == TOKEN_MENOR ||
           tokenAtual.tipo == TOKEN_MAIOR_IGUAL || tokenAtual.tipo == TOKEN_MAIOR) {
        avancar();
        exprAditiva();
    }
}

void Parser::exprAditiva() {
    exprMultiplicativa();
    while (tokenAtual.tipo == TOKEN_MAIS || tokenAtual.tipo == TOKEN_MENOS) {
        avancar();
        exprMultiplicativa();
    }
}

void Parser::exprMultiplicativa() {
    exprFator();
    while (tokenAtual.tipo == TOKEN_MULT || tokenAtual.tipo == TOKEN_DIV_REAL ||
           tokenAtual.tipo == TOKEN_DIV_INT) {
        avancar();
        exprFator();
    }
}

void Parser::exprFator() {
    if (tokenAtual.tipo == TOKEN_NOT) {
        avancar();
        exprFator();
    } else {
        exprBasica();
    }
}

void Parser::exprBasica() {
    if (tokenAtual.tipo == TOKEN_ABRE_PAR) {
        consumir(TOKEN_ABRE_PAR);
        expressao();
        consumir(TOKEN_FECHA_PAR);
    } else if (tokenAtual.tipo == TOKEN_LITERAL_INTEIRO ||
               tokenAtual.tipo == TOKEN_LITERAL_REAL ||
               tokenAtual.tipo == TOKEN_LITERAL_CHAR ||
               tokenAtual.tipo == TOKEN_IDENTIFICADOR) {
        avancar();
    } else {
        erroSintaxe();
    }
}