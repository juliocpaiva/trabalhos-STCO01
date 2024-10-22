#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um pixel, com componentes R, G e B
typedef struct pixel
{
    int R;
    int G;
    int B;
} pixel;

// Função para alocar memória para a matriz de pixels
pixel **alocar_matriz(int lin, int col)
{
    pixel **matriz = (pixel **)malloc(lin * sizeof(pixel *));
    if (!matriz)
    {
        printf("Erro ao alocar memória para matriz de pixels.\n");
        exit(1);
    }

    for (int i = 0; i < lin; i++)
    {
        matriz[i] = (pixel *)malloc(col * sizeof(pixel));
        if (!matriz[i])
        {
            printf("Erro ao alocar memória para linha da matriz de pixels.\n");
            exit(1);
        }
    }

    return matriz;
}

// Função recursiva para liberar memória de uma matriz de pixels
void liberar_matriz_recursivo(pixel **matriz, int lin, int index)
{
    // Caso base: quando o índice é igual ao número de linhas
    if (index == lin)
    {
        free(matriz); // Libera o ponteiro principal após liberar todas as linhas
        return;
    }

    // Libera a linha atual
    free(matriz[index]);

    // Chama recursivamente para a próxima linha
    liberar_matriz_recursivo(matriz, lin, index + 1);
}

// Função para ler os pixels da imagem ou filtro (recursivo)
void ler_pixels_recursivo(pixel **matriz, int lin, int col, int i, int j)
{
    // Caso base: se lemos todas as linhas
    if (i == lin)
        return;

    // Leitura do pixel na posição atual
    scanf("%d %d %d", &matriz[i][j].R, &matriz[i][j].G, &matriz[i][j].B);

    // Próximo pixel na mesma linha
    if (j + 1 < col)
        ler_pixels_recursivo(matriz, lin, col, i, j + 1);
    else
        ler_pixels_recursivo(matriz, lin, col, i + 1, 0); // Passa para a próxima linha
}

// Função para aplicar o filtro na imagem
void aplicar_filtro(pixel **imagem, pixel **filtro, pixel **imagem_com_filtro, int lin, int col)
{
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            imagem_com_filtro[i][j].R = 0;
            imagem_com_filtro[i][j].G = 0;
            imagem_com_filtro[i][j].B = 0;

            for (int k = 0; k < col; k++)
            {
                imagem_com_filtro[i][j].R += imagem[i][k].R * filtro[k][j].R;
                imagem_com_filtro[i][j].G += imagem[i][k].G * filtro[k][j].G;
                imagem_com_filtro[i][j].B += imagem[i][k].B * filtro[k][j].B;
            }
        }
    }
}

// Função para imprimir a matriz de pixels
void imprimir_pixels(pixel **matriz, int lin, int col)
{
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d %d %d ", matriz[i][j].R, matriz[i][j].G, matriz[i][j].B);
        }
        printf("\n");
    }
}

int main()
{
    int lin, col;

    scanf("%d %d", &lin, &col);

    // Alocação de memória para as matrizes de imagem, filtro e imagem com filtro
    pixel **imagem = alocar_matriz(lin, col);
    pixel **filtro = alocar_matriz(lin, col);
    pixel **imagem_com_filtro = alocar_matriz(lin, col);

    // Leitura dos pixels da imagem e do filtro
    ler_pixels_recursivo(imagem, lin, col, 0, 0);
    ler_pixels_recursivo(filtro, lin, col, 0, 0);

    // Aplicação do filtro
    aplicar_filtro(imagem, filtro, imagem_com_filtro, lin, col);

    printf("\n");
    // Impressão da imagem filtrada
    imprimir_pixels(imagem_com_filtro, lin, col);

    // Liberação de memória alocada de forma recursiva
    liberar_matriz_recursivo(imagem, lin, 0);
    liberar_matriz_recursivo(filtro, lin, 0);
    liberar_matriz_recursivo(imagem_com_filtro, lin, 0);

    return 0;
}
