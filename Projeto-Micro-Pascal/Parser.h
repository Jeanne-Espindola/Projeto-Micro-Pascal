#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"

typedef struct {
    const char* fonte;
    int posicao;
    int linha;
    Token tokenAtual;
} Parser;

void iniciarParser(Parser* p, const char* codigoFonte);
void analisar(Parser* p);

#endif