#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"

class Parser {
private:
    const char* fonte;
    int posicao;
    int linha;
    Token tokenAtual;

    void avancar();
    void consumir(TipoDoToken tipoEsperado);
    void erroSintaxe();

    // Regras Gramaticais
    void programa();
    void secaoVar();
    void declVar();
    void tipo();
    void bloco();
    void listaComandos();
    void comando();
    void atribuicao();
    void iteracao();
    void decisao();
    void escrita();

    // Expressões
    void expressao();
    void exprLogica();
    void exprRelacional();
    void exprAditiva();
    void exprMultiplicativa();
    void exprFator();
    void exprBasica();

public:
    Parser(const char* codigoFonte);
    void analisar();
};

#endif