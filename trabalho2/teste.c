#include <stdio.h>
#include "grafo.h"
#include <stdlib.h>

/**
 * @brief imprime na saida padrao uma matriz
 *
 * @param g grafo `g`
 *        tam numero de vertices de `g`   
 */
void imprime_matriz(int **matriz, int tam);

void
imprime_matriz(int **matriz, int tam)
{
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++)
            printf("%i ", matriz[i][j]);
        printf("\n");
    }
    printf("\n");
}

/**
 * @brief libera memoria de uma matriz
 *
 * @param g grafo `g`
 *        tam numero de vertices de `g`   
 */

void libera_matriz(int **matriz, int tam);

void
libera_matriz(int **matriz, int tam)
{
    for (int i = 0; i < tam; i++)
        free(matriz[i]);
    free(matriz);
    return;
}

int
main(void)
{
    grafo g = le_grafo();

    printf(" numero de vertices do grafo: %i \n", n_vertices(g));
    printf(" numero de arestas do grafo: %i \n", n_arestas(g));
    printf(" grau maximo: %i | grau mínimo: %i | grau médio: %i \n",
           grau_maximo(g), grau_minimo(g), grau_medio(g));
    printf(" numero de triangulos do grafo: %i \n", n_triangulos(g));
    printf(" regular: %i | completo: %i | conexo: %i | bipartido: %i \n",
           regular(g), completo(g), conexo(g), bipartido(g));

    escreve_grafo(g);
    // destroi_grafo(g);

    grafo comp = complemento(g);
    printf(" numero de vertices do grafo: %i \n", n_vertices(comp));
    printf(" numero de arestas do grafo: %i \n", n_arestas(comp));
    printf(" grau maximo: %i | grau mínimo: %i | grau médio: %i \n",
           grau_maximo(comp), grau_minimo(comp), grau_medio(comp));
    printf(" numero de triangulos do grafo: %i \n", n_triangulos(comp));
    printf(" regular: %i | completo: %i  | conexo: %i | bipartido: %i \n",
           regular(comp), completo(comp), conexo(comp), bipartido(comp));

    int **matriz = matriz_adjacencia(g);
    imprime_matriz(matriz, n_vertices(g));
    escreve_grafo(comp);
    libera_matriz(matriz, n_vertices(g));

    decompoe(g);
    destroi_grafo(comp);
    destroi_grafo(g);

    return 0;
}
