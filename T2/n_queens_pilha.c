#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// Estrutura para armazenar a posição de cada rainha
typedef struct
{
    int linha;  // Linha onde a rainha está posicionada
    int coluna; // Coluna onde a rainha está posicionada
} Rainha;

// Função para imprimir uma solução encontrada
void imprimir_solucao(Rainha *rainhas, int n)
{
    char **tabuleiro = (char **)malloc(n * sizeof(char *)); // Alocação dinâmica para o tabuleiro
    for (int i = 0; i < n; i++)
    {
        tabuleiro[i] = (char *)malloc(n * sizeof(char)); // Alocação dinâmica para cada linha do tabuleiro
    }

    // Inicializa o tabuleiro com espaços vazios representados por '_'
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tabuleiro[i][j] = '_';

    // Coloca as rainhas no tabuleiro com base nas posições armazenadas
    for (int i = 0; i < n; i++)
    {
        tabuleiro[rainhas[i].linha][rainhas[i].coluna] = 'R'; // 'R' representa uma rainha
    }

    // Imprime o tabuleiro
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c ", tabuleiro[i][j]); // Imprime cada célula do tabuleiro
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro
    }
    printf("\n"); // Linha em branco entre soluções

    // Libera a memória alocada para o tabuleiro
    for (int i = 0; i < n; i++)
    {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

// Função para verificar se a posição (linha, coluna) é segura para colocar uma rainha
int eh_seguro(Rainha *rainhas, int n, int linha, int coluna)
{
    // Verifica cada rainha já colocada
    for (int i = 0; i < linha; i++)
    {
        // Verifica se alguma rainha está na mesma coluna
        // Verifica as diagonais
        if (rainhas[i].coluna == coluna ||
            rainhas[i].linha - rainhas[i].coluna == linha - coluna ||
            rainhas[i].linha + rainhas[i].coluna == linha + coluna)
        {
            return 0; // Não é seguro, pois há um ataque
        }
    }
    return 1; // É seguro, nenhuma rainha ataca
}

// Função para resolver o problema das n rainhas usando pilha
void resolver_n_rainhas(int n)
{
    pilha P = cria_pilha();                                 // Cria uma nova pilha para armazenar estados
    Rainha *rainhas = (Rainha *)malloc(n * sizeof(Rainha)); // Alocação dinâmica para armazenar as posições das rainhas
    int linha = 0, coluna = 0;                              // Variáveis para rastrear a linha e a coluna atuais

    while (1)
    {
        // Tenta colocar uma rainha na coluna atual da linha atual
        while (coluna < n)
        {
            // Verifica se é seguro colocar a rainha na posição atual
            if (eh_seguro(rainhas, linha, linha, coluna))
            {
                // Armazena a posição da rainha
                rainhas[linha].linha = linha;
                rainhas[linha].coluna = coluna;

                // Se todas as rainhas foram colocadas, imprime a solução
                if (linha == n - 1)
                {
                    imprimir_solucao(rainhas, n);
                }
                else
                {
                    // Empilha o estado atual (linha atual e coluna inicial)
                    empilhar(P, linha);
                    linha++;    // Avança para a próxima linha
                    coluna = 0; // Reinicia a coluna para a nova linha
                    continue;   // Continua o loop para tentar a próxima coluna
                }
            }
            coluna++; // Avança para a próxima coluna
        }

        // Se não há mais colunas para explorar na linha atual
        // Desempilha o último estado
        if (pilha_vazia(P))
            break; // Se a pilha está vazia, encerra o loop

        linha = desempilhar(P);             // Retorna para a linha anterior
        coluna = rainhas[linha].coluna + 1; // Avança para a próxima coluna da linha anterior
    }

    free(rainhas);   // Libera a memória alocada para as rainhas
    libera_pilha(P); // Libera a pilha após terminar a busca por soluções
}

int main()
{
    int n; // Variável para armazenar o tamanho do tabuleiro (n x n)
    scanf("%d", &n);

    // Verifica se o valor de n é positivo
    if (n < 1)
    {
        printf("Valor de n deve ser maior ou igual a 1.\n");
        return -1; // Encerra o programa com erro
    }

    resolver_n_rainhas(n); // Chama a função para resolver o problema das n rainhas
    return 0;
}

/*
gcc -Wall -pedantic-errors pilha.c -c -o pilha.o
  gcc -Wall -pedantic-errors n_queens_pilha.c -c -o n_queens_pilha.o
  gcc -Wall -pedantic-errors pilha.o n_queens_pilha.o -o exec
  ./exec
*/
