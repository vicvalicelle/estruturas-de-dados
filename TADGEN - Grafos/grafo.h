#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo *Grafo;

Grafo Grafo_Inicializar(int n);
void Grafo_Destruir(Grafo g);
void Grafo_InserirAresta(Grafo g, int origem, int destino, void *custo, int tamanho_custo);
void Grafo_RemoverAresta(Grafo g, int origem, int destino);
void *Grafo_BuscarCusto(Grafo g, int origem, int destino);
int Grafo_GrauVertice(Grafo g, int vertice);
void Grafo_Imprimir(Grafo g);

#endif
