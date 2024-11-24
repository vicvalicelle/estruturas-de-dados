//Lara Fernandes e Victoria Valicelle
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int totalElementos = 0;
int indiceFilhoEsq(int x);
int indiceFilhoDir(int x);
int indicePai(int x);
void Inserir(float *heap, int x);
void AjustarSubindo(float *heap, int pos);
int Remover(float *heap);
void AjustarDescendo(float *heap, int pos);
void Imprimir(float *heap);

int indiceFilhoEsq(int x){
    int indice = (2*x)+1;
    if (x>=totalElementos || indice>=totalElementos){
        return -1;
    } else{
        return indice;
    }
}

int indiceFilhoDir(int x){
    int indice=(2*x)+2;
    if (x>=totalElementos || indice>=totalElementos){
        return -1;
    } else{
        return indice;
    }
}

int indicePai(int x){
    int indice = (int)floor((x-1)/2);
    if(x<=0 || x>=totalElementos){
        return -1;
    } else{
        return indice;
    }
}

void Inserir(float *heap, int x){
    heap[totalElementos] = x;
    totalElementos++;

    AjustarSubindo(heap, totalElementos-1);
}

void AjustarSubindo (float *heap, int pos){
    if (pos != -1){
        int pai = indicePai(pos);
        if (pai != -1){
            if (heap[pos] < heap[pai]){ 
                int aux = heap[pos];
                heap[pos] = heap[pai];
                heap[pai] = aux;
                AjustarSubindo(heap, pai);
            }
        }
    }
}

int Remover(float *heap){
    if (totalElementos == 0){
        return -1;
    } else{
        int retorno = heap[0];
        heap[0] = heap[totalElementos-1];
        totalElementos--;
        AjustarDescendo(heap,0);
        return retorno;
    }
}

void AjustarDescendo(float *heap, int pos){
    if (pos != -1 && indiceFilhoEsq(pos) != -1){
        //Descobrindo o menor filho
        int indiceMenorFilho = indiceFilhoEsq(pos);
        if (indiceFilhoDir(pos) != -1 && heap[indiceFilhoDir(pos)] < heap[indiceMenorFilho]){
            indiceMenorFilho = indiceFilhoDir(pos);
        }

        //Verificando se existe filho menor que o no atual
        if(heap[indiceMenorFilho] < heap[pos]){
            int aux = heap[pos];
            heap[pos] = heap[indiceMenorFilho];
            heap[indiceMenorFilho] = aux;
            AjustarDescendo(heap, indiceMenorFilho);
        }
    }
}

void Imprimir(float *heap){
    for (int i=0; i<totalElementos; i++){
        printf("%g ", heap[i]);
    }
    printf("\n");
}

int main(void){
    float heap[100];
    int x;

    while (1) {
        printf("Menu:\n");
        printf("1 - Inserir um elemento x na heap\n");
        printf("2 - Remover um elemento\n");
        printf("3 - Imprimir a heap\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &x);

        switch (x) {
            case 1: {
                int x;
                printf("Digite um numero para ser inserido: ");
                scanf("%d", &x);

                Inserir(heap, x);
                break;
            }
            case 2: {
                int y = Remover(heap);

                if (totalElementos == 0) {
                    printf("Heap vazio!\n");
                } else {
                    printf("Elemento removido: %d\n", y);
                }
                break;
            }
            case 3: {
                if (totalElementos == 0){
                    printf("Heap vazia.\n");
                }else {
                    printf("Heap: ");
                    Imprimir(heap);
                }
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