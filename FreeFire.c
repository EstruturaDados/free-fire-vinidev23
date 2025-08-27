#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

typedef enum {
    NOME,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade;
} Item;

Item inventario[MAX_ITENS];
int totalItens = 0;
bool inventarioOrdenadoPorNome = false;

void adicionarItem();
void removerItem();
void listarItens();
void buscarItemSequencial();
void ordenarInventario();
void buscarItemBinaria();
void limparBufferEntrada();
void trocarItens(Item* a, Item* b);

int main() {
    int opcao;

    do {
        printf("\n--- Mochila de Sobrevivencia ---\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (Busca Sequencial)\n");
        printf("5. Ordenar inventario\n");
        printf("6. Buscar item (Busca Binaria)\n");
        printf("7. Sair\n");
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
                buscarItemSequencial();
                break;
            case 5:
                ordenarInventario();
                break;
            case 6:
                buscarItemBinaria();
                break;
            case 7:
                printf("Fechando o sistema da mochila. Ate a proxima!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 7);

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

    do {
        printf("Prioridade (1 a 5): ");
        scanf("%d", &inventario[totalItens].prioridade);
        if (inventario[totalItens].prioridade < 1 || inventario[totalItens].prioridade > 5) {
            printf("Prioridade invalida. Escolha um valor entre 1 e 5.\n");
        }
    } while (inventario[totalItens].prioridade < 1 || inventario[totalItens].prioridade > 5);

    limparBufferEntrada();
    totalItens++;
    inventarioOrdenadoPorNome = false;
    printf("Item adicionado com sucesso!\n");
}

void removerItem() {
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
            for (int j = i; j < totalItens - 1; j++) {
                inventario[j] = inventario[j+1];
            }
            totalItens--;
            encontrado = 1;
            inventarioOrdenadoPorNome = false;
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
    printf("--------------------------------------------------------------------\n");
    printf("| %-20s | %-15s | %-10s | %-10s |\n", "Nome", "Tipo", "Quantidade", "Prioridade");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("| %-20s | %-15s | %-10d | %-10d |\n",
               inventario[i].nome,
               inventario[i].tipo,
               inventario[i].quantidade,
               inventario[i].prioridade);
    }

    printf("--------------------------------------------------------------------\n");
}

void buscarItemSequencial() {
    if (totalItens == 0) {
        printf("\nO inventario esta vazio. Nao ha itens para buscar.\n");
        return;
    }

    printf("\n--- Buscar Item (Sequencial) ---\n");
    char nomeBusca[50];
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("----------------------------------\n");
            printf("Nome: %s\n", inventario[i].nome);
            printf("Tipo: %s\n", inventario[i].tipo);
            printf("Quantidade: %d\n", inventario[i].quantidade);
            printf("Prioridade: %d\n", inventario[i].prioridade);
            printf("----------------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao encontrado no inventario.\n", nomeBusca);
    }
}

void ordenarInventario() {
    if (totalItens <= 1) {
        printf("\nNao ha itens suficientes para ordenar.\n");
        return;
    }

    int escolhaCriterio;
    printf("\n--- Ordenar Inventario ---\n");
    printf("Escolha o criterio de ordenacao:\n");
    printf("1. Nome (A-Z)\n");
    printf("2. Tipo (A-Z)\n");
    printf("3. Prioridade (1-5)\n");
    printf("Escolha: ");
    scanf("%d", &escolhaCriterio);
    limparBufferEntrada();

    CriterioOrdenacao criterio;
    switch (escolhaCriterio) {
        case 1:
            criterio = NOME;
            break;
        case 2:
            criterio = TIPO;
            break;
        case 3:
            criterio = PRIORIDADE;
            break;
        default:
            printf("Criterio invalido. Abortando ordenacao.\n");
            return;
    }

    long long comparacoes = 0;

    for (int i = 1; i < totalItens; i++) {
        Item chave = inventario[i];
        int j = i - 1;

        while (j >= 0) {
            bool condicaoTroca = false;
            comparacoes++;

            if (criterio == NOME) {
                if (strcmp(inventario[j].nome, chave.nome) > 0) {
                    condicaoTroca = true;
                }
            } else if (criterio == TIPO) {
                if (strcmp(inventario[j].tipo, chave.tipo) > 0) {
                    condicaoTroca = true;
                }
            } else if (criterio == PRIORIDADE) {
                if (inventario[j].prioridade > chave.prioridade) {
                    condicaoTroca = true;
                }
            }

            if (condicaoTroca) {
                inventario[j + 1] = inventario[j];
                j = j - 1;
            } else {
                break;
            }
        }
        inventario[j + 1] = chave;
    }
    
    printf("\nInventario ordenado com sucesso!\n");
    printf("Total de comparacoes realizadas: %lld\n", comparacoes);

    if (criterio == NOME) {
        inventarioOrdenadoPorNome = true;
    } else {
        inventarioOrdenadoPorNome = false;
    }
}

void buscarItemBinaria() {
    if (!inventarioOrdenadoPorNome) {
        printf("\nErro: O inventario precisa estar ordenado por nome para usar a Busca Binaria.\n");
        printf("Por favor, ordene por Nome (opcao 5) antes de tentar a busca.\n");
        return;
    }
    if (totalItens == 0) {
        printf("\nO inventario esta vazio. Nao ha itens para buscar.\n");
        return;
    }

    printf("\n--- Buscar Item (Binaria) ---\n");
    char nomeBusca[50];
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int inicio = 0;
    int fim = totalItens - 1;
    int encontrado = 0;
    
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        int comparacao = strcmp(inventario[meio].nome, nomeBusca);

        if (comparacao == 0) {
            printf("\nItem encontrado!\n");
            printf("----------------------------------\n");
            printf("Nome: %s\n", inventario[meio].nome);
            printf("Tipo: %s\n", inventario[meio].tipo);
            printf("Quantidade: %d\n", inventario[meio].quantidade);
            printf("Prioridade: %d\n", inventario[meio].prioridade);
            printf("----------------------------------\n");
            encontrado = 1;
            break;
        } else if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao encontrado no inventario.\n", nomeBusca);
    }
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}