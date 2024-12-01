//Lara Fernandes e Victoria Valicelle
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N = 0;

typedef struct aluno{
    int matricula;
    char nome[60]; 
    char curso[30]; 
    int disponibilidade;
} aluno;

int hash(int m){
    return m % N;
}

void inicializar (char *nomeArq){
    FILE *arq = fopen(nomeArq, "wb");
    aluno a;
    a.disponibilidade = 1;
    for(int i = 0; i < N; i++){ 
        fwrite(&a, sizeof(aluno), 1, arq);
    }
    fclose(arq);
}

int AcharPosicao (char *nomeArq, int m){
    int pos = hash(m);
    aluno a;
    FILE *arq = fopen(nomeArq, "rb");
    fseek (arq, pos*sizeof(aluno), SEEK_SET);
    fread (&a, sizeof(aluno), 1, arq);
    while(a.disponibilidade == 0 && a.matricula != m){
        pos = (pos+1)%N;
        fseek (arq, pos*sizeof(aluno), SEEK_SET);
        fread (&a, sizeof(aluno), 1, arq);
    }
    fclose(arq);
    return pos;
}

void inserir (char *nomeArq, aluno a){
    FILE *arq = fopen(nomeArq, "r+b");
    printf("Digite a matricula do aluno: \n");
    scanf("%d", &a.matricula);
    getchar();
    printf("Digite o nome do aluno: \n");
    fgets(a.nome, sizeof(a.nome), stdin);
    a.nome[strcspn(a.nome, "\n")] = 0;
    printf("Digite o curso: \n");
    fgets(a.curso, sizeof(a.curso), stdin);
    a.curso[strcspn(a.curso, "\n")] = 0;
    int pos = AcharPosicao(nomeArq, a.matricula);
    a.disponibilidade = 0;
    fseek(arq, pos*sizeof(aluno), SEEK_SET);
    fwrite(&a, sizeof(aluno), 1, arq);
    fclose(arq);
}

void ImprimirAluno (char *nomeArq, int m){
    FILE *arq = fopen(nomeArq, "rb");
    aluno a;
    int pos = AcharPosicao(nomeArq, m);
    fseek(arq, pos*sizeof(aluno), SEEK_SET);
    fread(&a, sizeof(aluno), 1, arq);
    if(a.disponibilidade == 0 && a.matricula == m){
        printf("Matricula: %d\n", a.matricula);
        printf("Nome: %s\n", a.nome);
        printf("Curso: %s\n", a.curso);
    }
    else {
    printf("Aluno nao encontrado.\n");
    }
    fclose(arq);
}

void ImprimirTabela(char *nomeArq) {
  FILE *arq = fopen(nomeArq, "rb");
  aluno a;
  printf("Tabela hash:\n");
  for(int i = 0; i < N; i++) {
    fseek(arq, i*sizeof(aluno), SEEK_SET);
    fread(&a, sizeof(aluno), 1, arq);
    printf("Posicao %d:", i);
    if(a.disponibilidade == 0) {
      printf(" Matricula: %d, Nome: %s, Curso: %s\n", a.matricula, a.nome, a.curso);
    } else {
      printf(" Vazio\n");
    }
  }
  fclose(arq);
}

int main(void){
    int x;
    aluno a;
    char nomeArq[50];

    printf("Digite o tamanho da tabela: \n");
    scanf("%d", &N);

    printf("Digite o nome do arquivo: \n");
    scanf("%s", nomeArq);

    inicializar(nomeArq);

    while (1) {
        printf("Menu:\n");
        printf("1 - Inserir um novo aluno\n");
        printf("2 - Imprimir as informacoes de um determinado aluno (busca pela matricula)\n");
        printf("3 - Imprimir a tabela de dispersao (tabela hash)\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &x);

        switch (x) {
            case 1: {
                inserir(nomeArq, a);
                break;
            }
            case 2: {
                int mat;
                printf("Digite a matricula: \n");
                scanf("%d", &mat);
                ImprimirAluno(nomeArq, mat);
                break;
            }
            case 3: {
                ImprimirTabela(nomeArq);
                break;
            }
            case 4: {
                return 0;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
    }
}