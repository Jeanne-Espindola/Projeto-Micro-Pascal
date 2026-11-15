// Responsável: Jeanne - verificação de tipos das expressões aritméticas
#include "VerificadorAritmetico.h"

// + - * : integer com integer -> integer; real com real -> real

TipoSemantico verificarOperacaoNumerica(TipoSemantico esquerdo, TipoSemantico direito){
    if(esquerdo == TIPO_INTEGER && direito == TIPO_INTEGER){
        return TIPO_INTEGER;
    }
    if(esquerdo == TIPO_REAL && direito == TIPO_REAL){
        return TIPO_REAL;
    }

    return TIPO_ERRO;
}

TipoSemantico verificadorCaractereInteiro(TipoSemantico esquerdo, TipoSemantico direito){
    if(esquerdo == TIPO_CHARACTER && direito == TIPO_INTEGER){
        return TIPO_CHARACTER;
    }
    return TIPO_ERRO;
}

TipoSemantico verificadorDivisaoInteira(TipoSemantico esquerdo, TipoSemantico direito){
    if(esquerdo == TIPO_INTEGER && direito == TIPO_INTEGER){
        return TIPO_INTEGER;
    }

    return TIPO_ERRO;
}

TipoSemantico verificarDivisaoReal(TipoSemantico esquerdo, TipoSemantico direito){
    if(esquerdo == TIPO_REAL && direito == TIPO_REAL){
        return TIPO_REAL;
    }
    return TIPO_ERRO;
}

TipoSemantico verificarMenosUnario(TipoSemantico operando) {
    if (operando == TIPO_INTEGER) {
        return TIPO_INTEGER;
    }
    if (operando == TIPO_REAL) {
        return TIPO_REAL;
    }
    return TIPO_ERRO;
}