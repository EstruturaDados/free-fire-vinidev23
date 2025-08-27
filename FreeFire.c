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