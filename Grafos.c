//Lara Fernandes e Victoria Valicelle
#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int destino;
    int custo;
    struct lista *prox;
} lista;

void inicializar(lista **g, int n){
    for (int i = 0; i <= n; i++)
    {
        g[i] = NULL;
    }   
}

lista *InserirLista(lista *l, int d, int c){
    lista *no = (lista *)malloc(sizeof(lista));
    no->destino = d;
    no->custo = c;
    no->prox = l;
    return no;
}

void InserirAresta(lista **g, int origem, int destino, int custo){
    g[origem] = InserirLista(g[origem], destino, custo);
}

void ImprimirLista(lista *l){
    if(l!=NULL){
        printf("-(%d, %d)", l->destino, l->custo);
        ImprimirLista(l->prox);
    }
}

void ImprimirGrafo(lista**g, int n){
    printf("Grafo: ");
    for (int i = 0; i <= n; i++)
    {
        printf("\n\t%d", i);
        ImprimirLista(g[i]);
    } 
}

lista *RemoverLista(lista *l, int d){
    lista *atual = l;
    lista *anterior = NULL;

    while (atual != NULL && atual->destino != d){
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL){
        if (anterior == NULL){
            l = atual->prox;
        } else{
            anterior->prox = atual->prox;
        }
        free(atual);
    } else {
        printf("Aresta para o destino %d nao encontrada!\n", d);
    }

    return l;
}

void RemoverAresta(lista **g, int origem, int destino){
    g[origem] = RemoverLista(g[origem], destino);
}

void CalcularGrauSaida(lista *l){
    int grau = 0;
    while (l != NULL){
        l = l->prox;
        grau++;
    }
    printf("Grau de saida: %d\n", grau);
}

void CalcularGrauEntrada(lista **g,int n, int vertice){
    int grau = 0;
    for (int i=1; i<=n; i++){
        lista *p = g[i];
        while (p != NULL){
            if (p->destino == vertice){
                grau++;
            }
            p = p->prox;
        }
        
    }
    printf("Grau de entrada: %d\n", grau);
}

void ImprimirGrau(lista **g, int n, int aresta){
    CalcularGrauEntrada(g, n, aresta);
    CalcularGrauSaida(g[aresta]);
}

int GrafoCompleto(lista **g, int n){
    for (int i=1; i<=n; i++){
        int grau = 0;
        lista *p = g[i];

        while (p != NULL){
            if (p->destino != i){
                grau++;
            }
            p = p->prox;
        }

        if (grau != n-1){
            return 0;
        }
    }
    return 1;
}

int existe(int *vet, int valor, int n){
    for (int i = 0; i < n; i++)
    {
        if (vet[i] == valor)
        {
            return 1;
        }
    }
    return 0;
}

void Caminhos(lista **g, int b, int *vet, int pos){
    if(vet[pos-1] == b){
        printf("\n");
        for (int i = 0; i < pos; i++)
        {
            printf("%d ", vet[i]);
        }
    }
    else{
        lista *p = g[vet[pos-1]];
        while(p!=NULL){
            if(!existe(vet, p->destino, pos)){
                vet[pos] = p->destino;
                Caminhos(g, b, vet, pos+1);
            }
            p = p->prox;
        }
    }
}

void MenorCaminho(lista **g, int origem, int destino, int *vet, int pos, int *menorCaminho, int *tamMenorCaminho){
    if(vet[pos-1] == destino){
        if (*tamMenorCaminho == -1 || pos < *tamMenorCaminho) {
            *tamMenorCaminho = pos;
            for (int i = 0; i < pos; i++) {
                menorCaminho[i] = vet[i];
            }
        }
    }
    else{
        lista *p = g[vet[pos-1]];
        while(p != NULL){
            if(!existe(vet, p->destino, pos)){
                vet[pos] = p->destino;
                MenorCaminho(g, origem, destino, vet, pos+1, menorCaminho, tamMenorCaminho);
            }
            p = p->prox;
        }
    }
}

void CaminhoMenorCusto(lista **g, int origem, int destino, int *vet, int pos, int custoAtual, int *menorCusto, int *caminhoMenorCusto, int *tamMenorCaminho){
    if(vet[pos-1] == destino){
        if (*menorCusto == -1 || custoAtual < *menorCusto) {
            *menorCusto = custoAtual;
            *tamMenorCaminho = pos;
            for (int i = 0; i < pos; i++) {
                caminhoMenorCusto[i] = vet[i];
            }
        }
    }
    else{
        lista *p = g[vet[pos-1]];
        while(p != NULL){
            if(!existe(vet, p->destino, pos)){
                vet[pos] = p->destino;
                CaminhoMenorCusto(g, origem, destino, vet, pos+1, custoAtual + p->custo, menorCusto, caminhoMenorCusto, tamMenorCaminho);
            }
            p = p->prox;
        }
    }
}

void LiberarLista(lista *l){
    lista *aux;
    while (l != NULL)
    {
        aux = l;
        l = l->prox;
        free(aux);
    }
}

void LiberarGrafo(lista **g, int n){
    for (int i=0; i<=n; i++){
        LiberarLista(g[i]);
    }
    free(g);
}


int main(void){
    int x;
    int n = 0;
    lista **g = NULL;

    printf("Digite o numero de vertices do grafico: ");
    scanf("%d", &n);

    g = (lista **)malloc((n+1)*sizeof(lista*));

    inicializar(g, n);

    while (1) {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Inserir uma aresta no grafo\n");
        printf("2 - Remover uma aresta do grafo\n");
        printf("3 - Imprimir grafo\n");
        printf("4 - Imprimir os graus de entrada e saida de um vertice\n");
        printf("5 - Verificar se um grafo eh completo\n");
        printf("6 - Imprimir todos os caminhos entre uma origem e um destino\n"); 
        printf("7 - Imprimir o caminho mais curto (com menor numero de arestas)\n");
        printf("8 - Imprimir o caminho de menor custo (menor soma dos custos das arestas)\n");
        printf("9 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &x);

        switch (x) {
            case 1: {
                int origem, destino, custo;
                printf("Digite a origem da aresta: ");
                scanf("%d", &origem);
                printf("Digite o destino da aresta: ");
                scanf("%d", &destino);
                printf("Digite o custo da aresta: ");
                scanf("%d", &custo);

                InserirAresta(g, origem, destino, custo);
                break;
            }
            case 2: {
                int origem, destino;
                printf("Digite a origem da aresta a ser removida: ");
                scanf("%d", &origem);
                printf("Digite o destino da aresta a ser removida: ");
                scanf("%d", &destino);

                RemoverAresta(g, origem, destino);
                break;
            }
            case 3: {
                ImprimirGrafo(g, n);
                break;
            }
            case 4: {
                int y;
                printf("Digite o vertice: ");
                scanf("%d", &y);
                ImprimirGrau(g, n, y);
                break;
            }
            case 5: {
                if (GrafoCompleto(g, n) == 1){
                    printf("Grafo completo!\n");
                } else {
                    printf("Grafo nao eh completo!\n");
                }
                break;
            }
            case 6: {
                int *vet;
                int origem, destino;
                printf("Digite a origem: ");
                scanf("%d", &origem);
                printf("Digite o destino: ");
                scanf("%d", &destino);

                vet = (int*)malloc(n*sizeof(int));
                vet[0] = origem;
                Caminhos(g, destino, vet, 1);
                free(vet);
                break;
            }
            case 7: {
                int origem, destino;
                printf("Digite a origem: ");
                scanf("%d", &origem);
                printf("Digite o destino: ");
                scanf("%d", &destino);
                int *vet = (int *)malloc(n * sizeof(int));
                int *menorCaminho = (int *)malloc(n * sizeof(int));
                int tamMenorCaminho = -1;
                vet[0] = origem;
                MenorCaminho(g, origem, destino, vet, 1, menorCaminho, &tamMenorCaminho);

                if (tamMenorCaminho == -1) {
                    printf("Nao existe caminho entre os vertices %d e %d.\n", origem, destino);
                } else {
                    printf("Menor caminho (em numero de arestas): ");
                    for (int i = 0; i < tamMenorCaminho; i++) {
                        printf("%d ", menorCaminho[i]);
                    }
                    printf("\n");
                }
                free(vet);
                free(menorCaminho);
                break;
            }
            case 8: {
                int origem, destino;
                printf("Digite a origem: ");
                scanf("%d", &origem);
                printf("Digite o destino: ");
                scanf("%d", &destino);
                int *caminhoMenorCusto = (int *)malloc(n * sizeof(int));
                int menorCusto = -1;
                int tamMenorCaminho = -1;
                int *vet = (int *)malloc(n * sizeof(int));
                
                vet[0] = origem;
                CaminhoMenorCusto(g, origem, destino, vet, 1, 0, &menorCusto, caminhoMenorCusto, &tamMenorCaminho);

                if (menorCusto == -1) {
                    printf("Nao existe caminho de menor custo entre os vertices %d e %d.\n", origem, destino);
                } else {
                    printf("Caminho de menor custo: ");
                    for (int i = 0; i < tamMenorCaminho; i++) {
                        printf("%d ", caminhoMenorCusto[i]);
                    }
                    printf("\nCusto total: %d\n", menorCusto);
                }
                
                free(vet);
                free(caminhoMenorCusto);
                break;
            }
            case 9: {
                LiberarGrafo(g, n);
                return 0;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
    }
}