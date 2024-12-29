
#ifndef Fila_H
#define Fila_H

typedef struct fila *Fila;
int Inserir(Fila f, int x);
int Remover(Fila f, int *x);
void Imprimir(Fila f);
Fila Inicializar();
Fila Destruir(Fila f);

#endif
