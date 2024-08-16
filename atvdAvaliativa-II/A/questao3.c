#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os nós da árvore
typedef struct No {
    char nome[50];
    char sexo;
    int idade;
    float peso;
    struct No *esquerda;
    struct No *direita;
} No;

// Função para criar um novo nó da árvore
No *criarNo(char nome[], char sexo, int idade, float peso) {
    No* novoNo = malloc(sizeof(No));
    strcpy(novoNo->nome, nome);
    novoNo->sexo = sexo;
    novoNo->idade = idade;
    novoNo->peso = peso;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um nó na árvore
No* inserir(No *raiz, char nome[], char sexo, int idade, float peso) {
    if (raiz == NULL) {
        return criarNo(nome, sexo, idade, peso);
    }

    int cmp = strcmp(nome, raiz->nome);
    if (cmp < 0) {
        raiz->esquerda = inserir(raiz->esquerda, nome, sexo, idade, peso);
    } else if (cmp > 0) {
        raiz->direita = inserir(raiz->direita, nome, sexo, idade, peso);
    }

    return raiz;
}

// Função para percorrer a árvore em ordem e adicionar os nós às listas correspondentes
void percorrerArvore(No *raiz, No **listaHomens, No **listaMulheres) {
    if (raiz != NULL) {
        percorrerArvore(raiz->esquerda, listaHomens, listaMulheres);
        if (raiz->sexo == 'M') {
            *listaHomens = inserir(*listaHomens, raiz->nome, raiz->sexo, raiz->idade, raiz->peso);
        } else {
            *listaMulheres = inserir(*listaMulheres, raiz->nome, raiz->sexo, raiz->idade, raiz->peso);
        }
        percorrerArvore(raiz->direita, listaHomens, listaMulheres);
    }
}

// Função para imprimir uma lista
void imprimirLista(No *lista) {
    No* atual = lista;
    while (atual != NULL) {
        printf("Nome: %s, Sexo: %c, Idade: %d, Peso: %.2f\n", atual->nome, atual->sexo, atual->idade, atual->peso);
        atual = atual->direita; // Avançar para o próximo nó na lista
    }
}

int main() {
   
    No *raiz = NULL;

    raiz = inserir(raiz, "Bia", 'F', 35, 55.0);
    raiz = inserir(raiz, "Joao", 'M', 30, 70.5);
    raiz = inserir(raiz, "Maria", 'F', 25, 60.2);
    raiz = inserir(raiz, "Bia", 'F', 20, 55.4);
     raiz = inserir(raiz, "Fatima", 'F', 20, 55.4);

    
    No *listaHomens = NULL;
    No *listaMulheres = NULL;

    
    percorrerArvore(raiz, &listaHomens, &listaMulheres);

   
    printf("Lista de Homens:\n");
    imprimirLista(listaHomens);
    printf("\n");

    printf("Lista de Mulheres:\n");
    imprimirLista(listaMulheres);
    printf("\n");

    return 0;
}
