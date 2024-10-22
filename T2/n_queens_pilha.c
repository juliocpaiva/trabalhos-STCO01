#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// Verifica se a posição da rainha é válida
int eh_valido(int *rainhas, int linha, int coluna)
{
    for (int i = 0; i < linha; i++)
    {
        if (rainhas[i] == coluna || (rainhas[i] - coluna) == (i - linha) || (rainhas[i] - coluna) == (linha - i))
        {
            return 0; // Falso
        }
    }
    return 1; // Verdadeiro
}

// Função para resolver o problema das N-Rainhas armazenando as soluções em um vetor
void resolver_n_rainhas(int n, int ***solucoes, int *num_solucoes)
{
    pilha p = cria_pilha(); // Cria a pilha para gerenciar o estado
    int *rainhas = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        rainhas[i] = -1; // Inicializa as rainhas como não posicionadas
    }

    int linha = 0; // Começa na linha 0

    while (linha >= 0)
    {
        int coluna;
        for (coluna = rainhas[linha] + 1; coluna < n; coluna++)
        {
            if (eh_valido(rainhas, linha, coluna))
            {
                rainhas[linha] = coluna; // Coloca a rainha na coluna válida
                break;                   // Sai do loop se encontrou uma coluna válida
            }
        }

        if (coluna < n)
        { // Se encontrou uma coluna válida
            if (linha == n - 1)
            { // Se todas as rainhas estão posicionadas
                (*num_solucoes)++;
                *solucoes = (int **)realloc(*solucoes, (*num_solucoes) * sizeof(int *));
                (*solucoes)[*num_solucoes - 1] = (int *)malloc(n * sizeof(int));
                for (int i = 0; i < n; i++)
                {
                    (*solucoes)[*num_solucoes - 1][i] = rainhas[i]; // Armazena a solução
                }
            }
            else
            {
                linha++; // Passa para a próxima linha
            }
        }
        else
        {                        // Se não encontrou coluna válida
            rainhas[linha] = -1; // Reinicia a coluna da linha atual
            linha--;             // Volta para a linha anterior
        }
    }

    free(rainhas);   // Libera a memória alocada
    libera_pilha(p); // Libera a pilha, se necessário
}

// Função para imprimir as soluções com 'R' para rainhas e '_' para espaços vazios
void imprimir_solucoes(int n, int **solucoes, int num_solucoes)
{
    for (int i = 0; i < num_solucoes; i++)
    {
        for (int linha = 0; linha < n; linha++)
        {
            for (int coluna = 0; coluna < n; coluna++)
            {
                if (solucoes[i][linha] == coluna)
                {
                    printf("R ");
                }
                else
                {
                    printf("_ ");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    if (n <= 0)
    {
        return 1;
    }

    int **solucoes = NULL; // Vetor de ponteiros para armazenar as soluções
    int num_solucoes = 0;

    resolver_n_rainhas(n, &solucoes, &num_solucoes);

    if (num_solucoes > 0)
    {
        imprimir_solucoes(n, solucoes, num_solucoes);
    }

    // Libera a memória alocada para as soluções
    for (int i = 0; i < num_solucoes; i++)
    {
        free(solucoes[i]);
    }
    free(solucoes);

    return 0;
}

/*
gcc -Wall -pedantic-errors pilha.c -c -o pilha.o
  gcc -Wall -pedantic-errors n_queens_pilha.c -c -o n_queens_pilha.o
  gcc -Wall -pedantic-errors pilha.o n_queens_pilha.o -o exec
  ./exec
*/
