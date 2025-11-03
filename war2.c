#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
typedef struct {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército dono do território
    int tropas;     // Quantidade de tropas
} Territorio;

// Função para cadastrar territórios dinamicamente
Territorio* cadastrarTerritorios(int n) {
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }

    for(int i = 0; i < n; i++) {
        printf("\nCadastro do Territorio %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]s", mapa[i].nome);
        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    return mapa;
}

// Função para exibir territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== Dados dos Territorios ===\n");
    for(int i = 0; i < n; i++) {
        printf("%d - Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função para simular ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if(strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque invalido: mesmo exército!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n%s (Atacante) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) rolou: %d\n", defensor->nome, dadoDefensor);

    if(dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");
        defensor->tropas = atacante->tropas / 2;
        strcpy(defensor->cor, atacante->cor);
    } else {
        printf("Defensor venceu!\n");
        atacante->tropas -= 1;
        if(atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    Territorio* mapa = cadastrarTerritorios(n);

    exibirTerritorios(mapa, n);

    int atacanteIdx, defensorIdx;
    printf("\nEscolha o índice do território atacante: ");
    scanf("%d", &atacanteIdx);
    printf("Escolha o índice do território defensor: ");
    scanf("%d", &defensorIdx);

    atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);

    exibirTerritorios(mapa, n);

    liberarMemoria(mapa);
    return 0;
}
