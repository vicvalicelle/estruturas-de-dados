//Lara Fernandes e Victoria Valicelle
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct professores{
    int matricula;
    char nome[50];
    float salario;
}Professores;

typedef struct alunos{
    int matricula;
    char nome[50];
    char curso[30];
    int anoI;
}Alunos;

typedef struct pessoa{
    int tipo; // 1- Professor e 2- Aluno
    void* item;
}Pessoa;

void Inicializar(Pessoa *vet, int tam){
    for (int i = 0; i < tam; i++)
    {
        vet[i].tipo = 0;
        vet[i].item = NULL;
    }
}

void Inserir(Pessoa *vet, int tam, void *info, int tipo){
    for (int i = 0; i < tam; i++)
    {
        if(vet[i].tipo == 0){
            vet[i].tipo = tipo;
            vet[i].item = info;
            return;
        }
    }
}

void RemoverMatricula(Pessoa *vet, int tam, int matricula){
    for (int i = 0; i < tam; i++)
    {
        if(vet[i].tipo == 1){
            Professores *p = (Professores *)vet[i].item;
            if(p->matricula == matricula){
                vet[i].tipo = 0;
                vet[i].item = NULL;
                return;
            }
        }
        else if(vet[i].tipo == 2){
            Alunos *a = (Alunos *)vet[i].item;
            if(a->matricula == matricula){
                vet[i].tipo = 0;
                vet[i].item = NULL;
                return;
            }
        }
    }
}

void BuscaMatricula(Pessoa *vet, int tam, int mat){
    for (int i = 0; i < tam; i++)
    {
        if(vet[i].tipo == 1){
            Professores *p = (Professores *)vet[i].item;
            if(p->matricula == mat){
                printf("Matricula: %d - Nome: %s - Salario: %.2f\n", p->matricula, p->nome, p->salario);
                return;
            }
        }
        else if(vet[i].tipo == 2){
            Alunos *a = (Alunos *)vet[i].item;
            if(a->matricula == mat){
                printf("Matricula: %d - Nome: %s - Curso: %s - Ano de Ingresso: %d\n", a->matricula, a->nome, a->curso, a->anoI);
                return;
            }
        }
    }
}

int ContarAlunosPorCurso(Pessoa *vet, int tam, const char *curso) {
    int contador = 0;
    for (int i = 0; i < tam; i++) {
        if (vet[i].tipo == 2) {
            Alunos *a = (Alunos *)vet[i].item;
            if (strcmp(a->curso, curso) == 0) {
                contador++;
            }
        }
    }
    return contador;
}

void ImprimirProfessoresMaiorSalario(Pessoa *vet, int tam) {
    float maiorSalario = 0;

    for (int i = 0; i < tam; i++) {
        if (vet[i].tipo == 1) {
            Professores *p = (Professores *)vet[i].item;
            if (p->salario > maiorSalario) {
                maiorSalario = p->salario;
            }
        }
    }

    printf("Professores com salario: %.2f\n", maiorSalario);
    for (int i = 0; i < tam; i++) {
        if (vet[i].tipo == 1) {
            Professores *p = (Professores *)vet[i].item;
            if (p->salario == maiorSalario) {
                printf("Matricula: %d - Nome: %s - Salario: %.2f\n", p->matricula, p->nome, p->salario);
            }
        }
    }
}

void Destruir(Pessoa *vet, int tam) {
    for (int i = 0; i < tam; i++) {
        if (vet[i].tipo == 1) {
            Professores *p = (Professores *)vet[i].item;
            free(p);
        } else if (vet[i].tipo == 2) {
            Alunos *a = (Alunos *)vet[i].item;
            free(a);
        }
    }
}

int main(){
    Pessoa vet[10];
    int tam = sizeof(vet) / sizeof(vet[0]);
    Inicializar(vet, tam);

    int opcao;
    int matricula;
    char curso[30];
    while (1) {
        printf("\nMenu:\n");
        printf("1 - Inserir uma pessoa na lista (pode ser no inicio)\n");
        printf("2 - Remover uma pessoa pela matricula\n");
        printf("3 - Buscar uma pessoa pela matricula\n");
        printf("4 - Contar o numero de alunos em um determinado curso\n");
        printf("5 - Imprimir os professores com o maior salario\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int tipo;
                printf("Escolha o tipo de pessoa (1 - Professor, 2 - Aluno): ");
                scanf("%d", &tipo);

                if (tipo == 1) {
                    Professores *prof = (Professores*) malloc(sizeof(Professores));
                    printf("Inserir matricula, nome e salario: ");
                    scanf("%d %s %f", &prof->matricula, prof->nome, &prof->salario);
                    Inserir(vet, tam, prof, 1);
                } else if (tipo == 2) {
                    Alunos *aluno = (Alunos*) malloc(sizeof(Alunos));
                    printf("Inserir matricula, nome, curso e ano de ingresso: ");
                    scanf("%d %s %s %d", &aluno->matricula, aluno->nome, aluno->curso, &aluno->anoI);
                    Inserir(vet, tam, aluno, 2);
                }
                break;
            }
            case 2: {
                printf("Digite a matricula da pessoa a ser removida: ");
                scanf("%d", &matricula);
                RemoverMatricula(vet, tam, matricula);
                break;
            }
            case 3: {
                printf("Digite a matricula da pessoa a ser buscada: ");
                scanf("%d", &matricula);
                BuscaMatricula(vet, tam, matricula);
                break;
            }
            case 4: {
                printf("Digite o nome do curso: ");
                scanf("%s", curso);
                int numAlunos = ContarAlunosPorCurso(vet, tam, curso);
                printf("Numero de alunos no curso %s: %d\n", curso, numAlunos);
                break;
            }
            case 5: {
                ImprimirProfessoresMaiorSalario(vet, tam);
                break;
            }
            case 6: {
                Destruir(vet, tam);
                return 0;
            }
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}