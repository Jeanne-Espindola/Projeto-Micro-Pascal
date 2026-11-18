// Responsável: Roberto - expressões lógicas, comparações e tipos dos comandos

#ifndef VERIFICADORLOGICO_H
#define VERIFICADORLOGICO_H

#include "Tipos.h"

// Assinaturas das funções para comparações, operações lógicas e comandos

// Comparações relacionais (<, <=, >, >=)
TipoSemantico verificarComparacaoRelacional(TipoSemantico esquerdo, TipoSemantico direito);

// Comparações de igualdade (=, <>)
TipoSemantico verificarComparacaoIgualdade(TipoSemantico esquerdo, TipoSemantico direito);

// Operações lógicas (and, or)
TipoSemantico verificarOperacaoLogica(TipoSemantico esquerdo, TipoSemantico direito);

// Verificação de atribuição (variável = expressão atribuída)
int verificarAtribuicao(TipoSemantico tipoVariavel, TipoSemantico tipoExpressao);

// Verificação de condições (if, while, repeat-until devem ser BOOLEAN)
int verificarCondicao(TipoSemantico tipoCondicao);

#endif