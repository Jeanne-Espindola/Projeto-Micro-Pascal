
#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "Tipos.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OP_SOMA, OP_SUB, OP_MULT, OP_DIV_INT, OP_DIV_REAL,
    OP_MENOR, OP_MENOR_IGUAL, OP_MAIOR, OP_MAIOR_IGUAL,
    OP_IGUAL, OP_DIFERENTE,
    OP_AND, OP_OR
} OperadorSem;

void inicializarSemantico(void);
int  houveErroSemantico(void);      
int  totalErrosSemanticos(void);


void erroSemantico(int linha, const char *fmt, ...);


TipoSemantico tipoDeNome(const char *nomeTipoDeclarado);
void declararVariavel(const char *nome, TipoSemantico tipo, int linha);
TipoSemantico tipoDaVariavel(const char *nome, int linha);

TipoSemantico tipoBinario(OperadorSem op, TipoSemantico esq, TipoSemantico dir, int linha);
TipoSemantico tipoMenosUnario(TipoSemantico operando, int linha);
TipoSemantico tipoNot(TipoSemantico operando, int linha);   

void checarAtribuicao(const char *nomeVar, TipoSemantico tipoExpr, int linha);
void checarCondicao(TipoSemantico tipoCond, const char *comando, int linha); 

#ifdef __cplusplus
}
#endif
#endif
