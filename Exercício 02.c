#include <stdio.h>
#include <stdlib.h>


int main(){
    int i;
    int N;
    int *Numeros;
    float Media, Soma;
    Media=0;
    Soma=0;

    printf("Digite o numero de repeticoes: ");
    scanf("%d", &N);

    Numeros = (int*)malloc(N*sizeof(int));
    printf("Alocacao por vetor: \n");
    for (i=0; i<N; i++){
        printf("Armazene o dado %d: ", i+1);
        scanf("%d", &Numeros[i]);
    }
    printf("\n\nCalculo de media dos valores: \n");
    for (i=0; i<N; i++){
        Soma+=Numeros[i];
    }
    Media=Soma/N;
    printf("Media dos valores: %.1f\n", Media);
    free(Numeros);
    return 0;
}
