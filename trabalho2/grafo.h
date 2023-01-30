#ifndef _GRAFO_H
#define _GRAFO_H

#include <graphviz/cgraph.h>

/** um grafo ou subgrafo */
typedef Agraph_t *grafo;
/** um vértice de algum grafo ou subgrafo */
typedef Agnode_t *vertice;

/**
 * @brief Devolve o grafo lido da entrada padrão (formato dot)
 *
 * @return grafo lido do `stdin`
 */
grafo le_grafo(void);

/**
 * @brief Desaloca `g`
 *
 * @param g grafo a ser desalocado
 */
void destroi_grafo(grafo g);

/**
 * @brief Escreve `g` na saída padrão em format dot
 *
 * @param g grafo a ser escrito em stdout
 * @return grafo `g`, ou `NULL`se não foi possível escrever grafo
 */
grafo escreve_grafo(grafo g);

/**
 * @brief Devolve o número de vértices de `g`
 *
 * @param g grafo `g`
 * @return número de vértices de `g`
 */
int n_vertices(grafo g);

/**
 * @brief Devolve o número de arestas do grafo
 *
 * @param g grafo `g`
 * @return número de arestas de `g`
 */
int n_arestas(grafo g);

/**
 * @brief Devolve o grau do vértice `v` em `g`
 *
 * @param v vértice `v`
 * @param g grafo `g`
 * @return grau do vértice
 */
int grau(vertice v, grafo g);

/**
 * @brief Devolve o grau máximo de `g`
 *
 * @param g grafo `g`
 * @return grau máximo do grafo
 */
int grau_maximo(grafo g);

/**
 * @brief Devolve o grau mínimo de `g`
 *
 * @param g grafo `g`
 * @return grau mínimo do grafo
 */
int grau_minimo(grafo g);

/**
 * @brief Devolve o grau médio de `g`
 *
 * @param g grafo `g`
 * @return grau médio do grafo
 */
int grau_medio(grafo g);

/**
 * @brief Devolve 1 se `g` é regular, ou 0 caso contrário
 *
 * @param g grafo `g`
 * @return boolean
 */
int regular(grafo g);

/**
 * @brief Devolve 1 se `g` é complexo, ou 0 caso contrário
 *
 * @param g grafo `g`
 * @return boolean
 */
int completo(grafo g);

/**
 * @brief Devolve 1 se `g` é conexo, ou 0 caso contrário
 *
 * @param g grafo `g`
 * @return boolean
 */
int conexo(grafo g);

/**
 * @brief Devolve 1 se `g` é bipartido, ou 0 caso contrário
 *
 * @param g grafo `g`
 * @return boolean
 */
int bipartido(grafo g);

/**
 * @brief Devolve o número de triângulos (subgrafos completos de 3 vértices) em
 *      `g`
 *
 * @param g grafo `g`
 * @return número de triãngulos em `g`
 */
int n_triangulos(grafo g);

/**
 * @brief retorna matriz de adjacência de `g`
 *
 * @param g grafo `g`
 * @return uma matriz de adjacência de `g` onde as linhas/colunas
 *      estão ordenadas do mesmo modo que agfstnode() e agnxtnode() em
 *      libcgraph
 */
int **matriz_adjacencia(grafo g);

/**
 * @brief Devolve o grafo complementar a `g`
 *
 * @param g grafo `g`
 * @return grafo complementar a `g`
 */
grafo complemento(grafo g);

//------------------------------------------------------------------------------
// acrescenta à lista de subgrafos de g cada um de seus componentes fortes
// vide agsubg(), agfstsubg(), agnxtsubg()
//
// não faz nada se g não for grafo direcionado
//
// devolve g

grafo decompoe(grafo g);


#endif
