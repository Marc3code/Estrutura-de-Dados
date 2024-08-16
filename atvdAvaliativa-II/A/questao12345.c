#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct No
{
    int valor;
    int contador;
    struct No *esquerda;
    struct No *direita;
} No;

// Função para criar um novo nó
No *criarNo(int valor) {
    No *novoNo = malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->contador = 0; 
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um valor na árvore
No *inserir(No *raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }

    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    } else {
        // Valor encontrado é igual ao valor do nó atual
        raiz->contador++;
        printf("Valor %d ja existe na arvore. Contador incrementado para %d\n", valor, raiz->contador);
        return raiz;
    }

    return raiz;
}

// Função para listar os valores da árvore em pré-ordem
void listar(No *raiz)
{

    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);
        listar(raiz->esquerda);
        listar(raiz->direita);
    }
}

// Função para encontrar o menor valor na árvore
No *encontrarMinimo(No *raiz)
{
    No *atual = raiz;
    while (atual && atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }
    return atual;
}

// função para encontrar maior valor na arvore
No *encontrarMaximo(No *raiz)
{
    No *atual = raiz;
    while (atual->direita && atual != NULL)
    {
        atual = atual->direita;
    }
    printf("o maior valor da arvore eh: %d\n", atual->valor);
}

// Função para remover um valor da árvore
No *remover(No *raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else { //se nao for igual, entra nos possíveis casos
        // Caso 1: Nó sem filhos ou apenas um filho
        if (raiz->esquerda == NULL) {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 2: Nó com dois filhos, encontrar o sucessor em ordem
        No *temp = encontrarMinimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->contador = temp->contador; // Atualiza o contador
        raiz->direita = remover(raiz->direita, temp->valor);
    }
    return raiz;
}

// Função para verificar se a árvore é cheia
int arvoreCheia(No *raiz) {
    if (raiz == NULL) {
        return 1;
    }
    
    // Verifica se o nó atual não é uma folha e tem ambos os filhos
    if (raiz->esquerda == NULL && raiz->direita == NULL) {
        return 1; // Se for folha, retorna verdadeiro para manter a propriedade da árvore cheia
    }
    
    if (raiz->esquerda != NULL && raiz->direita != NULL) {
        // Verifica se ambos os filhos também são árvores cheias
        return arvoreCheia(raiz->esquerda) && arvoreCheia(raiz->direita);
    }
    
    // Se chegou aqui, significa que o nó não é uma folha e não tem ambos os filhos, logo a árvore não é cheia
    return 0;
}


int main()
{
    No *raiz = NULL;

    // Inserção dos elementos
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 1);
    raiz = inserir(raiz, 3);
    raiz = inserir(raiz, 4);
   


    // encontrando maior valor
    encontrarMaximo(raiz);

    // listagem arvore original
    printf("arvore original: ");
    listar(raiz);
    printf("\n");

    // Remoção dos nós 9, 5 e 20
    raiz = remover(raiz, 2);
   

    // listagem apos remocao
    printf("arvore apos remocao: ");
    listar(raiz);
    printf("\n");

    raiz = inserir(raiz, 2);
    
    return 0;
}
