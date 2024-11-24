//Dupla: Lara Fernandes e Victoria Valicelle
#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
  int info;
  struct lista *prox;
} lista;

lista* cria_no(int valor) {
  lista* novo = (lista*)malloc(sizeof(lista));
  novo->info = valor;
  novo->prox = NULL;
  return novo;
}

lista* insere(lista* l, int valor) {
  lista* novo = cria_no(valor);
  novo->prox = l;
  return novo;
}

void imprime(lista* l) {
  lista* p = l;
  while (p != NULL) {
    printf("%d ", p->info);
    p = p->prox;
  }
  printf("\n");
}

int somar(lista* l){
  if (l == NULL){
    return 0;
  } else{
    return l->info + somar(l->prox);
  }
}

int conta_elemento(lista* l, int x){
  if (l == NULL){
    return 0;
  } else{
    if (l->info == x){
      return 1 + conta_elemento(l->prox, x);
    } else{
      return conta_elemento(l->prox, x);
    }
  }
}

lista * remove_elemento(lista* l, int x){
  if (l == NULL){
    return NULL;
  }
  if (l->info == x){
    lista* aux = l->prox;
    free(l);
    return aux;
  }
  l->prox = remove_elemento(l->prox, x);
  return l;
}

int main(void) {
  lista* l = NULL;

  l = insere(l, 10);
  l = insere(l, 1);
  l = insere(l, 1);
  l = insere(l, 1);
  l = insere(l, 5);

  int continuar = 1;
  while(continuar){
    imprime(l);

    printf("Digite 1 para somar os elementos da lista\nDigite 2 para contar um elemento\nDigite 3 para remover um elemento\nDigite 4 para sair\n");
    int op;
    scanf("%d", &op);

    if (op == 1){
      int soma = somar(l);
      printf("Soma: %d\n", soma);
    } else if (op == 2){
      int x;
      printf("Digite um número para ser buscado na lista");
      scanf("%d", &x);
      int contagem = conta_elemento(l, x);
      printf("Ocorrência de %d: %d\n", x, contagem);
    } else if(op == 3){
      int y;
      printf("Digite um número para ser removido da lista: ");
      scanf("%d", &y);
      l = remove_elemento(l, y);
      printf("Lista após a remoção");
    } else{
      printf("Opção inválida");
    }

    printf("Deseja fazer outra operação? (1 para sim, 0 para não)\n ");
    scanf("%d", &continuar);
  }
  return 0;
}
