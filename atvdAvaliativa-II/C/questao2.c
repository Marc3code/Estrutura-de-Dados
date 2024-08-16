#include <stdio.h>
#include <stdlib.h>

#define INF 99999

typedef struct grafo {
    int ponderado;
    int V;
    int A;
    int **adj;
    int *grau;
    float **pesos;
} Grafo;

// Função para alocar matriz de adjacência
int **alocaMatriz(int linhas, int colunas) {
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++)
        matriz[i] = (int *)malloc(colunas * sizeof(int));
    return matriz;
}

// Função para inicializar o grafo
Grafo *inicializaGrafo(int V) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->V = V;
    grafo->A = 0;
    grafo->ponderado = 1; // Considerando que o grafo é ponderado

    grafo->adj = alocaMatriz(V, V);
    grafo->grau = (int *)calloc(V, sizeof(int));
    grafo->pesos = alocaMatriz(V, V);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            grafo->adj[i][j] = INF; // Inicializa todas as distâncias como infinito
            grafo->pesos[i][j] = 0; // Inicializa todos os pesos como zero
        }
    }
    return grafo;
}

// Função para adicionar aresta ponderada ao grafo
void adicionaAresta(Grafo *grafo, int origem, int destino, int peso) {
    grafo->adj[origem][destino] = peso;
    grafo->pesos[origem][destino] = peso;
    grafo->A++;
}

// Função para executar o algoritmo de Floyd-Warshall
void floydWarshall(Grafo *grafo) {
    int V = grafo->V;
    int **distancias = grafo->adj;

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (distancias[i][k] + distancias[k][j] < distancias[i][j])
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
            }
        }
    }
}

// Função para imprimir as distâncias mínimas entre todos os pares de vértices
void imprimeDistancias(Grafo *grafo) {
    int V = grafo->V;
    int **distancias = grafo->adj;

    printf("Distancias minimas entre todos os pares de vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (distancias[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", distancias[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int V = 4;
    Grafo *grafo = inicializaGrafo(V);

    // Adiciona arestas e seus pesos
    adicionaAresta(grafo, 0, 1, 5);
    adicionaAresta(grafo, 0, 3, 10);
    adicionaAresta(grafo, 1, 2, 3);
    adicionaAresta(grafo, 2, 3, 1);

    // Executa o algoritmo de Floyd-Warshall
    floydWarshall(grafo);

    // Imprime as distâncias mínimas entre todos os pares de vértices
    imprimeDistancias(grafo);

    return 0;
}
