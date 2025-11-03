#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército
    int tropas;     // Quantidade de tropas
} Territorio;

int main() {
    Territorio territorios[5]; // Vetor para armazenar 5 territórios
    int i;

    printf("=== Cadastro de Territorios ===\n");

    // Loop para cadastrar os 5 territórios
    for(i = 0; i < 5; i++) {
        printf("\nTerritorio %d:\n", i + 1);

        printf("Nome: ");
        scanf(" %[^\n]s", territorios[i].nome); // Lê string com espaços

        printf("Cor do exército: ");
        scanf(" %s", territorios[i].cor); // Lê cor do exército

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas); // Lê número de tropas
    }

    // Exibição dos dados cadastrados
    printf("\n=== Dados dos Territorios Cadastrados ===\n");
    for(i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}

