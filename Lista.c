#include <stdio.h>
#include <stdlib.h>

//CONSTANTE
int CapacidadeLista=10;

typedef struct Lista{
    int info;
    struct Lista *proximo;
}lista;

void InicioLista(lista **p){
    (*p)->proximo=NULL;
}

void Inserir (lista **p){
    int Valores;
    lista *insercao;

    scanf("%d", &Valores);
    insercao= (lista *)malloc(sizeof(lista));
    insercao->info= Valores;
    insercao->proximo= (*p)->proximo;
    (*p)->proximo=insercao;
}

void Buscar (lista **p){
    lista *insercao;

    if((*p)->proximo==NULL)
        printf("Lista vazia! \n");
    else{
        insercao= (lista *)malloc(sizeof(lista));
        insercao=(*p)->proximo;
        while(insercao!=NULL){
            printf("Valor: %d\n", insercao->info);
            insercao= insercao->proximo;
        }
    }
}

void Remocao (lista**p){
    lista *insercao;

    if((*p)->proximo==NULL)
        printf("Lista vazia! \n");
    else{
        insercao= (*p)->proximo;
        (*p)->proximo= insercao->proximo;
        free(insercao);
    }
}

int main(){
    int i, aux;
    int RespostaUsuario;

    lista *pLista;
    pLista= (lista *)malloc(sizeof(struct Lista));
    aux=1;

    InicioLista(&pLista);
    printf("Insira dez valores para a lista: \n");
    for(i=0; i<CapacidadeLista; i++){
        printf("Valor %d: ", i+1);
        Inserir(&pLista);
    }
    printf("\nQuadro geral da lista: \n");
    Buscar(&pLista);
    while(aux==1){
        printf("\nDeseja retirar valor nesta lista?\n<1> SIM <OUTRO VALOR> NAO ");
        scanf("%d", &RespostaUsuario);
        switch(RespostaUsuario){
            case(1):
                Remocao(&pLista);
                aux=1;
                printf("Situacao da lista:\n");
                Buscar(&pLista);
                break;
            default:
                printf("Fim da linha!\n");
                aux=0;
                break;
        }
    }
    return 0;
}
