#include <stdio.h>
#include "pilha.h"

int main() {
	int x;
	Pilha a = Inicializar();
	Push(a, 10);
	Push(a, 24);
	Imprimir(a);
	Pop(a, &x);
	printf("\n%d", x);
	a = Destruir(a);
	return 0;
}