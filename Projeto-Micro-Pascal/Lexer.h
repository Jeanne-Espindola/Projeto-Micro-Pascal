//aqui vai ficar a definição do token e do enum

enum TipoDoToken{
    TOKEN_PROGRAM,
    TOKEN_IF,
    TOKEN_THEN,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_DO,
    TOKEN_REPEAT,
    TOKEN_UNTIL,
    TOKEN_INTEGER,
    TOKEN_REAL,
    TOKEN_CHAR,
    TOKEN_BEGIN,
    TOKEN_END,
    TOKEN_WRITE,
    TOKEN_READ,
    TOKEN_VAR,


    //operadores
    TOKEN_MAIS,
    TOKEN_MENOS,
    TOKEN_MULT,
    TOKEN_DIV_REAL,
    TOKEN_DIV_INT,

    //operadores logicos 
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_IGUAL,
    TOKEN_DIFERENTE,
    TOKEN_MENOR,
    TOKEN_MENOR_IGUAL,
    TOKEN_MAIOR,
    TOKEN_MAIOR_IGUAL,
    TOKEN_ATRIBUICAO,

    //operadores de simbolo
    TOKEN_DOIS_PONTOS,
    TOKEN_PONTO_VIRGULA,
    TOKEN_VIRGULA,
    TOKEN_PONTO,
    TOKEN_ABRE_PAR,
    TOKEN_FECHA_PAR,


    TOKEN_IDENTIFICADOR, 
    TOKEN_LITERAL_INTEIRO, 
    TOKEN_LITERAL_REAL,
    TOKEN_LITERAL_CHAR,
 
    TOKEN_EOF, 
    TOKEN_ERRO
};

struct Token{
    enum TipoDoToken tipo;
    char texto[100]; 
    int linha; 
};


Token proximoToken(const char* texto, int* posicao, int* linhaAtual);




