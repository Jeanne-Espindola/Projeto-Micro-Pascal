//aqui vai ficar a definição do token e do enum

enum TipoDoToken{
    //palavras reservadas
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

    //Identificadores

    TOKEN_IDENTIFICADOR, //exemplo nome de variavel
    TOKEN_LITERAL_INTEIRO, //para numeros sem virgula
    TOKEN_LITERAL_REAL, //para numeros com virgula
    TOKEN_LITERAL_CHAR, //caracteres entre aspas simples.

    //controladores
    TOKEN_EOF, //esse vai servir pra dizer q o arquivo terminou de ser lido.
    TOKEN_ERRO
};

struct Token{
    enum TipoDoToken tipo;
    char texto[100]; //nosso lexema extraido do codigo fonte
    int linha; //vai guardar a linha que o token foi encontrado do arquivo .mp

    //essa linha serve pra tanto avisar q o erro esta em tal linha, cm lidar tambem com o \n, quebras de linha.

};

Token proximoToken(const char* texto, int* posicao, int* linhaAtual);

//o texto é o texto completo que vai ser analisado, a posicao do caracter onde a linha parou, e linha é a linha atual do arquivo

/*O parâmetro pos é o índice que controla onde a leitura parou. A cada token lido, o Lexer avança esse número para que a próxima 
chamada leia os caracteres seguintes até chegar ao fim do arquivo.*/



