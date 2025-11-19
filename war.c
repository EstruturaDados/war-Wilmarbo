#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Cadastro do território %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

// Função para exibir os dados dos territórios
void exibirTerritorios(Territorio* mapa, int quantidade) {
    printf("\n--- Territórios cadastrados ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

// Função que simula o ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: não é possível atacar um território da mesma cor!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque de %s contra %s\n", atacante->nome, defensor->nome);
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Resultado: defensor resistiu ao ataque.\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

// Função para liberar a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios

    int quantidade;
    printf("Digite o número de territórios a cadastrar: ");
    scanf("%d", &quantidade);

    // Alocação dinâmica de memória para os territórios
    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);
    exibirTerritorios(mapa, quantidade);

    // Simulação de ataque
    int atacante, defensor;
    printf("\nEscolha o número do território atacante (1 a %d): ", quantidade);
    scanf("%d", &atacante);
    printf("Escolha o número do território defensor (1 a %d): ", quantidade);
    scanf("%d", &defensor);

    if (atacante < 1 || atacante > quantidade || defensor < 1 || defensor > quantidade) {
        printf("Territórios inválidos.\n");
    } else {
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
        exibirTerritorios(mapa, quantidade);
    }

    liberarMemoria(mapa);
    return 0;
}
