#include <stdio.h>
#include <stdlib.h>

int main(){
    int i, j;
    int Numeros[10];
    int Matriz[3][4];

    printf("Alocacao por vetor: \n");
    for (i=0; i<10; i++){
        printf("Armazene o dado %d: ", i+1);
        scanf("%d", &Numeros[i]);
    }
    printf("\n\nImpressao dos valores: \n");
    for (i=0; i<10; i++){
        printf("Dado %d: %d\n", i+1, Numeros[i]);
    }

    printf("\nAlocacao por matriz: \n");
     for(i=0; i<3; i++){
        for (j=0; j<4; j++){
            printf("Linha %d, Coluna %d: ", i+1, j+1);
            scanf("%d", &Matriz[i][j]);
        }
        printf("\n");
    }
    printf("Impressao da matriz:\n");
    for(i=0; i<3; i++){
        for (j=0; j<4; j++){
            printf("%d\t", Matriz[i][j]);
        }
        printf("\n");
    }
    return 0;
}
