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
void limparBufferEntrada();

int main() {
    int opcao;

    do {
        printf("\n--- Mochila de Sobrevivencia ---\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Sair\n");
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
    inventario[totalItens].nome[strcspn(inventario[totalItens].nome, "\n")] = 0; // Remove a quebra de linha

    printf("Tipo do item (ex: Arma, Curativo): ");
    fgets(inventario[totalItens].tipo, sizeof(inventario[totalItens].tipo), stdin);
    inventario[totalItens].tipo[strcspn(inventario[totalItens].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &inventario[totalItens].quantidade);
    limparBufferEntrada();

    totalItens++;
    printf("Item adicionado com sucesso!\n");
}

