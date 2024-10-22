#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um pixel, com componentes R, G e B
typedef struct pixel pixel;
struct pixel
{
    int R; // Componente Vermelha (Red)
    int G; // Componente Verde (Green)
    int B; // Componente Azul (Blue)
};

int main()
{
    // Declaração de ponteiros para armazenar as imagens e os filtros
    pixel **imagem;            // ponteiro para armazenar a imagem original
    pixel **filtro;            // ponteiro para armazenar o filtro
    pixel **imagem_com_filtro; // ponteiro para armazenar o resultado da aplicação do filtro
    int lin, col;              // Variáveis para armazenar o número de linhas e colunas
    int i, j, k;               // Variáveis de controle para os loops

    // Leitura do número de linhas e colunas da imagem
    scanf("%d %d", &lin, &col);

    // Alocação de memória para as matrizes de pixels (imagem, filtro e imagem filtrada)
    imagem = (pixel **)malloc(lin * sizeof(pixel *));
    filtro = (pixel **)malloc(lin * sizeof(pixel *));
    imagem_com_filtro = (pixel **)malloc(lin * sizeof(pixel *));

    // Alocação de memória para cada elemento da imagem, filtro e imagem com filtro
    for (i = 0; i < col; i++)
    {
        imagem[i] = (pixel *)malloc(col * sizeof(pixel));            // Alocando memória para a imagem
        filtro[i] = (pixel *)malloc(col * sizeof(pixel));            // Alocando memória para o filtro
        imagem_com_filtro[i] = (pixel *)malloc(col * sizeof(pixel)); // Alocando memória para a imagem filtrada
    }

    // Leitura dos valores dos pixels da imagem
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            scanf("%d %d %d", &imagem[i][j].R, &imagem[i][j].G, &imagem[i][j].B); // Leitura dos componentes RGB da imagem
        }
    }

    // Leitura dos valores dos pixels do filtro
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            scanf("%d %d %d", &filtro[i][j].R, &filtro[i][j].G, &filtro[i][j].B); // Leitura dos componentes RGB do filtro
        }
    }

    // Nesta parte será realizada o filtro da imagem.
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            // Inicialização dos valores de cada componente RGB para a imagem filtrada
            imagem_com_filtro[i][j].R = 0;
            imagem_com_filtro[i][j].G = 0;
            imagem_com_filtro[i][j].B = 0;

            // Aplicação do filtro multiplicando a imagem pelos valores do filtro
            for (k = 0; k < col; k++)
            {
                imagem_com_filtro[i][j].R += imagem[i][k].R * filtro[k][j].R; // Multiplicação das componentes vermelhas
                imagem_com_filtro[i][j].G += imagem[i][k].G * filtro[k][j].G; // Multiplicação das componentes verdes
                imagem_com_filtro[i][j].B += imagem[i][k].B * filtro[k][j].B; // Multiplicação das componentes azuis
            }
        }
    }

    // Impressão dos valores da imagem resultante após a aplicação do filtro
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            // Impressão das componentes RGB da imagem filtrada
            printf("%d %d %d ", imagem_com_filtro[i][j].R, imagem_com_filtro[i][j].G, imagem_com_filtro[i][j].B);
        }
        printf("\n");
    }

    // Liberação da memória alocada para elementos das matrizes
    for (i = 0; i < lin; i++)
    {
        free(imagem[i]);            // Libera a memória alocada para cada linha da imagem
        free(filtro[i]);            // Libera a memória alocada para cada linha do filtro
        free(imagem_com_filtro[i]); // Libera a memória alocada para cada linha da imagem filtrada
    }

    // Liberação da memória alocada para os ponteiros principais
    free(imagem);
    free(imagem_com_filtro);
    free(filtro);

    return 0;
}
