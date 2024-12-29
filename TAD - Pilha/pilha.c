/*Implementação usando vetor*/

#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

#define N 100

struct pilha {
	int vet[N];
	int topo;
};

Pilha Inicializar() {
	Pilha p = (Pilha)malloc(sizeof(struct pilha));
	p->topo = 0;
	return p;
}

Pilha Destruir(Pilha p) {
	free(p);
	return NULL;
}

int cheia(Pilha p) {
	if (p->topo == N)
		return 1;
	else
		return 0;
}

int Push(Pilha p, int x) {
	if (cheia(p))
		return 0;
	p->vet[p->topo] = x;
	p->topo++;
	return 1;
}

int vazia(Pilha p) {
	if (p->topo == 0)
		return 1;
	else
		return 0;
}

int Pop(Pilha p, int *x) {
	if (vazia(p))
		return 0;
	p->topo--;
	*x = p->vet[p->topo];
	return 1;
}

void Imprimir(Pilha p)
{
	int i;
	printf("\nElementos: ");
	for (i = 0; i < p->topo; i++)
		printf("%d ", p->vet[i]);
}



