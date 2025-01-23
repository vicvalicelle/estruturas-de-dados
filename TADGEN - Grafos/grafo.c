#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista {
    int destino;
    void *custo;
    struct lista *prox;
} Lista;

struct grafo {
    int num_vertices;
    Lista **adj;
};

Grafo Grafo_Inicializar(int n) {
    Grafo g = (Grafo)malloc(sizeof(struct grafo));
    g->num_vertices = n;
    g->adj = (Lista **)malloc((n + 1) * sizeof(Lista *));
    for (int i = 0; i <= n; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void LiberarLista(Lista *l) {
    while (l != NULL) {
        Lista *aux = l;
        l = l->prox;
        free(aux->custo); // Libera o custo genérico
        free(aux);
    }
}

void Grafo_Destruir(Grafo g) {
    for (int i = 0; i <= g->num_vertices; i++) {
        LiberarLista(g->adj[i]);
    }
    free(g->adj);
    free(g);
}

Lista *InserirNaLista(Lista *l, int destino, void *custo, int tamanho_custo) {
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->destino = destino;
    novo->custo = malloc(tamanho_custo);
    memcpy(novo->custo, custo, tamanho_custo);
    novo->prox = l;
    return novo;
}

void Grafo_InserirAresta(Grafo g, int origem, int destino, void *custo, int tamanho_custo) {
    g->adj[origem] = InserirNaLista(g->adj[origem], destino, custo, tamanho_custo);
}

Lista *RemoverNaLista(Lista *l, int destino) {
    Lista *atual = l, *anterior = NULL;

    while (atual != NULL && atual->destino != destino) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            l = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual->custo);
        free(atual);
    }

    return l;
}

void Grafo_RemoverAresta(Grafo g, int origem, int destino) {
    g->adj[origem] = RemoverNaLista(g->adj[origem], destino);
}

void *Grafo_BuscarCusto(Grafo g, int origem, int destino) {
    Lista *atual = g->adj[origem];
    while (atual != NULL) {
        if (atual->destino == destino) {
            return atual->custo;
        }
        atual = atual->prox;
    }
    return NULL;
}

int Grafo_GrauVertice(Grafo g, int vertice) {
    int grau = 0;
    Lista *atual = g->adj[vertice];
    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }
    return grau;
}

void ImprimirLista(Lista *l) {
    while (l != NULL) {
        printf(" -> %d", l->destino);
        l = l->prox;
    }
}

void Grafo_Imprimir(Grafo g) {
    printf("Grafo: ");
    for (int i = 0; i <= g->num_vertices; i++) {
        printf("\n\t%d", i);
        ImprimirLista(g->adj[i]);
    }
}
