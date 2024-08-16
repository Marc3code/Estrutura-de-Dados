#include <stdio.h>
#include <stdlib.h>

typedef struct grafo {
    int ponderado;
    int V;
    int A;
    int **adj;
    int *grau;
    float **pesos;
} Grafo;

// Função para criar um grafo
Grafo* criarGrafo(int V, int ponderado) {
    Grafo* G = (Grafo*)malloc(sizeof(Grafo));
    G->V = V;
    G->A = 0;
    G->ponderado = ponderado;
    
    // Alocando memória para a matriz de adjacência
    G->adj = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        G->adj[i] = (int*)calloc(V, sizeof(int));
    }
    
    // Alocando memória para o vetor de graus
    G->grau = (int*)calloc(V, sizeof(int));
    
    // Se for ponderado, alocar memória para a matriz de pesos
    if (ponderado) {
        G->pesos = (float**)malloc(V * sizeof(float*));
        for (int i = 0; i < V; i++) {
            G->pesos[i] = (float*)calloc(V, sizeof(float));
        }
    }
    
    return G;
}

// Função para inserir uma aresta no grafo
void inserirAresta(Grafo* G, int u, int v, float peso) {
    if (G->ponderado) {
        G->pesos[u][v] = peso;
        G->pesos[v][u] = peso; // Para grafos não direcionados
    }
    G->adj[u][v] = 1;
    G->adj[v][u] = 1; // Para grafos não direcionados
    G->grau[u]++;
    G->grau[v]++;
    G->A++;
}

// Função para remover uma aresta do grafo
void removerAresta(Grafo* G, int u, int v) {
    if (G->ponderado) {
        G->pesos[u][v] = 0;
        G->pesos[v][u] = 0; // Para grafos não direcionados
    }
    G->adj[u][v] = 0;
    G->adj[v][u] = 0; // Para grafos não direcionados
    G->grau[u]--;
    G->grau[v]--;
    G->A--;
}

// Função para liberar a memória alocada para o grafo
void liberarGrafo(Grafo* G) {
    for (int i = 0; i < G->V; i++) {
        free(G->adj[i]);
        if (G->ponderado) {
            free(G->pesos[i]);
        }
    }
    free(G->adj);
    free(G->grau);
    if (G->ponderado) {
        free(G->pesos);
    }
    free(G);
}

// Função para listar o grafo
void listarGrafo(Grafo* G) {
    printf("Lista de Adjacencias do Grafo:\n");
    for (int i = 0; i < G->V; i++) {
        printf("%d: ", i);
        for (int j = 0; j < G->V; j++) {
            if (G->adj[i][j]) {
                printf("%d ", j);
                if (G->ponderado) {
                    printf("(%.2f) ", G->pesos[i][j]);
                }
            }
        }
        printf("\n");
    }
}

// Função para ler o grafo a partir de um arquivo
Grafo* lerGrafoDeArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    int V, A, ponderado;
    fscanf(arquivo, "%d %d %d", &V, &A, &ponderado);
    Grafo* G = criarGrafo(V, ponderado);

    int u, v;
    float peso;
    for (int i = 0; i < A; i++) {
        fscanf(arquivo, "%d %d", &u, &v);
        if (ponderado) {
            fscanf(arquivo, "%f", &peso);
            inserirAresta(G, u, v, peso);
        } else {
            inserirAresta(G, u, v, 0); // Não ponderado
        }
    }

    fclose(arquivo);
    return G;
}

int main() {
    Grafo* G = lerGrafoDeArquivo("grafo.txt");
    if (G == NULL) {
        return 1;
    }

    listarGrafo(G);

    liberarGrafo(G);
    return 0;
}
