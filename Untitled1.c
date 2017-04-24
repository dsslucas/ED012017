#include <stdio.h>
#include <stdlib.h>

//CAMPO DA CONSTANTE
int capacidade=10;

struct Fila{
    int capacidade;
    int *dados;
    int PrimeiroValor;
    int UltimoValor;
    int NValores;
};

void CriarFila(struct Fila *f, int capacidade){
    f->capacidade;
    f->dados=(int*)malloc(f->capacidade*sizeof(int));
    f->PrimeiroValor=0;
    f->UltimoValor=-1;
    f->NValores=0;
}

void InicioFila (struct Fila *f, int ValorEntrada){
    if(f->UltimoValor==f->capacidade-1){
        f->UltimoValor=-1;
    }
    f->UltimoValor++;
    f->dados[f->UltimoValor]=ValorEntrada;
    f->NValores++;
}

void MostrarFila(struct Fila *f){
	int contador, i;
	printf("\nValores contidos na fila: \n");
	for (contador=0, i=f->PrimeiroValor; contador<f->NValores; contador++){
		printf("%d\t", f->dados[i++]);
		if (i == f->capacidade)
			i=0;
    }
    printf("\n\n");
}

void LimpezaFila (struct Fila *f){
    int aux=f->dados[f->PrimeiroValor++];
    if(f->PrimeiroValor==f->capacidade){
        f->PrimeiroValor=0;
    }
    return aux;
}

int main(){
    int i, Valor, qtdfila=10, j;
    struct Fila fila;
    CriarFila(&fila, qtdfila);
    printf("Criando uma fila para os dez valores:\n");
    for(i=0; i<10; i++){
        printf("Elemento n.%d: ", i+1);
        scanf("%d", &Valor);
        InicioFila(&fila, Valor);
    }
    MostrarFila(&fila);
    LimpezaFila(&fila);
    printf("Fila limpa com sucesso!\n");
    return 0;
}
