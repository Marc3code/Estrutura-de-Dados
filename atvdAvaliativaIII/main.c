#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_VERTICES 110

// Função para sortear aleatoriamente dois vértices
void sortearVertices(int *vertice1, int *vertice2, int num_vertices)
{
   
    srand(time(NULL));

    // Sorteia dois vértices aleatórios
    *vertice1 = rand() % num_vertices;
    *vertice2 = rand() % num_vertices;
}

// Função para calcular a menor distância entre dois vértices usando o algoritmo de Dijkstra
int dijkstra(int matriz_distancias[MAX_VERTICES][MAX_VERTICES], int origem, int destino, int num_vertices)
{
    int distancia[num_vertices];
    int visitado[num_vertices];
    int i, j, min_dist, proximo_vertice;

    // Inicializa as distâncias como infinito e os vértices como não visitados
    for (i = 0; i < num_vertices; i++)
    {
        distancia[i] = INT_MAX;
        visitado[i] = 0;
    }

    // A distância da origem para ela mesma é zero
    distancia[origem] = 0;

    // Encontra a menor distância para todos os vértices
    for (i = 0; i < num_vertices - 1; i++)
    {
        min_dist = INT_MAX;

        // Escolhe o vértice com a menor distância não visitado
        for (j = 0; j < num_vertices; j++)
        {
            if (visitado[j] == 0 && distancia[j] <= min_dist)
            {
                min_dist = distancia[j];
                proximo_vertice = j;
            }
        }

        // Marca o vértice escolhido como visitado
        visitado[proximo_vertice] = 1;

        // Atualiza as distâncias para os vértices adjacentes ao vértice escolhido
        for (j = 0; j < num_vertices; j++)
        {
            if (!visitado[j] && matriz_distancias[proximo_vertice][j] && distancia[proximo_vertice] != INT_MAX &&
                distancia[proximo_vertice] + matriz_distancias[proximo_vertice][j] < distancia[j])
            {
                distancia[j] = distancia[proximo_vertice] + matriz_distancias[proximo_vertice][j];
            }
        }
    }

    return distancia[destino];
}

// Função para calcular o menor caminho entre os locais do acidente e um hospital de atendimento de urgência
void menorCaminhoAcidenteHospital(int matriz_distancias[MAX_VERTICES][MAX_VERTICES], int hospital, int *vertices_acidente, int num_vertices)
{
    int i;

    printf("\nMenor caminho do acidente ao Hospital %d:\n", hospital);

    // Calcula a menor distância para cada local do acidente até o hospital
    for (i = 0; i < 2; i++)
    {
        int menor_distancia = dijkstra(matriz_distancias, vertices_acidente[i], hospital, num_vertices);
        printf("Local do acidente %d -> Hospital %d: %d\n", i + 1, hospital, menor_distancia);
    }
}

void menu()
{
    printf(" 1. Sortear vertices \n");
    printf(" 2. Calcular distancia da SAMU ate o acidente \n");
    printf(" 3. Calcular distancia do acidente ate hospital mais proximo \n");
    printf("4. Sair");
}

int main()
{
    FILE *arquivo;
    int matriz_distancias[MAX_VERTICES][MAX_VERTICES];
    int num_vertices, linha, coluna;
    int opcao;

    // Abre o arquivo
    arquivo = fopen("DistSAMU_110.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê o número de linhas e colunas (matriz quadrada)
    fscanf(arquivo, "%d", &num_vertices);

    // Lê a matriz de distâncias
    for (linha = 0; linha < num_vertices; linha++)
    {
        for (coluna = 0; coluna < num_vertices; coluna++)
        {
            fscanf(arquivo, "%d", &matriz_distancias[linha][coluna]);
        }
    }

    // Vértices especiais
    int hospital1 = 40;
    int hospital2 = 19;
    int hospital3 = 82;
    int central_samu = 83;
    int vertice_acidente1, vertice_acidente2;

    do
    {
        menu();
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            // Sorteia dois vértices para a ocorrência de um acidente

            sortearVertices(&vertice_acidente1, &vertice_acidente2, num_vertices);
            printf("\nAcidente ocorrido entre os vértices %d e %d.\n", vertice_acidente1, vertice_acidente2);
            break;

        case 2:
            // Calcula a menor distância da central do SAMU ao acidente
            int menor_distancia_samu_acidente = dijkstra(matriz_distancias, central_samu, vertice_acidente1, num_vertices);
            printf("Menor distância da central do SAMU ao acidente: %d\n", menor_distancia_samu_acidente);
            break;

        case 3:
            // Calcula o menor caminho dos locais do acidente para um hospital de atendimento de urgência
           int vertices_acidente[2] = {vertice_acidente1, vertice_acidente2};
            menorCaminhoAcidenteHospital(matriz_distancias, hospital1, vertices_acidente, num_vertices);
            menorCaminhoAcidenteHospital(matriz_distancias, hospital2, vertices_acidente, num_vertices);
            menorCaminhoAcidenteHospital(matriz_distancias, hospital3, vertices_acidente, num_vertices); 
            break;

        default:
            break;
        }
    } while (opcao != 4);

    // Fecha o arquivo
    fclose(arquivo);

    // Calcula as distâncias entre os vértices especiais
    printf("Distância entre Hospital 1 e Hospital 2: %d\n", matriz_distancias[hospital1][hospital2]);
    printf("Distância entre Hospital 1 e Hospital 3: %d\n", matriz_distancias[hospital1][hospital3]);
    printf("Distância entre Hospital 1 e Central do SAMU: %d\n", matriz_distancias[hospital1][central_samu]);
    printf("Distância entre Hospital 2 e Hospital 3: %d\n", matriz_distancias[hospital2][hospital3]);
    printf("Distância entre Hospital 2 e Central do SAMU: %d\n", matriz_distancias[hospital2][central_samu]);
    printf("Distância entre Hospital 3 e Central do SAMU: %d\n", matriz_distancias[hospital3][central_samu]);

    return 0;
}
