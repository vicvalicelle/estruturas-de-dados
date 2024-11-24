// Dupla: Lara Fernandes e Victoria Valicelle
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arvore {
  int info;
  struct arvore *esq;
  struct arvore *dir;
} arvore;

arvore* Inserir(arvore* a, int x){
  if (a == NULL){
    a = (arvore*)malloc(sizeof(arvore));
    a->info = x;
    a->esq = NULL;
    a->dir = NULL;
  }
  else if (x <= a->info)
    a->esq = Inserir(a->esq, x);
  else
    a->dir = Inserir(a->dir, x);
  return a;
}

void Remover(arvore **a, int x) {
    if (*a != NULL) {
        if ((*a)->info == x) {
            // Caso 1: Nó folha
            if ((*a)->esq == NULL && (*a)->dir == NULL) {
                free(*a);
                *a = NULL;
            }
            // Caso 2: Apenas um filho (direito)
            else if ((*a)->esq == NULL) {
                arvore *aux = (*a)->dir;
                free(*a);
                *a = aux;
            }
            // Caso 2: Apenas um filho (esquerdo)
            else if ((*a)->dir == NULL) {
                arvore *aux = (*a)->esq;
                free(*a);
                *a = aux;
            }
            // Caso 3: Dois filhos
            else {
                arvore *aux = (*a)->esq;
                // Encontra o maior nó na subárvore esquerda (ou pode usar o menor na direita)
                while (aux->dir != NULL) {
                    aux = aux->dir;
                }
                (*a)->info = aux->info;  // Substitui o valor do nó a ser removido
                Remover(&((*a)->esq), aux->info);  // Remove o nó substituído
            }
        }
        // Percorre recursivamente a subárvore esquerda ou direita
        else if (x < (*a)->info) {
            Remover(&((*a)->esq), x);
        } else {
            Remover(&((*a)->dir), x);
        }
    }
}

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

void liberarArvore(arvore* a) {
  if (a != NULL) {
    liberarArvore(a->esq);
    liberarArvore(a->dir);
    free(a);
  }
}

int Existe(arvore *a, int x) {
  if (a == NULL) {
    return 0;
  }
  else if (x == a->info) {
    return 1;
  }
  else if (x < a->info) {
    return Existe(a->esq, x);
  }
  else{
    return Existe(a->dir, x);
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
    printf("\nnivel %d: ", i - 1);
    Nos(a, i);
    printf("\n");
  }
}

void FolhasMenoresX(arvore *a, int x){
  if (a != NULL){
    if (a->esq == NULL && a->dir == NULL){
      if (a->info < x){
        printf("%d ", a->info);
      }
    }
    else {
      if (a->info < x) {
        FolhasMenoresX(a->dir, x);
      }
      FolhasMenoresX(a->esq, x);
    }
  }
}

int nivelNo(arvore* a, int valor, int nivel) {
  if (a == NULL)
    return -1;
  if (a->info == valor)
    return nivel;
  else if (valor < a->info){
    return nivelNo(a->esq, valor, nivel+1);
  } else {
    return nivelNo(a->dir, valor, nivel+1);
  }
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
    printf("4 - Imprimir o nivel de um no x\n");
    printf("5 - Imprimir os nos folhas menores que um valor x\n");
    printf("6 - Inserir um no x na arvore\n");
    printf("7 - Remover um no x da arvore\n");
    printf("8 - Sair\n");
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
            printf("Impressao em largura:");
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
        if (a == NULL){
          printf("Arvore vazia!\n");
        }
        else{
          system("cls"); // Windows
          int valor;

          printf("Digite o valor do no: ");
          scanf("%d", &valor);

          int nivel = nivelNo(a, valor, 0);

          if (nivel != -1) {
          printf("Nivel do no %d: %d\n", valor, nivel);
          }
          else {
            printf("O no %d nao existe na arvore.\n", valor);
          }
        }
        break;
      }
      case 5: {
        if (a == NULL){
            printf("Arvore vazia!\n");
        }
        else{
            system("cls"); // Windows
            int x;
            printf("Digite um valor: ");
            scanf("%d", &x);
            FolhasMenoresX(a, x);
            printf("\n");
        }
        break;
      }
      case 6: {
        if (a == NULL){
            printf("Arvore vazia!\n");
        }
        else{
            system("cls"); // Windows
            int x;
            printf("Digite um valor para ser inserido: ");
            scanf("%d", &x);
            Inserir(a, x);
        }
        break;
      }
      case 7: {
        if (a == NULL){
            printf("Arvore vazia!\n");
        }
        else{
            system("cls"); // Windows
            int x;
            printf("Digite o valor para ser removido: ");
            scanf("%d", &x);
            Remover(&a, x);
        }
        break;
      }
      case 8: {
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