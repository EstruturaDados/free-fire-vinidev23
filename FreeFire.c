#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
} Item;

Item inventario[MAX_ITENS];
int totalItens = 0;

void adicionarItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBufferEntrada();

int main() {
    int opcao;

    do {
        printf("\n--- Mochila de Sobrevivencia ---\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item por nome\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("Fechando o sistema da mochila. Ate a proxima!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}

void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Inventario cheio! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Item ---\n");

    printf("Nome do item: ");
    fgets(inventario[totalItens].nome, sizeof(inventario[totalItens].nome), stdin);
    inventario[totalItens].nome[strcspn(inventario[totalItens].nome, "\n")] = 0;

    printf("Tipo do item (ex: Arma, Curativo): ");
    fgets(inventario[totalItens].tipo, sizeof(inventario[totalItens].tipo), stdin);
    inventario[totalItens].tipo[strcspn(inventario[totalItens].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &inventario[totalItens].quantidade);
    limparBufferEntrada();

    totalItens++;
    printf("Item adicionado com sucesso!\n");
}

void removerItem() {
    if (totalItens == 0) {
        printf("O inventario esta vazio. Nao ha itens para remover.\n");
        return;
    }

    printf("\n--- Remover Item ---\n");
    char nomeRemover[50];
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(inventario[i].nome, nomeRemover) == 0) {
            // Item encontrado, agora o removemos
            for (int j = i; j < totalItens - 1; j++) {
                inventario[j] = inventario[j+1];
            }
            totalItens--;
            encontrado = 1;
            printf("Item '%s' removido com sucesso.\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado no inventario.\n", nomeRemover);
    }
}

void listarItens() {
    if (totalItens == 0) {
        printf("\nO inventario esta vazio. Adicione itens para visualiza-los.\n");
        return;
    }

    printf("\n--- Itens no Inventario (%d/%d) ---\n", totalItens, MAX_ITENS);
    printf("--------------------------------------------------\n");
    printf("| %-20s | %-15s | %-10s |\n", "Nome", "Tipo", "Quantidade");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("| %-20s | %-15s | %-10d |\n",
               inventario[i].nome,
               inventario[i].tipo,
               inventario[i].quantidade);
    }

    printf("--------------------------------------------------\n");
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}