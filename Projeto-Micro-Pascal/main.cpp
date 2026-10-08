#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"


char* lerArquivo(const char* nomeArquivo) {
    FILE* file = fopen(nomeArquivo, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

 
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

  
    char* buffer = (char*)malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, file);
        buffer[length] = '\0';
    }
    fclose(file);
    return buffer;
}

int main(int argc, char* argv[]) {
    const char* caminhoArquivo = (argc > 1) ? argv[1] : "programa.mp";

    char* fonte = lerArquivo(caminhoArquivo);
    if (!fonte) {
        return 1;
    }

    Parser parser(fonte);
    parser.analisar();
    
    
    printf("Análise concluída sem erros.\n");

    free(fonte);
    return 0;
}