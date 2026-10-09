#include <stdio.h>
#include "Parser.h"

int main() {
    FILE* arquivo = fopen("teste.mp", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo teste.mp\n");
        return 1;
    }

    char buffer[4096];
    int tamanho = fread(buffer, 1, sizeof(buffer) - 1, arquivo);
    buffer[tamanho] = '\0';
    fclose(arquivo);

    
    Parser parser(buffer);
    parser.analisar();

    printf("Análise concluída sem erros.\n");
    return 0;
}