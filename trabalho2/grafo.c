#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"
#include <stdlib.h>
#include <string.h>

/** uma aresta de um grafo ou subgrafo */
typedef Agedge_t *aresta;

grafo
le_grafo(void)
{
    return agread(stdin, NULL);
}

void
destroi_grafo(grafo g)
{
    agclose(g);
}

grafo
escreve_grafo(grafo g)
{
    return 0 == agwrite(g, stdout) ? g : NULL;
}

int
n_vertices(grafo g)
{
    return agnnodes(g);
}

int
n_arestas(grafo g)
{
    return agnedges(g);
}

int
grau(vertice v, grafo g)
{
    return agdegree(g, v, TRUE, TRUE);
}

int
grau_maximo(grafo g)
{
    int max = 0, tmp;
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v))
        if (max < (tmp = grau(v, g))) max = tmp;
    return max;
}

int
grau_minimo(grafo g)
{
    vertice v = agfstnode(g);
    int min = grau(v, g), tmp;
    if (v != NULL) {
        for (v = agnxtnode(g, v); v != NULL; v = agnxtnode(g, v))
            if (min > (tmp = grau(v, g))) min = tmp;
    }
    return min;
}

int
grau_medio(grafo g)
{
    int sum = 0, k = 0;
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v)) {
        sum += grau(v, g);
        ++k;
    }
    return k != 0 ? sum / k : 0;
}

int
regular(grafo g)
{
    vertice v = agfstnode(g);
    const int grau_esperado = grau(v, g);
    if (v != NULL) {
        for (v = agnxtnode(g, v); v != NULL; v = agnxtnode(g, v))
            if (grau_esperado != grau(v, g)) return 0;
    }
    return 1;
}

int
completo(grafo g)
{
    /* para ser completo é preciso ser não direcionado e simples */
    if (agisdirected(g) || agissimple(g)) return 0;
    /* cada vértice deverá apontar para todos os outros vértices restantes */
    const int grau_esperado = n_vertices(g) - 1;
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v))
        if (grau_esperado != grau(v, g)) return 0;
    return 1;
}

static int
_conexo(grafo g, vertice v)
{
    static char tag[] = "visitado";
    /* retorna se vértice já foi visitado */
    if (agbindrec(v, tag, 0, TRUE)) return 0;
    /* marca vértice como visitado */
    agbindrec(v, tag, sizeof(char), TRUE);
    /* checa todos os outros vértices possíveis de acessar a partir do atual */
    int n_arestas = 0;
    for (aresta a = agfstedge(g, v); a != NULL; a = agnxtedge(g, a, v))
        n_arestas += _conexo(g, agtail(a)) + _conexo(g, aghead(a));
    return n_arestas + 1;
}

int
conexo(grafo g)
{
    return n_vertices(g) == _conexo(g, agfstnode(g));
}

int
bipartido(grafo g)
{
    // aloca os vetores de vertices vermelho e azul
    vertice *ver = (vertice*)malloc((long unsigned int)n_vertices(g) * sizeof(vertice));
    int tam_ver = 0;
    vertice *azul = (vertice*)malloc((long unsigned int)n_vertices(g) * sizeof(vertice));
    int tam_azul = 0;
    int i = 0; // indice de azul
    int j = 0; // indice de vermelho
    int flag; // variavel de controle
    int resp = 1; // valor a ser retornado, é necessario para poder desalocar
                  // os vertices

    // pega o nodo inicia coloca ele em vermelho e sua fronteira em azul
    vertice v1 = agfstnode(g);
    ver[i] = v1;
    i++;
    tam_ver++;
    for (vertice u1 = agnxtnode(g, v1); u1 != NULL; u1 = agnxtnode(g, u1)) {
        if (NULL != agedge(g, v1, u1, NULL, FALSE)) {
            azul[j] = u1;
            j++;
            tam_azul++;
        }
    }
    int k_azul_antigo = 0;
    int k_ver_antigo = tam_ver;
    int flag_vermelho;
    int flag_azul;

    // enquanto a lista vermelho + lista azul nao pegarem todos os vertices
    while (i + j < n_vertices(g)) {
        flag_vermelho = 0;
        // para cada elemento azul, expanda sua fronteira
        for (int k = k_azul_antigo; k < tam_azul; k++) {
            v1 = azul[k];
            for (vertice u1 = agfstnode(g); u1 != NULL; u1 = agnxtnode(g, u1))
            {
                if (NULL != agedge(g, v1, u1, NULL, FALSE)) {
                    flag = 0;
                    // caso esse elemento ja nao esteja em vermelho coloque ele
                    // em vermelho
                    for (int L = 0; L < tam_ver; L++) {
                        if (u1 == ver[L]) {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) {
                        flag_vermelho = 1;
                        ver[i] = u1;
                        i++;
                        tam_ver++;
                    }
                }
            }
        }
        k_azul_antigo = tam_azul;

        flag_azul = 0;

        // para cada elemento de vermelho, expanda sua fronteira
        for (int k = k_ver_antigo; k < tam_ver; k++) {
            v1 = ver[k];
            for (vertice u1 = agfstnode(g); u1 != NULL; u1 = agnxtnode(g, u1))
            {
                if (NULL != agedge(g, v1, u1, NULL, FALSE)) {
                    flag = 0;
                    // caso esse elemento ja nao esteja em azul coloque ele em
                    // azul
                    for (int L = 0; L < tam_azul; L++) {
                        if (u1 == azul[L]) {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) {
                        flag_azul = 1;
                        azul[j] = u1;
                        j++;
                        tam_azul++;
                    }
                }
            }
        }
        k_ver_antigo = tam_ver;

        // caso G tenha mais de 1 componente e a ultima componente descoberta
        // tenha sido preeenchida totalmente, ache a proxima componente
        if (!flag_azul && !flag_vermelho) {
            for (v1 = agfstnode(g); v1 != NULL; v1 = agnxtnode(g, v1)) {
                flag_azul = 0;
                flag_vermelho = 0;
                for (int L = 0; L < tam_azul; L++) {
                    if (v1 == azul[L]) {
                        flag_azul = 1;
                        break;
                    }
                }
                if (flag_azul == 0) {
                    for (int L = 0; L < tam_ver; L++) {
                        if (v1 == ver[L]) {
                            flag_vermelho = 1;
                            break;
                        }
                    }
                }
                if (!flag_vermelho && !flag_azul) {
                    ver[i] = v1;
                    i++;
                    tam_ver++;
                    break;
                }
            }
        }
    }
    // verifica se todos os nodos de vermelho nao sao vizinhos
    for (i = 0; i < tam_ver; i++) {
        for (j = i; j < tam_ver; j++) {
            if (NULL != agedge(g, ver[i], ver[j], NULL, FALSE)) resp = 0;
        }
    }
    // verifica se todos os nodos de azul nao sao vizinhos
    for (i = 0; i < tam_azul; i++) {
        for (j = i; j < tam_azul; j++) {
            if (NULL != agedge(g, azul[i], azul[j], NULL, FALSE)) resp = 0;
        }
    }
    free(ver);
    free(azul);
    return resp;
}

int
n_triangulos(grafo g)
{
    int triangulo = 0;
    // pegue um vertice
    for (vertice v1 = agfstnode(g); v1 != NULL; v1 = agnxtnode(g, v1)) {
        // pegeu outro vertice diferente do primeiro
        for (vertice u1 = agnxtnode(g, v1); u1 != NULL; u1 = agnxtnode(g, u1))
        {
            // se houver uma aresta entre os 2 primeiros vertices pegue um
            // terceito vertice
            if (NULL != agedge(g, v1, u1, NULL, FALSE)) {
                for (vertice k1 = agnxtnode(g, u1); k1 != NULL;
                     k1 = agnxtnode(g, k1)) {
                    // verifica se o terceti overtice tem aresta entre os
                    // outros 2
                    if (NULL != agedge(g, u1, k1, NULL, FALSE)
                        && NULL != agedge(g, k1, v1, NULL, FALSE))
                        // caso tenha aresta entao esses 3 vertices formam um
                        // triangulo
                        triangulo++;
                }
            }
        }
    }
    return triangulo;
}

int **
matriz_adjacencia(grafo g)
{
    // descobre o numero de vertices para aloxar a matriz
    const int tam = n_vertices(g);
    // aloca a matriz
    int **matriz = (int**)malloc((long unsigned int)tam * sizeof(int *));
    for (int i = 0; i < tam; i++)
        matriz[i] = (int*)calloc((size_t)tam, sizeof(int));

    // i,j indices da matriz
    // A matriz é percorrida de forma triangular, entao seu custo real é
    // dividido por 2
    int i = 0;
    // pega os 2 vertices
    for (vertice v1 = agfstnode(g); v1 != NULL; v1 = agnxtnode(g, v1)) {
        int j = i + 1;
        for (vertice u1 = agnxtnode(g, v1); u1 != NULL; u1 = agnxtnode(g, u1))
        {
            // se houver aresta entre esses 2 vertices coloca o valor 1 na
            // matriz, 0 caso contrario
            if (agedge(g, v1, u1, NULL, FALSE) != NULL) {
                aresta e = agedge(g, v1, u1, NULL, FALSE);
                vertice vaux = aghead(e);
                if (v1 == vaux) {
                    matriz[i][j] = 1;
                    matriz[j][i] = -1;
                }
                else {
                    matriz[i][j] = -1;
                    matriz[j][i] = 1;
                }
            }
            else
                matriz[i][j] = matriz[j][i] = 0;
            j++;
        }
        i++;
    }
    return matriz;
}

grafo
complemento(grafo g)
{
    // cria o nome da matriz como "complementar de <nome de g>"
    char nome[256];
    snprintf(nome, sizeof(nome), "complementar de %s", agnameof(g));
    // aloca o grafo , que herda as configuracoes do grafo g (g->desc)
    grafo aux = agopen(nome, g->desc, NULL);
    // preenche os vertices
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v))
        agnode(aux, agnameof(v), TRUE);
    // preenche as arestas
    vertice v2 = agfstnode(aux);
    for (vertice v1 = agfstnode(g); v1 != NULL; v1 = agnxtnode(g, v1)) {
        vertice u2 = agnxtnode(aux, v2);
        for (vertice u1 = agnxtnode(g, v1); u1 != NULL; u1 = agnxtnode(g, u1))
        {
            // se nao houver aresta entre 2 vertices gera uma nova aresta
            if (NULL == agedge(g, v1, u1, NULL, FALSE))
                agedge(aux, v2, u2, NULL, TRUE);
            u2 = agnxtnode(aux, u2);
        }
        v2 = agnxtnode(aux, v2);
    }
    return aux;
}

static grafo
grafo_reverso(grafo g)
{
    // cria o nome da matriz como "complementar de <nome de g>"
    char nome[256];
    snprintf(nome, sizeof(nome), "reverso de %s", agnameof(g));
    // aloca o grafo , que herda as configuracoes do grafo g (g->desc)
    grafo aux = agopen(nome, g->desc, NULL);
    // preenche os vertices
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v))
        agnode(aux, agnameof(v), TRUE);
    // preenche as arestas
    vertice v2 = agfstnode(aux);
    for (vertice v1 = agfstnode(g); v1 != NULL; v1 = agnxtnode(g, v1)) {
        vertice u2 = agfstnode(aux);
        for (vertice u1 = agfstnode(g); u1 != NULL; u1 = agnxtnode(g, u1)) {
            // se nao houver aresta entre 2 vertices gera uma nova aresta
            if (NULL != agedge(g, v1, u1, NULL, FALSE)) {
                aresta e = agedge(g, v1, u1, NULL, FALSE);
                vertice vaux = aghead(e);
                if (v1 == vaux) {
                    agedge(aux, v2, u2, NULL, TRUE);
                }
                else {
                    agedge(aux, u2, v2, NULL, TRUE);
                }
            }
            u2 = agnxtnode(aux, u2);
        }
        v2 = agnxtnode(aux, v2);
    }
    return aux;
}

struct grafo_ctx {
    Agrec_t header;
    const char pad[4]; // desabilita -Wpad warning
    int componentes;
};
static char grafo_ctx_tag[] = "componentes";

struct vertice_ctx {
    Agrec_t header;
    int estado;
    int componente;
};
static char vertice_ctx_tag[] = "contexto";

static void
dfsR(grafo g, vertice v, vertice *vv, int *cnt)
{
    struct vertice_ctx *r_ctx = (struct vertice_ctx*)agbindrec(v, vertice_ctx_tag, 0, FALSE);

    r_ctx->estado = 0;
    for (aresta a = agfstedge(g, v); a != NULL; a = agnxtedge(g, a, v)) {
        // vizinho
        if (aghead(a) == v) {
            const vertice r = agtail(a);
            struct vertice_ctx *v_ctx =
                (struct vertice_ctx*)agbindrec(r, vertice_ctx_tag, 0, FALSE);
            if (v_ctx->estado == -1) dfsR(g, r, vv, cnt);
        }
    }
    vv[*cnt] = v;
    ++*cnt;

    return;
}

static vertice *
rev_posordem(grafo G)
{
    vertice *vv = (vertice*)malloc((long unsigned int)n_vertices(G) * sizeof(vertice));
    grafo reverso = grafo_reverso(G);
    struct vertice_ctx *v_ctx;
    vertice v;
    int cnt = 0;

    for (v = agfstnode(reverso); v != NULL; v = agnxtnode(reverso, v)) {
        v_ctx =
            (struct vertice_ctx*)agbindrec(v, vertice_ctx_tag, sizeof(struct vertice_ctx), FALSE);
        v_ctx->estado = -1;
        v_ctx->componente = 0;
    }
    for (v = agfstnode(reverso); v != NULL; v = agnxtnode(reverso, v)) {
        v_ctx = (struct vertice_ctx*)agbindrec(v, vertice_ctx_tag, 0, FALSE);
        if (v_ctx->estado == -1) dfsR(reverso, v, vv, &cnt);
    }
    for (int i = 0; i < cnt; i++) {
        for (vertice v1 = agfstnode(G); v1 != NULL; v1 = agnxtnode(G, v1)) {
            if (!strcmp(agnameof(vv[i]), agnameof(v1))) {
                vv[i] = v1;
                break;
            }
        }
    }
    destroi_grafo(reverso);

    return vv;
}

static void
_decompoe(grafo g, vertice r)
{
    struct vertice_ctx *r_ctx = (struct vertice_ctx*)agbindrec(r, vertice_ctx_tag, 0, FALSE);
    struct grafo_ctx *g_ctx = (struct grafo_ctx*)agbindrec(g, grafo_ctx_tag, 0, FALSE);

    r_ctx->estado = 1;
    for (aresta a = agfstedge(g, r); a != NULL; a = agnxtedge(g, a, r)) {
        // vizinho
        if (agtail(a) == r) {
            const vertice v = aghead(a);
            struct vertice_ctx *v_ctx =
                (struct vertice_ctx*)agbindrec(v, vertice_ctx_tag, 0, FALSE);
            if (v_ctx->estado == 0) _decompoe(g, v);
        }
    }
    r_ctx->componente = g_ctx->componentes;
    r_ctx->estado = 2;
}

grafo
decompoe(grafo g)
{
    struct vertice_ctx *v_ctx;
    struct grafo_ctx *g_ctx;
    vertice *L;
    vertice v;

    if (!agisdirected(g)) return 0; // precisamos que seja um grafo direcionado

    for (v = agfstnode(g); v != NULL; v = agnxtnode(g, v)) {
        v_ctx =
            (struct vertice_ctx*)agbindrec(v, vertice_ctx_tag, sizeof(struct vertice_ctx), FALSE);
        v_ctx->estado = 0;
        v_ctx->componente = 0;
    }

    g_ctx = (struct grafo_ctx*)agbindrec(g, grafo_ctx_tag, sizeof(struct grafo_ctx), TRUE);
    g_ctx->componentes = 0;

    L = rev_posordem(g);
    for (int i = 0, n = n_vertices(g); i < n; ++i) {
        v = L[i];
        v_ctx = (struct vertice_ctx*)agbindrec(v, vertice_ctx_tag, 0, FALSE);
        if (v_ctx->estado == 0) {
            ++g_ctx->componentes;
            _decompoe(g, v);
        }
    }


    printf("\nNº de componentes: %i\n", g_ctx->componentes);

    grafo * h = (grafo*)calloc((long unsigned int)g_ctx->componentes, sizeof(grafo));

    for (int i = 0; i < g_ctx->componentes; i++){
        h[i] = agsubg(g,NULL,TRUE);
    }

    for (vertice n = agfstnode(g); n != NULL; n = agnxtnode(g,n)){
        for (vertice s = agfstnode(g); s != NULL; s = agnxtnode(g,s)){
            
            struct vertice_ctx *s_ctx =
                    (struct vertice_ctx*)agbindrec(s, vertice_ctx_tag, 0, FALSE);    
            struct vertice_ctx *n_ctx =
                    (struct vertice_ctx*)agbindrec(n, vertice_ctx_tag, 0, FALSE);
            agsubnode(h[s_ctx->componente-1],s,TRUE);
            if(n_ctx->componente == s_ctx->componente){
                if(NULL != agedge(g,s,n,NULL,FALSE)){
                    aresta e = agedge(g,s,n,NULL,FALSE);
                    if (aghead(e) == n){
                        printf("\nNº do componentes: %i || %i \n", n_ctx->componente,g_ctx->componentes);        
                        agsubedge(h[n_ctx->componente-1],agedge(g,s,n,NULL,FALSE),TRUE);
                    }
                    else{
                        printf("\nNº do componentes: %i || %i \n", n_ctx->componente,g_ctx->componentes);        
                        agsubedge(h[n_ctx->componente-1],agedge(g,n,s,NULL,FALSE),TRUE);
                    }
                }
            }            
        }
    }
    for (int i = 0; i < g_ctx->componentes; i++){
        printf("Componente %i: \n", i);
        escreve_grafo(h[i]);       
    }
    printf("\nNº de componentes: %i\n", g_ctx->componentes);
    free(L);

    return g;
}
