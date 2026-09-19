//aqui vai ficar a logica onde eu leio os tokens e gero os tokens.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Lexer.h"

Token proximoToken(const char* texto, int* posicao, int* linhaAtual){
    Token token;
    token.texto[0] = '\0'; //iniciando o texto vazio e na posicao 0
    token.linha = linhaAtual;

    while(texto[posicao] != '\0'){ //enquanto nao apontar pro fim do texto continue executando 
        if(texto[posicao] == ' ' || texto[posicao] == '\t' || texto[posicao] == '\r'){
            posicao++; //se for uma tabulação, um espaço etc, avança pro proximo caractere
        }
        else if(texto[posicao] == '\n'){
            linhaAtual++;
            posicao++; 
            //instrução feita pra considerar quebra de linha e pular pro proximo token.
        }
        else{
            break; //para caracter invalido
        }}
        token.linha = linhaAtual;

        if(texto[posicao] == '\0'){ //mesmo depois de pular todos os espaços ele serve pra verificar se acabou o texto
            token.tipo = TOKEN_EOF;
            strcpy(token.texto, "EOF");
            return token;
        }

        //operadores compostos ou seja considerando mais de um caracter, essa abaixo é operador de atribuicao
        if(texto[posicao] == ':' && texto[posicao + 1] == '='){
            token.tipo = TOKEN_ATRIBUICAO;
            strcpy(token.texto, ":=");
            posicao += 2; //pra pular
            return token;
        }

        if(texto[posicao] == '<' && texto[posicao + 1] == '='){
            token.tipo = TOKEN_MENOR_IGUAL;
            strcpy(token.texto, "<=");
            posicao += 2;
            return token;
        }

        if(texto[posicao] == '>' && texto[posicao + 1] == '='){
            token.tipo = TOKEN_MAIOR_IGUAL;
            strcpy(token.texto, ">=");
            posicao += 2;
            return token;
        }

        if(texto[posicao] == '<' && texto[posicao + 1] == '>'){
            token.tipo = TOKEN_DIFERENTE;
            strcpy(token.texto, "<>");
            posicao += 2;
            return token;
        }


        //operadores simples, considerando apenas um caracter

        if(texto[posicao] == ':'){
            token.tipo = TOKEN_DOIS_PONTOS;
            strcpy(token.texto, ":");
            posicao++;
            return token;
        }

        if(texto[posicao] == ';'){ //aspas simples pois trata de apenas um caracter
            token.tipo = TOKEN_PONTO_VIRGULA;
            strcpy(token.texto, ";") //aqui a gente copia pro texto como uma string inteira
            posicao++;
            return token;
        }

        if(texto[posicao] == ','){
            token.tipo = TOKEN_VIRGULA;
            strcpy(token.texto, ",");
            posicao++;
            return token;
        }

        if(texto[posicao] == '.'){
            token.tipo = TOKEN_PONTO;
            strcpy(token.texto, ".");
            posicao++;
            return token;
        }

        if(texto[posicao] == '('){
            token.tipo = TOKEN_ABRE_PAR;
            strcpy(token.texto, "(");
            posicao++;
            return token;
        }

        if(texto[posicao] == ')'){
            token.tipo = TOKEN_FECHA_PAR;
            strcpy(token.texto, ")");
            posicao++;
            return token;
        }

        if(texto[posicao] == '+'){
            token.tipo = TOKEN_MAIS;
            strcpy(token.texto, "+");
            posicao++;
            return token;
        }

        if(texto[posicao] == '-'){
            token.tipo = TOKEN_MENOR;
            strcpy(token.texto, "-");
            posicao++;
            return token;
        }

        if(texto[posicao] == '*'){
            token.tipo = TOKEN_MULT;
            strcpy(token.texto, "*");
            posicao++;
            return token;
        }

        if(texto[posicao] == '/'){
            token.tipo = TOKEN_DIV_REAL;
            strcpy(token.texto, "/");
            posicao++;
            return token;
        }

        if(texto[posicao] == '='){
            token.tipo = TOKEN_IGUAL;
            strcpy(token.texto, "=");
            posicao++;
            return token;
        }

        if(texto[posicao] == '<'){
            token.tipo = TOKEN_MENOR;
            strcpy(token.texto, "<");
            posicao++;
            return token;
        }

        if(texto[posicao] == '>'){
            token.tipo = TOKEN_MAIOR;
            strcpy(token.texto, ">");
            posicao++;
            return token;
        }

        //IDENTIFICADORES E PALAVRAS RESERVADAS










    }


