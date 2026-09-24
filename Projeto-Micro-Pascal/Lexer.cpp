#include "Lexer.h"
#include <ctype.h>
#include <string.h>

Token proximoToken(const char* texto, int* posicao, int* linhaAtual) {
    Token token;
    token.linha = *linhaAtual;

    // 1. Ignorar Espaços em Branco, Tabulações e Quebras de Linha
    while (texto[*posicao] == ' ' || texto[*posicao] == '\t' || texto[*posicao] == '\n' || texto[*posicao] == '\r') {
        if (texto[*posicao] == '\n') {
            (*linhaAtual)++;
        }
        (*posicao)++;
        token.linha = *linhaAtual;
    }

    // 2. Fim de Arquivo (EOF)
    if (texto[*posicao] == '\0') {
        token.tipo = TOKEN_EOF;
        strcpy(token.texto, "EOF");
        return token;
    }

    // 3. Operadores Compostos (2 caracteres)
    if (texto[*posicao] == ':' && texto[*posicao + 1] == '=') {
        token.tipo = TOKEN_ATRIBUICAO;
        strcpy(token.texto, ":=");
        *posicao += 2;
        return token;
    }
    if (texto[*posicao] == '<' && texto[*posicao + 1] == '=') {
        token.tipo = TOKEN_MENOR_IGUAL;
        strcpy(token.texto, "<=");
        *posicao += 2;
        return token;
    }
    if (texto[*posicao] == '>' && texto[*posicao + 1] == '=') {
        token.tipo = TOKEN_MAIOR_IGUAL;
        strcpy(token.texto, ">=");
        *posicao += 2;
        return token;
    }
    if (texto[*posicao] == '<' && texto[*posicao + 1] == '>') {
        token.tipo = TOKEN_DIFERENTE;
        strcpy(token.texto, "<>");
        *posicao += 2;
        return token;
    }

    // 4. Símbolos e Operadores Simples (1 caractere)
    if (texto[*posicao] == ':') {
        token.tipo = TOKEN_DOIS_PONTOS;
        strcpy(token.texto, ":");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == ';') {
        token.tipo = TOKEN_PONTO_VIRGULA;
        strcpy(token.texto, ";");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == ',') {
        token.tipo = TOKEN_VIRGULA;
        strcpy(token.texto, ",");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == '.') {
        token.tipo = TOKEN_PONTO;
        strcpy(token.texto, ".");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == '(') {
        token.tipo = TOKEN_ABRE_PAR;
        strcpy(token.texto, "(");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == ')') {
        token.tipo = TOKEN_FECHA_PAR;
        strcpy(token.texto, ")");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == '+') {
        token.tipo = TOKEN_MAIS;
        strcpy(token.texto, "+");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == '-') {
        token.tipo = TOKEN_MENOS;
        strcpy(token.texto, "-");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == '*') {
        token.tipo = TOKEN_MULT;
        strcpy(token.texto, "*");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == '/') {
        token.tipo = TOKEN_DIV_REAL;
        strcpy(token.texto, "/");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == '=') {
        token.tipo = TOKEN_IGUAL;
        strcpy(token.texto, "=");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == '<') {
        token.tipo = TOKEN_MENOR;
        strcpy(token.texto, "<");
        (*posicao)++;
        return token;
    }
    if (texto[*posicao] == '>') {
        token.tipo = TOKEN_MAIOR;
        strcpy(token.texto, ">");
        (*posicao)++;
        return token;
    }

    // 5. Identificadores e Palavras Reservadas
    if (isalpha(texto[*posicao])) {
        int i = 0;
        while (isalnum(texto[*posicao])) {
            token.texto[i] = texto[*posicao];
            i++;
            (*posicao)++;
        }
        token.texto[i] = '\0';

        if (strcmp(token.texto, "program") == 0) token.tipo = TOKEN_PROGRAM;
        else if (strcmp(token.texto, "var") == 0) token.tipo = TOKEN_VAR;
        else if (strcmp(token.texto, "integer") == 0) token.tipo = TOKEN_INTEGER;
        else if (strcmp(token.texto, "real") == 0) token.tipo = TOKEN_REAL;
        else if (strcmp(token.texto, "begin") == 0) token.tipo = TOKEN_BEGIN;
        else if (strcmp(token.texto, "end") == 0) token.tipo = TOKEN_END;
        else if (strcmp(token.texto, "if") == 0) token.tipo = TOKEN_IF;
        else if (strcmp(token.texto, "then") == 0) token.tipo = TOKEN_THEN;
        else if (strcmp(token.texto, "else") == 0) token.tipo = TOKEN_ELSE;
        else if (strcmp(token.texto, "while") == 0) token.tipo = TOKEN_WHILE;
        else if (strcmp(token.texto, "do") == 0) token.tipo = TOKEN_DO;
        else if (strcmp(token.texto, "write") == 0) token.tipo = TOKEN_WRITE;
        else if (strcmp(token.texto, "read") == 0) token.tipo = TOKEN_READ;
        else token.tipo = TOKEN_IDENTIFICADOR;

        return token;
    }

    // 6. Números Inteiros
    if (isdigit(texto[*posicao])) {
        int i = 0;
        while (isdigit(texto[*posicao])) {
            token.texto[i] = texto[*posicao];
            i++;
            (*posicao)++;
        }
        token.texto[i] = '\0';

        token.tipo = TOKEN_LITERAL_INTEIRO;
        return token;
    }

    // Erro Léxico: Caractere não reconhecido
    token.tipo = TOKEN_ERRO;
    token.texto[0] = texto[*posicao];
    token.texto[1] = '\0';
    (*posicao)++;
    return token;
}