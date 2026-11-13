#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabelaSimbolos.h"

Hash* criar(int TABLE_SIZE) {
    Hash *ha = malloc(sizeof(Hash));
    if(ha != NULL) {
        ha-> TABLE_SIZE = TABLE_SIZE;
        ha-> qtd = 0;
    }
    ha-> symbol = calloc(TABLE_SIZE, sizeof(Simbolos));
    if(ha->symbol == NULL) {
        free(ha);
        return NULL;
    }
    ha -> TABLE_SIZE = TABLE_SIZE;
    ha->qtd = 0;
    return ha;
}

int valorString(char *str) {
    int i;
    int valor = 7;
    int tam = strlen(str);
    for(int i = 0; i < tam; i++) {
        valor = 31 * valor + (int) str[i];
    }
    return valor;
}

int funcao_hash(int TABLE_SIZE, char *str) {
    return (valorString(str) & 0x7FFFFFFF) % TABLE_SIZE;
}

int SondagemLinear(int pos,int i, int TABLE_SIZE) {
    return (pos + i) % TABLE_SIZE;
}

void mensagemerro(char *msg) {
    printf("Erro Semantico %s\n", msg);
}

int inserir(Hash *ha, char *nome) {

    if(ha == NULL) {
        return 0;
    }
    int pos = funcao_hash(ha->TABLE_SIZE, nome);
    Simbolos* novo = malloc(sizeof(Simbolos));

    strcpy(novo->nome, nome);
    ha->symbol[pos] = novo;
    ha->qtd++;
    return 1;

}

int consultar(Hash *ha, char *nome, Simbolos *out) {

    if(ha == NULL) {
        return 0;
    }

    int pos = funcao_hash(ha->TABLE_SIZE, nome);

    if(ha->symbol[pos] == NULL) {
        return 0; //posição vazia
    }
    if(strcmp(ha->symbol[pos]->nome, nome) != 0) {
        return 0;
    }

    *out = (*ha->symbol[pos]);

    return 1;
}

void imprimir(Hash *ha) {
    if (ha != NULL) {
        printf("Tabela (size=%d, qtd=%d)\n", ha->TABLE_SIZE, ha->qtd);
        for (int i = 0; i < ha->TABLE_SIZE; i++) {
            if (ha->symbol[i] != NULL) 
                printf("[%d] = %s\n", i, *ha->symbol[i]);
            else              
                printf("[%d] = NULL\n", i);
        }
    }
 
}

void liberar(Hash *ha) {
    if(ha != NULL) {
        return;

    }
    for(int i = 0; i < ha->TABLE_SIZE; i++) {
        if(ha->symbol[i] != NULL) {
            free(ha->symbol[i]);
        }
    }
    free(ha->symbol);
    free(ha);
}
