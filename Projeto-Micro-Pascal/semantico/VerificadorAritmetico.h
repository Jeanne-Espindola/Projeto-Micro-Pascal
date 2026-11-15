// Responsável: Jeanne - verificação de tipos das expressões aritméticas


#ifndef VERIFICADORARITMETICO_H

#define VERIFICADORARITMETICO_H
#include "Tipos.h"


//Assinatura das funções


TipoSemantico verificarOperacaoNumerica(TipoSemantico esquerdo, TipoSemantico direito);
TipoSemantico verificarCaractereInteiro(TipoSemantico esquerdo, TipoSemantico direito);
TipoSemantico verificarDivisaoInteira(TipoSemantico esquerdo, TipoSemantico direito);
TipoSemantico verificarDivisaoReal(TipoSemantico esquerdo, TipoSemantico direito);
TipoSemantico verificarMenosUnario(TipoSemantico operando);


#endif

