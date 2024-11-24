// Dupla: Lara Fernandes e Victoria Valicelle
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arvore {
  int info;
  struct arvore *esq;
  struct arvore *dir;
} arvore;

arvore *LerArvore(FILE *arq) {
  char c;
  int num;

  fscanf(arq, "%c", &c);
  fscanf(arq, "%d", &num);

  if (num == -1) {
    fscanf(arq, "%c", &c);
    return NULL;
  } else {
    arvore *a = (arvore *)malloc(sizeof(arvore));
    a->info = num;
    a->esq = LerArvore(arq);
    a->dir = LerArvore(arq);
    fscanf(arq, "%c", &c);
    return a;
  }
}

void PreOrdem(arvore *a) {
  if (a != NULL) {
    printf("%d ", a->info);
    PreOrdem(a->esq);
    PreOrdem(a->dir);
  }
}

void EmOrdem(arvore *a) {
  if (a != NULL) {
    EmOrdem(a->esq);
    printf("%d ", a->info);
    EmOrdem(a->dir);
  }
}

void PosOrdem(arvore *a) {
  if (a != NULL) {
    PosOrdem(a->esq);
    PosOrdem(a->dir);
    printf("%d ", a->info);
  }
}



int Existe(arvore *a, int x) {
  if (a == NULL) {
    return 0;
  } else if (a->info == x) {
    return 1;
  } else {
    int ret = Existe(a->esq, x);
    if (ret == 1) {
      return 1;
    }
    return Existe(a->dir, x);
  }
}

int ContaElementos(arvore *a) {
  if (a == NULL) {
    return 0;
  } else {
    return 1 + ContaElementos(a->esq) + ContaElementos(a->dir);
  }
}

void ImprimirNosFolhas(arvore *a) {
  if (a != NULL) {
    if (a->esq == NULL && a->dir == NULL) {
      printf("%d ", a->info);
    } else {
      ImprimirNosFolhas(a->esq);
      ImprimirNosFolhas(a->dir);
    }
  }
}

void liberarArvore(arvore* a) {
  if (a != NULL) {
    liberarArvore(a->esq);
    liberarArvore(a->dir);
    free(a);
  }
}

int altura(arvore* a){
  if (a == NULL){
    return 0;
  }
  else{
    int he = altura(a->esq);
    int hd = altura(a->dir);
    if (he > hd){
      return he+1;
    }
    else{
      return hd+1;
    }
  }
}

void Nos(arvore* a, int nivel) {
    if (a == NULL)
        return;
    if (nivel == 1)
        printf("%d ", a->info);
    else if (nivel > 1) {
        Nos(a->esq, nivel - 1);
        Nos(a->dir, nivel - 1);
    }
}

void EmLargura(arvore* a) {
  int h = altura(a);
  for (int i = 1; i <= h; i++) {
    printf("nivel %d: ", i - 1);
    Nos(a, i);
    printf("\n");
  }
}

bool balanceada(arvore *a) {
  if (a == NULL)
    return true;

  int alturaEsquerda = altura(a->esq);
  int alturaDireita = altura(a->dir);
  
  return (abs(alturaEsquerda - alturaDireita) <= 1) && balanceada(a->esq) && balanceada(a->dir);
}

int cheia(arvore* a) {
  if (a == NULL) {
    return 1;
  }
  if (a->esq == NULL && a->dir == NULL) {
    return 1;
  }
  if (a->esq == NULL || a->dir == NULL) {
    return 0;
  }
  return cheia(a->esq) && cheia(a->dir);
}

int nivelNo(arvore* a, int valor, int nivel) {
  if (a == NULL)
    return -1;
  if (a->info == valor)
    return nivel;
  int nivelEsquerdo = nivelNo(a->esq, valor, nivel + 1);
  
  if (nivelEsquerdo != -1)
    return nivelEsquerdo;
  
  return nivelNo(a->dir, valor, nivel + 1);
}

int main(void) {
  int x;
  FILE *arq;
  arvore *a = NULL;

  while (1) {
    system("cls"); // Windows
    printf("Menu:\n");
    printf("1 - Ler uma arvore\n");
    printf("2 - Imprimir a arvore\n");
    printf("3 - Verificar se um elemento x existe na arvore\n");
    printf("4 - Contar os elementos da arvore\n");
    printf("5 - Imprimir os nos folhas da arvore\n");
    printf("6 - Verificar se a arvore esta balanceada\n");
    printf("7 - Verificar se a arvore esta cheia\n");
    printf("8 - Imprimir o nivel de um no x\n");
    printf("9 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &x);

    switch (x) {
      case 1: {
        arq = fopen("arvore.txt", "rt");
        if (arq == NULL) {
          printf("Erro ao abrir o arquivo\n");
        }
        else {
          a = LerArvore(arq);
          fclose(arq);
        }
        break;
      }
      case 2: {
        if (a == NULL) {
          printf("Arvore vazia!\n");
        }
        else {
          system("cls"); // Windows
          int y;
          printf("1 - Pre-ordem\n2 - Em-ordem\n3 - Pos-ordem\n4 - Em largura\nEscolha uma opcao: ");
          scanf("%d", &y);
          if (y == 1) {
            printf("Impressao em pre-ordem: ");
            PreOrdem(a);
            printf("\n");
          }
          else if (y == 2) {
            printf("Impressao em ordem: ");
            EmOrdem(a);
            printf("\n");
          }
          else if (y == 3) {
            printf("Impressao em pos-ordem: ");
            PosOrdem(a);
            printf("\n");
          }
          else if (y == 4) {
            printf("Impressao em largura:\n");
            EmLargura(a);
            printf("\n");
          }
          else {
            printf("Opcao invalida!\n");
          }
        }
        break;
      }
      case 3: {
        if (a == NULL) {
          printf("Arvore vazia!\n");
        }
        else {
          system("cls"); // Windows
          int z;
          printf("Digite um numero para ser buscado: ");
          scanf("%d", &z);
          if (Existe(a, z)) {
            printf("O numero %d existe na arvore!\n", z);
          }
          else {
            printf("O numero %d nao foi encontrado na arvore\n", z);
          }
        }
        break;
      }
      case 4: {
        if (a == NULL) {
          printf("Arvore vazia!\n");
        }
        else {
          int total = ContaElementos(a);
          printf("A arvore possui %d elementos\n", total);
        }
        break;
      }
      case 5: {
        if (a == NULL) {
          printf("Arvore vazia!\n");
        }
        else {
          printf("Nos folhas da arvore: ");
          ImprimirNosFolhas(a);
          printf("\n");
        }
        break;
      }
      case 6: {
        if (balanceada(a)) {
          printf("A arvore esta balanceada.\n");
        }
        else {
          printf("A arvore nao esta balanceada.\n");
        }
        break;
      }
      case 7: {
        if (cheia(a)) {
          printf("A arvore esta cheia.\n");
        }
        else {
          printf("A arvore nao esta cheia.\n");
        }
        break;
      }
      case 8: {
        system("cls"); // Windows
        int valor;

        printf("Digite o valor do no: ");
        scanf("%d", &valor);

        int nivel = nivelNo(a, valor, 1);

        if (nivel != -1) {
        printf("Nivel do no %d: %d\n", valor, nivel);
        }
        else {
          printf("O no %d nao existe na arvore.\n", valor);
        }
        break;
      }
      case 9: {
        liberarArvore(a);
        return 0;
      }
      default:
        printf("Opcao invalida. Tente novamente.\n");
      }

    char continuar;
    printf("Voltar para o menu (m): ");
    scanf(" %c", &continuar);
  }

  return 0;
}