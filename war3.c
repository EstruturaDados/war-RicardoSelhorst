#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_JOGADORES 2
#define MAX_TERRITORIOS 5

// Estrutura de território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ---------------- Funções ---------------- //

// Cadastro de territórios dinamicamente
Territorio* cadastrarTerritorios(int n) {
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if(!mapa) {
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

// Exibe todos os territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== Dados dos Territorios ===\n");
    for(int i = 0; i < n; i++) {
        printf("%d - Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simulação de ataque
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

// Atribui missão ao jogador (alocação dinâmica)
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    *destino = (char*) malloc((strlen(missoes[sorteio]) + 1) * sizeof(char));
    if(!*destino) {
        printf("Erro na alocacao de memoria para a missão.\n");
        exit(1);
    }
    strcpy(*destino, missoes[sorteio]);
}

// Exibe a missão
void exibirMissao(char* missao) {
    printf("\nSua missão é: %s\n", missao);
}

// Verificação simples de missão (exemplo inicial)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo simplificado: missão "Conquistar 3 territórios" verifica se há 3 territórios da mesma cor
    int contador[MAX_TERRITORIOS] = {0};
    for(int i = 0; i < tamanho; i++) {
        for(int j = i+1; j < tamanho; j++) {
            if(strcmp(mapa[i].cor, mapa[j].cor) == 0) contador[i]++;
        }
    }

    if(strcmp(missao, "Conquistar 3 territorios") == 0) {
        for(int i = 0; i < tamanho; i++) {
            if(contador[i] >= 2) return 1; // missão cumprida
        }
    }
    // Outras missões podem ser adicionadas aqui
    return 0; // missão não cumprida
}

// Liberação de memória
void liberarMemoria(Territorio* mapa, char* missoesJogadores[], int nJogadores) {
    free(mapa);
    for(int i = 0; i < nJogadores; i++) {
        free(missoesJogadores[i]);
    }
}

// ---------------- Main ---------------- //

int main() {
    srand(time(NULL));

    int nTerritorios = MAX_TERRITORIOS;
    Territorio* mapa = cadastrarTerritorios(nTerritorios);
    exibirTerritorios(mapa, nTerritorios);

    // Missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar todas as tropas vermelhas",
        "Controlar territórios da cor azul",
        "Ter mais tropas que o adversario",
        "Conquistar o territorio do meio"
    };
    int totalMissoes = 5;

    // Alocação de missões para cada jogador
    char* missoesJogadores[MAX_JOGADORES];
    for(int i = 0; i < MAX_JOGADORES; i++) {
        atribuirMissao(&missoesJogadores[i], missoes, totalMissoes);
        printf("\nJogador %d: ", i+1);
        exibirMissao(missoesJogadores[i]);
    }

    // Simulação de ataque
    int atacanteIdx, defensorIdx;
    printf("\nEscolha o índice do território atacante: ");
    scanf("%d", &atacanteIdx);
    printf("Escolha o índice do território defensor: ");
    scanf("%d", &defensorIdx);

    atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);
    exibirTerritorios(mapa, nTerritorios);

    // Verificação de missões
    for(int i = 0; i < MAX_JOGADORES; i++) {
        if(verificarMissao(missoesJogadores[i], mapa, nTerritorios)) {
            printf("\nJogador %d cumpriu a sua missão e venceu!\n", i+1);
        } else {
            printf("\nJogador %d ainda nao cumpriu a sua missão.\n", i+1);
        }
    }

    liberarMemoria(mapa, missoesJogadores, MAX_JOGADORES);

    return 0;
}
