/*Implementação usando vetor*/

#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

#define N 100

struct fila{
   int vet[N];  // Vetor para armazenar os elementos da fila
   int elementos;               // Número de elementos inseridos
   int inicio;           // Primeiro elemento da fila
   int fim;             // Final da fila (próxima posição disponível)
};

// Inicializar uma fila vazia.
Fila Inicializar(){
    Fila f = (Fila)malloc(sizeof(struct fila));
    f->elementos = 0;
    f->inicio = 0;
    f->fim = 0;
	return f;
}

Fila Destruir(Fila f) {
	free(f);
	return NULL;
}

int cheia(Fila f) {
	if (f->elementos == N)
		return 1;
	else
		return 0;
}

int vazia(Fila f) {
	if (f->elementos == 0)
		return 1;
	else
		return 0;
}

// Adicionar o elemento x à fila.
int Inserir(Fila f, int x){
   // Certifica-se de que há espaço disponível.
   if (cheia(f))
        return 0;

   // Coloca o elemento no final da fila.
   f->vet[f->fim] = x;

   // Incrementa a quantidade de elementos inseridos na fila.
   f->elementos++;

   // Atualiza o fim da fila.
   f->fim = (f->fim+1)%N;
   return 1;
}

// Remover um elemento da fila.
int Remover(Fila f, int *x){
   // Certifica-se de que a fila não está vazia.
   if (vazia(f))
		return 0;

   // Valor no início da fila.
   *x = f->vet[f->inicio];

   // Decrementa a quantidade de elementos inseridos na fila.
   f->elementos--;

   // Atualiza a posição do primeiro elemento da fila.
   f->inicio = (f->inicio+1)%N;
   return 1;
}

void Imprimir(Fila f){
	int i;
	printf("\nElementos: ");
	for (i = 0; i < f->elementos; i++)
		printf("%d ", f->vet[(f->inicio + i) % N]);
}