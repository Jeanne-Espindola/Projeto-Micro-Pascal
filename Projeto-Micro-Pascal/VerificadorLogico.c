// Responsável: Roberto - expressões lógicas, comparações e tipos dos comandos
#include "VerificadorLogico.h"
#include <stdio.h>

// Parte A - Comparações (<, <=, >, >=)
// Permitir comparações numéricas entre operandos do mesmo tipo (integer ou real) -> retorna TIPO_BOOLEAN
TipoSemantico verificarComparacaoRelacional(TipoSemantico esquerdo, TipoSemantico direito) {
    if ((esquerdo == TIPO_INTEGER && direito == TIPO_INTEGER) ||
        (esquerdo == TIPO_REAL && direito == TIPO_REAL)) {
        return TIPO_BOOLEAN;
    }
    return TIPO_ERRO;
}

// Parte A - Comparações de igualdade (=, <>)
// Permitir comparações entre operandos do mesmo tipo, inclusive character e boolean (além de integer e real)
TipoSemantico verificarComparacaoIgualdade(TipoSemantico esquerdo, TipoSemantico direito) {
    if (esquerdo == direito && esquerdo != TIPO_ERRO) {
        return TIPO_BOOLEAN;
    }
    return TIPO_ERRO;
}

// Parte A - Operações lógicas (and, or)
// Garantir que operações lógicas aceitem apenas boolean e retornem boolean
TipoSemantico verificarOperacaoLogica(TipoSemantico esquerdo, TipoSemantico direito) {
    if (esquerdo == TIPO_BOOLEAN && direito == TIPO_BOOLEAN) {
        return TIPO_BOOLEAN;
    }
    return TIPO_ERRO;
}

// Parte B - Verificação de tipos dos comandos (Atribuição)
// Garantir que o tipo da variável seja igual ao tipo da expressão atribuída.
int verificarAtribuicao(TipoSemantico tipoVariavel, TipoSemantico tipoExpressao) {
    if (tipoVariavel == tipoExpressao && tipoVariavel != TIPO_ERRO) {
        return 1; // Válido
    }
    // Caso especial aceito em algumas linguagens (ex: real recebe integer)
    if (tipoVariavel == TIPO_REAL && tipoExpressao == TIPO_INTEGER) {
        return 1;
    }
    return 0; // Inválido / Erro
}

// Parte B - Verificação de condições (if, while, repeat-until)
// Garantir que todas essas condições sejam estritamente booleanas.
int verificarCondicao(TipoSemantico tipoCondicao) {
    if (tipoCondicao == TIPO_BOOLEAN) {
        return 1; // Válido
    }
    return 0; // Inválido / Erro
}