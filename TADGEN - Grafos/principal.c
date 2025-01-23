#include "grafo.h"
#include <stdio.h>
#include <string.h>

// Estruturas
typedef struct {
    float tempo;
    float distancia;
} Rota;

typedef struct {
    int n_conexao;
    char tipo_conexao[30];
} Conexao;

// Função para exibir o menu
int exibir_menu() {
    int opcao;
    printf("\n--- Menu do Grafo ---\n");
    printf("1. Adicionar Aresta\n");
    printf("2. Remover Aresta\n");
    printf("3. Imprimir Grafo\n");
    printf("4. Buscar Informacao\n");
    printf("5. Calcular Grau do Vertice\n");
    printf("6. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

// Primeira main
int main() {
    Grafo grafo = Grafo_Inicializar(5);
    int opcao;

    do {
        opcao = exibir_menu();
        switch (opcao) {
            case 1: {
                int origem, destino;
                Rota rota;

                printf("Informe a origem da rota: ");
                scanf("%d", &origem);
                printf("Informe o destino da rota: ");
                scanf("%d", &destino);

                printf("Informe o tempo da rota (em horas): ");
                scanf("%f", &rota.tempo);
                printf("Informe a distancia da rota (em km): ");
                scanf("%f", &rota.distancia);

                if (Grafo_BuscarCusto(grafo, origem, destino) == NULL) {
                    Grafo_InserirAresta(grafo, origem, destino, &rota, sizeof(Rota));
                    printf("Aresta %d -> %d adicionada.\n", origem, destino);
                } else {
                    printf("A aresta %d -> %d ja existe.\n", origem, destino);
                }
                break;
            }
            case 2: {
                int origem, destino;

                printf("Informe a origem da rota: ");
                scanf("%d", &origem);
                printf("Informe o destino da rota: ");
                scanf("%d", &destino);

                if (Grafo_BuscarCusto(grafo, origem, destino) == NULL) {
                    printf("A aresta %d -> %d nao existe.\n", origem, destino);
                } else {
                    Grafo_RemoverAresta(grafo, origem, destino);
                    printf("Aresta %d -> %d removida.\n", origem, destino);
                }
                break;
            }
            case 3: {
                Grafo_Imprimir(grafo);
                break;
            }
            case 4: {
                int origem, destino;

                printf("Digite a origem e o destino da rota para buscar as informacoes: ");
                scanf("%d %d", &origem, &destino);

                Rota *rota = (Rota *)Grafo_BuscarCusto(grafo, origem, destino);
                if (rota) {
                    printf("Rota encontrada: %d -> %d\n", origem, destino);
                    printf("Tempo: %.2f h, Distancia: %.2f km\n", rota->tempo, rota->distancia);
                } else {
                    printf("Rota %d -> %d nao encontrada.\n", origem, destino);
                }
                break;
            }
            case 5: {
                int y;
                printf("Digite o vertice: ");
                scanf("%d", &y);
                int z = Grafo_GrauVertice(grafo, y);
                printf("Grau do vertice %d : %d \n", y, z);
                break;
            }
            case 6: {
                printf("Saindo...\n");
                break;
            }
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);

    Grafo_Destruir(grafo);
    return 0;
}

/*
// Segunda main
int main() {

    Grafo grafo = Grafo_Inicializar(4);
    int opcao;

    do {
        opcao = exibir_menu();
        switch (opcao) {
            case 1: {
                int origem, destino;
                Conexao conexao;

                printf("Informe a origem da conexao: ");
                scanf("%d", &origem);
                printf("Informe o destino da conexao: ");
                scanf("%d", &destino);

                printf("Informe o tipo da conexao (ex.: 'Amizade', 'Seguidor'): ");
                scanf("%s", conexao.tipo_conexao);
                printf("Informe o numero de conexoes: ");
                scanf("%d", &conexao.n_conexao);

                if (Grafo_BuscarCusto(grafo, origem, destino) == NULL) {
                    Grafo_InserirAresta(grafo, origem, destino, &conexao, sizeof(Conexao));
                    printf("Aresta %d -> %d adicionada.\n", origem, destino);
                } else {
                    printf("A aresta %d -> %d ja existe.\n", origem, destino);
                }
                break;
            }
            case 2: {
                int origem, destino;
                Conexao conexao;

                printf("Informe a origem da conexao: ");
                scanf("%d", &origem);
                printf("Informe o destino da conexao: ");
                scanf("%d", &destino);

                if (Grafo_BuscarCusto(grafo, origem, destino) == NULL) {
                    printf("A aresta %d -> %d nao existe.\n", origem, destino);
                } else {
                    Grafo_RemoverAresta(grafo, origem, destino);
                    printf("Aresta %d -> %d removida.\n", origem, destino);
                }
                break;
            }
            case 3: {
                Grafo_Imprimir(grafo);
                break;
            }
            case 4: {
                int origem, destino;

                printf("Digite a origem e o destino da conexao para buscar as informacoes: ");
                scanf("%d %d", &origem, &destino);

                Conexao *conexao = (Conexao *)Grafo_BuscarCusto(grafo, origem, destino);
                if (conexao) {
                    printf("Conexao encontrada: %d -> %d\n", origem, destino);
                    printf("%s, Quantidade: %d\n", 
                        conexao->tipo_conexao, conexao->n_conexao);
                } else {
                    printf("Conexao %d -> %d nao encontrada.\n", origem, destino);
                }
                break;
            }
            case 5: {              
                int y;
                printf("Digite o vertice: ");
                scanf("%d", &y);
                int z = Grafo_GrauVertice(grafo, y);
                printf("Grau do vertice %d : %d \n", y, z);
                break;
            }
            case 6: {
                printf("Saindo...\n");
                break;
            } 
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);

    Grafo_Destruir(grafo);
    return 0;
}
*/
