#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valor;
    int peso;
} Item;

int comparar(const void *a, const void *b) {
    double proporcao_a = ((Item *)a)->valor / (double)((Item *)a)->peso;
    double proporcao_b = ((Item *)b)->valor / (double)((Item *)b)->peso;
    if (proporcao_a < proporcao_b)
        return -1;
    else if (proporcao_a > proporcao_b)
        return 1;
    else
        return 0;
}

int mochila_gulosa(Item itens[], int n, int capacidade) {
    qsort(itens, n, sizeof(Item), comparar);

    int valor_maximo = 0;
    int peso_atual = 0;

    for (int i = 0; i < n; i++) {
        if (itens[i].peso + peso_atual <= capacidade) {
            valor_maximo += itens[i].valor;
            peso_atual += itens[i].peso;
        }
    }

    return valor_maximo;
}

int main() {
    Item itens[] = {{60, 10}, {100, 20}, {120, 30}};
    int n = sizeof(itens) / sizeof(itens[0]);
    int capacidade = 50;
    printf("Valor Maximo (Guloso): %d\n", mochila_gulosa(itens, n, capacidade));
    // A saída deve ser: 220
    return 0;
}