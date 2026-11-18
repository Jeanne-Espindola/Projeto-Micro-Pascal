#define TABELA_SIMBOLOS_H
#include "tipos.h"

typdef struct simbolos{
    Tiposemantico tipo;
} Simbolos;


typedef struct hash {
    int TABLE_SIZE;
    Simbolos **symbol;
    int qtd;
} Hash;

Hash* criar(int TABLE_SIZE);
int valorString(char *str);
int funcao_hash(int TABLE_SIZE, char *str);
int SondagemLinear(int pos,int i, int TABLE_SIZE);
void mensagemerro(char *msg);
int inserir(Hash *ha, char *nome, TipoSemantico tipo);
int consultar(Hash *ha, char *nome, Simbolos *out);
void imprimir(Hash *ha);
void liberar(Hash *ha);