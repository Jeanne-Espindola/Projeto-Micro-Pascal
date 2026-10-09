#include <stdio.h>
#include "Parser.h"

int main() {
    // 1. Abre o ficheiro de teste diretamente para leitura
    FILE* arquivo = fopen("teste.mp", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo teste.mp\n");
        return 1;
    }

    // 2. Lê o código para um buffer fixo na memória
    char buffer[4096];
    int tamanho = fread(buffer, 1, sizeof(buffer) - 1, arquivo);
    buffer[tamanho] = '\0';
    fclose(arquivo);

    // 3. Dispara o Parser e a análise
    Parser parser(buffer);
    parser.analisar();

    printf("Análise concluída sem erros.\n");
    return 0;
}