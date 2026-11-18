// Responsavel: Breno - representacao interna dos tipos
#ifndef TIPOS_H
#define TIPOS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TIPO_INTEGER,
    TIPO_REAL,
    TIPO_CHARACTER,
    TIPO_BOOLEAN,   // uso interno: o programador NAO pode declarar variaveis boolean
    TIPO_ERRO       // resultado de expressao invalida (evita erros em cascata)
} TipoSemantico;

static inline const char *nomeTipo(TipoSemantico t) {
    switch (t) {
        case TIPO_INTEGER:   return "integer";
        case TIPO_REAL:      return "real";
        case TIPO_CHARACTER: return "character";
        case TIPO_BOOLEAN:   return "boolean";
        default:             return "erro";
    }
}

static inline int tipoNumerico(TipoSemantico t) {
    return t == TIPO_INTEGER || t == TIPO_REAL;
}

#ifdef __cplusplus
}
#endif
#endif
