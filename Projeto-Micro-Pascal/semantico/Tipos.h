// Responsável: Breno - representação interna dos tipos (INTEGER, REAL, CHARACTER, BOOLEAN)

//Nomes PROVISORIOS, so pra eu começar o meu codigo (Jeanne) dps tu muda e me avisa ou deixa assim msm. 


#ifndef TIPOS_H
#define TIPOS_H

enum TipoSemantico {
    TIPO_INTEGER,
    TIPO_REAL,
    TIPO_CHARACTER,
    TIPO_BOOLEAN,
    TIPO_ERRO
};

typedef enum TipoSemantico TipoSemantico;

#endif
