#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct
{
    int linha;
    int coluna;
} Rainha;

// Função para imprimir uma solução encontrada
void imprimir_solucao(Rainha *rainhas, int n, char **tabuleiro)
{
    // Inicializa o tabuleiro com espaços vazios representados por '_'
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tabuleiro[i][j] = '_';

    // Coloca as rainhas no tabuleiro com base nas posições armazenadas
    for (int i = 0; i < n; i++)
        tabuleiro[rainhas[i].linha][rainhas[i].coluna] = 'R';

    // Imprime o tabuleiro
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%c ", tabuleiro[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Função para verificar se a posição (linha, coluna) é segura para colocar uma rainha
int posicao_segura(Rainha *rainhas, int linha, int coluna)
{
    // Verifica cada rainha já colocada em linhas anteriores
    for (int i = 0; i < linha; i++)
    {
        // Verifica se alguma rainha está na mesma coluna ou nas diagonais
        if (rainhas[i].coluna == coluna ||                            // Mesma coluna
            rainhas[i].linha - rainhas[i].coluna == linha - coluna || // Diagonal principal
            rainhas[i].linha + rainhas[i].coluna == linha + coluna)   // Diagonal secundária
            return 0;                                                 // Não é seguro, pois há um ataque
    }
    return 1; // É seguro, nenhuma rainha ataca
}

// Função para resolver o problema das n-rainhas
void resolver_n_rainhas(int n)
{
    pilha P = cria_pilha();                                 // Cria uma nova pilha para armazenar estados
    Rainha *rainhas = (Rainha *)malloc(n * sizeof(Rainha)); // Alocação para posições das rainhas

    // Aloca uma vez o tabuleiro para evitar realocação desnecessária a cada impressão
    char **tabuleiro = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
        tabuleiro[i] = (char *)malloc(n * sizeof(char));

    int linha = 0, coluna = 0;

    // Loop principal para posicionar rainhas de forma segura em cada linha do tabuleiro.
    while (!pilha_vazia(P) || linha < n)
    {
        while (coluna < n)
        {
            // Verifica se é seguro colocar a rainha na posição atual
            if (posicao_segura(rainhas, linha, coluna))
            {
                rainhas[linha].linha = linha;
                rainhas[linha].coluna = coluna;

                // Se todas as rainhas foram colocadas, imprime a solução
                if (linha == n - 1)
                    imprimir_solucao(rainhas, n, tabuleiro);
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
        if (pilha_vazia(P))
            break; // Encerra o loop se a pilha está vazia

        linha = desempilhar(P);             // Retorna para a linha anterior
        coluna = rainhas[linha].coluna + 1; // Avança para a próxima coluna da linha anterior
    }

    // Libera a memória alocada para as rainhas e o tabuleiro
    free(rainhas);
    for (int i = 0; i < n; i++)
        free(tabuleiro[i]);
    free(tabuleiro);
    libera_pilha(P); // Libera a pilha após terminar a busca por soluções
}

int main()
{
    int n;
    scanf("%d", &n);

    resolver_n_rainhas(n); // Chama a função para resolver o problema das n rainhas
    return 0;
}
