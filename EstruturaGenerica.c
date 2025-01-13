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

typedef struct pessoa {
    int tipo; // 1- Professor e 2- Aluno
    void *item;
    struct pessoa *next;
} Pessoa;

void Inicializar(Pessoa **head) {
    *head = NULL;
}

void Inserir(Pessoa **head, void *info, int tipo) {
    Pessoa *novaPessoa = (Pessoa*)malloc(sizeof(Pessoa));
    novaPessoa->tipo = tipo;
    novaPessoa->item = info;
    novaPessoa->next = *head;
    *head = novaPessoa;
}

void Destruir(Pessoa *head) {
    Pessoa *atual = head;
    while (atual != NULL) {
        if (atual->tipo == 1) {
            Professores *p = (Professores*)atual->item;
            free(p);
        } else if (atual->tipo == 2) {
            Alunos *a = (Alunos*)atual->item;
            free(a);
        }
        atual = atual->next;
    }
}

void RemoverMatricula(Pessoa **head, int matricula) {
    Pessoa *atual = *head;
    Pessoa *anterior = NULL;

    while (atual != NULL) {
        if (atual->tipo == 1) {
            Professores *p = (Professores*)atual->item;
            if (p->matricula == matricula) {
                if (anterior == NULL) {
                    *head = atual->next;
                } else {
                    anterior->next = atual->next;
                }
                free(p);
                free(atual);
                return;
            }
        } else if (atual->tipo == 2) {
            Alunos *a = (Alunos*)atual->item;
            if (a->matricula == matricula) {
                if (anterior == NULL) {
                    *head = atual->next;
                } else {
                    anterior->next = atual->next;
                }
                free(a);
                free(atual);
                return;
            }
        }
        anterior = atual;
        atual = atual->next;
    }
}

void BuscaMatricula(Pessoa *head, int mat) {
    Pessoa *atual = head;

    while (atual != NULL) {
        if (atual->tipo == 1) {
            Professores *p = (Professores*)atual->item;
            if (p->matricula == mat) {
                printf("Matricula: %d - Nome: %s - Salario: %.2f\n", p->matricula, p->nome, p->salario);
                return;
            }
        } else if (atual->tipo == 2) {
            Alunos *a = (Alunos*)atual->item;
            if (a->matricula == mat) {
                printf("Matricula: %d - Nome: %s - Curso: %s - Ano de Ingresso: %d\n", a->matricula, a->nome, a->curso, a->anoI);
                return;
            }
        }
        atual = atual->next;
    }
}

int ContarAlunosPorCurso(Pessoa *head, const char *curso) {
    int contador = 0;
    Pessoa *atual = head;

    while (atual != NULL) {
        if (atual->tipo == 2) {
            Alunos *a = (Alunos*)atual->item;
            if (strcmp(a->curso, curso) == 0) {
                contador++;
            }
        }
        atual = atual->next;
    }
    return contador;
}

void ImprimirProfessoresMaiorSalario(Pessoa *head) {
    float maiorSalario = 0;
    Pessoa *atual = head;

    while (atual != NULL) {
        if (atual->tipo == 1) { // Professor
            Professores *p = (Professores*)atual->item;
            if (p->salario > maiorSalario) {
                maiorSalario = p->salario;
            }
        }
        atual = atual->next;
    }

    printf("Professores com salario: %.2f\n", maiorSalario);
    atual = head;
    while (atual != NULL) {
        if (atual->tipo == 1) { // Professor
            Professores *p = (Professores*)atual->item;
            if (p->salario == maiorSalario) {
                printf("Matricula: %d - Nome: %s - Salario: %.2f\n", p->matricula, p->nome, p->salario);
            }
        }
        atual = atual->next;
    }
}

int main() {
    Pessoa *head;
    Inicializar(&head);

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
                    Inserir(&head, prof, 1);
                } else if (tipo == 2) {
                    Alunos *aluno = (Alunos*) malloc(sizeof(Alunos));
                    printf("Inserir matricula, nome, curso e ano de ingresso: ");
                    scanf("%d %s %s %d", &aluno->matricula, aluno->nome, aluno->curso, &aluno->anoI);
                    Inserir(&head, aluno, 2);
                }
                break;
            }
            case 2: {
                printf("Digite a matricula da pessoa a ser removida: ");
                scanf("%d", &matricula);
                RemoverMatricula(&head, matricula);
                break;
            }
            case 3: {
                printf("Digite a matricula da pessoa a ser buscada: ");
                scanf("%d", &matricula);
                BuscaMatricula(head, matricula);
                break;
            }
            case 4: {
                printf("Digite o nome do curso: ");
                scanf("%s", curso);
                int numAlunos = ContarAlunosPorCurso(head, curso);
                printf("Numero de alunos no curso %s: %d\n", curso, numAlunos);
                break;
            }
            case 5: {
                ImprimirProfessoresMaiorSalario(head);
                break;
            }
            case 6: {
                Destruir(head);
                return 0;
            }
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}