#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No
{
    char nome[50];
    char sexo;
    int idade;
    float peso;
    int altura;
    struct No *esquerda;
    struct No *direita;
} No;

No *criarNo(char nome[], char sexo, int idade, float peso)
{
    No *novoNo = (No *)malloc(sizeof(No));
    strcpy(novoNo->nome, nome);
    novoNo->sexo = sexo;
    novoNo->idade = idade;
    novoNo->peso = peso;
    novoNo->altura = 1; // Inicialmente, a altura de um nó é 1
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int altura(No *no)
{
    if (no == NULL)
        return 0;
    return no->altura;
}

int fatorBalanceamento(No *no)
{
    if (no == NULL)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}

No *rotacaoDireita(No *y)
{
    No *x = y->esquerda;
    No *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

No *atualizarAltura(No *no)
{
    if (no == NULL)
    {
        return no;
    }
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
    return no;
}

// Função para realizar uma rotação simples à esquerda
No *rotacaoEsquerda(No *x)
{
    No *y = x->direita;
    No *T2 = y->esquerda;

    // Realizar a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualizar alturas
    x = atualizarAltura(x);
    y = atualizarAltura(y);

    return y;
}

// Função para encontrar o nó com o menor valor (nó mais à esquerda)
No *encontrarMenorValor(No *no)
{
    No *atual = no;

    // Percorre a árvore até encontrar o nó mais à esquerda
    while (atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }

    return atual;
}

// Função para remover um nó da árvore AVL
No *remover(No *raiz, char nome[])
{
    if (raiz == NULL)
    {
        return raiz;
    }

    // Busca pelo nó a ser removido
    int cmp = strcmp(nome, raiz->nome);
    if (cmp < 0)
    {
        raiz->esquerda = remover(raiz->esquerda, nome);
    }
    else if (cmp > 0)
    {
        raiz->direita = remover(raiz->direita, nome);
    }
    else
    {
        // Nó encontrado, realizar a remoção
        // Caso 1: Nó sem filhos ou com apenas um filho
        if (raiz->esquerda == NULL || raiz->direita == NULL)
        {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            // Caso 1a: Nó sem filhos
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            {                  // Caso 1b: Nó com um filho
                *raiz = *temp; // Copia os conteúdos do filho não nulo
            }
            free(temp);
        }
        else
        {
            // Caso 2: Nó com dois filhos
            // Encontrar o sucessor na subárvore direita (menor nó à direita)
            No *temp = raiz->direita;
            while (temp->esquerda != NULL)
            {
                temp = temp->esquerda;
            }
            // Copiar os dados do sucessor para este nó
            strcpy(raiz->nome, temp->nome);
            raiz->sexo = temp->sexo;
            raiz->idade = temp->idade;
            raiz->peso = temp->peso;
            // Remover o sucessor
            raiz->direita = remover(raiz->direita, temp->nome);
        }
    }

    // Se a árvore tinha apenas um nó, retornar
    if (raiz == NULL)
    {
        return raiz;
    }

    raiz = atualizarAltura(raiz);
    int balance = fatorBalanceamento(raiz);

    // Se o nó ficou desbalanceado, aplicar rotações
    // Verificar os quatro casos de rotação
    // Retornar o nó atualizado
    if (balance > 1 && fatorBalanceamento(raiz->esquerda) >= 0)
    {
        return rotacaoDireita(raiz);
    }
    if (balance < -1 && fatorBalanceamento(raiz->direita) <= 0)
    {
        return rotacaoEsquerda(raiz);
    }
    if (balance > 1 && fatorBalanceamento(raiz->esquerda) < 0)
    {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }
    if (balance < -1 && fatorBalanceamento(raiz->direita) > 0)
    {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void imprimirListaEmOrdem(No *no, char sexo)
{
    if (no != NULL)
    {
        imprimirListaEmOrdem(no->esquerda, sexo);
        if (no->sexo == sexo)
        {
            printf("Nome: %s, Sexo: %c, Idade: %d, Peso: %.2f\n", no->nome, no->sexo, no->idade, no->peso);
        }
        imprimirListaEmOrdem(no->direita, sexo);
    }
}

No *inserir(No *raiz, char nome[], char sexo, int idade, float peso)
{
    if (raiz == NULL)
    {
        return criarNo(nome, sexo, idade, peso);
    }

    int cmp = strcmp(nome, raiz->nome);
    if (cmp < 0)
    {
        raiz->esquerda = inserir(raiz->esquerda, nome, sexo, idade, peso);
    }
    else if (cmp > 0)
    {
        raiz->direita = inserir(raiz->direita, nome, sexo, idade, peso);
    }
    else
    {
        printf("Nome duplicado, não é possível inserir.\n");
    }

    raiz = atualizarAltura(raiz);

    return raiz;
}

No *consultar(No *raiz, char nome[])
{
    if (raiz == NULL || strcmp(nome, raiz->nome) == 0)
    {
        return raiz;
    }

    if (strcmp(nome, raiz->nome) < 0)
    {
        return consultar(raiz->esquerda, nome);
    }
    else
    {
        return consultar(raiz->direita, nome);
    }
}

void menu()
{
    printf("\nMenu de Opcoes:\n");
    printf("1. Inserir um novo individuo\n");
    printf("2. Listar todos os individuos\n");
    printf("3. Remover um individuo\n");
    printf("4. Consultar um individuo\n");
    printf("5. Mostrar altura da arvore\n");
    printf("6. Sair\n");
}

int main()
{
    No *raiz = NULL;
    int opcao;
    char nome[50], sexo;
    int idade;
    float peso;

    do
    {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o nome: ");
            scanf("%s", nome);
            printf("Digite o sexo (M/F): ");
            scanf(" %c", &sexo);
            printf("Digite a idade: ");
            scanf("%d", &idade);
            printf("Digite o peso: ");
            scanf("%f", &peso);
            raiz = inserir(raiz, nome, sexo, idade, peso);
            break;
        case 2:
            printf("Lista de Individuos:\n");
            imprimirListaEmOrdem(raiz, 'M');
            imprimirListaEmOrdem(raiz, 'F');
            break;
        case 3:
            printf("Digite o nome do individuo a ser removido: ");
            scanf("%s", nome);
            raiz = remover(raiz, nome);
            break;
        case 4:
            printf("Digite o nome do individuo a ser consultado: ");
            scanf("%s", nome);
            No *resultado = consultar(raiz, nome);
            if (resultado != NULL)
            {
                printf("Individuo encontrado:\n");
                printf("Nome: %s, Sexo: %c, Idade: %d, Peso: %.2f\n", resultado->nome, resultado->sexo, resultado->idade, resultado->peso);
            }
            else
            {
                printf("Individuo não encontrado.\n");
            }
            break;
        case 5:
            printf("a altura da arvore eh %d", raiz->altura);
            break; 
        case 6:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
