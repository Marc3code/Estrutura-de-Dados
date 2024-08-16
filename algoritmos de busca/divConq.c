#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int mochila_dividir_conquistar(int valores[], int pesos[], int n, int capacidade) {
    // Caso base: se não há itens ou a capacidade da mochila é zero
    if (n == 0 || capacidade == 0)
        return 0;
    
    // Se o peso do último item é maior que a capacidade, então esse item não pode ser incluído
    if (pesos[n - 1] > capacidade)
        return mochila_dividir_conquistar(valores, pesos, n - 1, capacidade);
    
    // Retornar o máximo entre duas possibilidades:
    // 1. Incluir o último item
    // 2. Não incluir o último item
    else
        return max(valores[n - 1] + mochila_dividir_conquistar(valores, pesos, n - 1, capacidade - pesos[n - 1]), 
                   mochila_dividir_conquistar(valores, pesos, n - 1, capacidade));
}

int main() {
    int valores[] = {60, 100, 120};
    int pesos[] = {10, 20, 30};
    int capacidade = 50;
    int n = sizeof(valores) / sizeof(valores[0]);
    printf("Valor Maximo (Dividir e Conquistar): %d\n", mochila_dividir_conquistar(valores, pesos, n, capacidade)); 
    // Saída deve ser: 220
    return 0;
}
