/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Algoritmos e Programação de Computadores – 1/2017

Alunos: Lucas da Silva Souza, Gustavo Costa de Souza
Matriculas: 16/0013020, 15/0128576
Turma: B
Versão do compilador: GCC 4.7.1

Descricao: Trabalho Obrigatorio 02.
Simulação de uma agenda telefônica. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct No{ //Struct dos nós de uma lista
	char Nome[30];
	char Endereco[30];
	int Numero;
    int aux; //Usada somente para organizar a lista.
	struct No *prox;
};

typedef struct No no;
int Contagem;
int Escolha(void);
int selecionarOpcao(no *entrada, int op);
void EditarContato(no *entrada);
void RemoverContato(no *entrada);
void AdicionarContato(no *entrada);
void ListarContatos(no *entrada);
void OrganizarLista(no* entrada);

int* TransformarString(char* entrada) {
    char chave[53] = " AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    int X, Y;
    int* retorno = malloc(strlen(entrada) * sizeof(*retorno));
    for(X = 0; X < strlen(entrada); X++) {
        for(Y = 0; Y < strlen(chave); Y++) {
            if(entrada[X] == chave[Y])
                retorno[X] = Y;
        }
    }
    return retorno;
}

int JaExistente(no *entrada, int Numero) {
    no* tmp = entrada;
    while(tmp != NULL) {
        if(tmp->Numero == Numero)
            return 1;
        tmp = tmp->prox;
    }
    return 0;
}

void AdicionarLista(no *entrada, char* Nome, char* Endereco, int Numero, int aux){
	no *novo= (no *) malloc(sizeof(no));
	strcpy(novo->Nome, Nome);
	strcpy(novo->Endereco, Endereco);
	novo->Numero = Numero;
	novo->prox = NULL;
    if(aux == 1)
        novo->aux = 1;
	if(JaExistente(entrada, Numero) == 1)
        return;
	if(vazia(entrada))
		entrada->prox=novo;
	else{
		no *tmp = entrada->prox;
		while(tmp->prox != NULL)
			tmp = tmp->prox;
		tmp->prox = novo;
	}
}

no* CompararNos(no* No1, no* No2) { //Esta função irá retornar a string que em uma lista alfabética ficaria no final.
    char String1[30], String2[30];
    strcpy(String1, No1->Nome);
    strcpy(String2, No2->Nome);
    int* _string1 = TransformarString(String1);
    int* _string2 = TransformarString(String2);
    int i;
    int max = strlen(String1) > strlen(String1) ? strlen(String1) : strlen(String2);

    for(i = 0; i < max; i++) {
        if(_string1[i] > _string2[i])
            return No2;
        else if(_string1[i] < _string2[i])
            return No1;
    }
    return No2;
}

int main(void){
    no *lista = (no *) malloc(sizeof(no)); //Criação do nó principal, será usado em todas as funções.
	Contagem=0;
	int iOpcao;
	printf("Bem vindo a Agenda Telefonica 2000!\n");
	printf("Eis algumas funcoes desta agenda:\n");
	printf("\t- Listagem de contatos (em ordem numerica);\n\t- Adicao, Edicao e Remocao de contatos;\n\t- Funcao para organizar os contatos por ordem alfabetica.\n");
	printf("\t- Use a vontade e venha de zap voce tambem!\n\n");
	while(iOpcao) {
		iOpcao=Escolha();
		if(selecionarOpcao(lista,iOpcao) == 0)
            return 0;
	}

	return 0;
}

int Escolha(void){
	int aux;
	printf("Escolha uma opcao\n");
	printf("0. Sair\n");
	printf("1. Listar contatos (em ordem numerica)\n");
	printf("2. Adicionar contato\n");
	printf("3. Remover contato\n");
	printf("4. Editar contato\n");
	printf("5. Organizar e Imprimir Lista (em ordem alfabetica)\n");
	printf("Opcao: "); scanf("%d", &aux);
    printf("\n");
	return aux;
}

int selecionarOpcao(no *entrada, int op){
	no *tmp;
	switch(op){
		case 0:
			return 0;
		case 1:
			ListarContatos(entrada);
			break;
		case 2:
			AdicionarContato(entrada);
			break;
        case 3:
            RemoverContato(entrada);
            break;
        case 4:
            EditarContato(entrada);
            break;
        case 5:
            OrganizarLista(entrada);
            break;
		default:
			printf("Comando invalido\n");
	}
	printf("\n");
	return 1;
}

int vazia(no *entrada){
	if(entrada->prox == NULL)
		return 1;
	else
		return 0;
}

no * swapAdjacent(no * list) {
   if (!list) return NULL;
   if (!list->prox) return list;

   no *newHead = list->prox;
   list->prox = swapAdjacent(newHead->prox);
   newHead->prox = list;
   return newHead;
}

void InverterPointers( no **p, no **pt){
    int *pp;
    pp = *p;
    *p = *pt;
    *pt= pp;
}

void OrganizarLista(no* entrada) {
    no* ordenada = (no *) malloc(sizeof(no));
    ordenada->prox = NULL;
    no* temp = entrada;
    no* menorNo = NULL;
    while(1 == 1) {
        while(temp != NULL) {
            temp = temp->prox;
            if(temp != NULL) {
                if(JaExistente(ordenada, temp->Numero) == 1)
                    continue;
                if(temp->prox != NULL && menorNo == NULL) {
                    if(JaExistente(ordenada, temp->prox->Numero) == 1) {
                        menorNo = temp;
                        continue;
                    }
                    if(menorNo == NULL)
                        menorNo = CompararNos(temp, temp->prox);
                }
                else if(menorNo != NULL) {
                    menorNo = CompararNos(menorNo, temp);
                }
            }
        }
        if(menorNo != NULL) {
            AdicionarLista(ordenada, menorNo->Nome, menorNo->Endereco, menorNo->Numero, 1);
            temp = entrada;
            menorNo = NULL;
        }
        else {
            temp = entrada;
            while(temp != NULL) {
                if(JaExistente(ordenada, temp->Numero) == 0)
                    AdicionarLista(ordenada, temp->Nome, temp->Endereco, temp->Numero, 1);
                temp = temp->prox;
            }
            break;
        }
    }
    printf("\nLista organizada em ordem alfabetica:\n");
    temp = ordenada->prox;
    while(temp != NULL) {
        printf("\t%s - %s - %d\n", temp->Nome, temp->Endereco, temp->Numero);
        temp = temp->prox;
    }
}

void EditarContato(no *entrada) {
    int Num = 0, encontrado = 0;
    char Nome[30], Endereco[30];
	int Numero = 0;
    printf("Numero que deseja editar: "); scanf("%d", &Num);
    no* aux = entrada;
    no* anterior;
    while( aux != NULL){
		if(aux != NULL && aux->Numero == Num) {
            encontrado = 1;
            int opt = 0;
            printf("Estamos editando a pessoa de nome %s, caso deseje continuar digite 1, caso nao deseje digite 0.\nOpcao: ", aux->Nome); scanf("%d", &opt);
            if(opt == 0)
                printf("Cancelando remocao.");
            else {
                getchar();
                printf("Novo nome: "); fgets (&aux->Nome, 30, stdin);
                printf("Novo endereco: "); fgets (&aux->Endereco, 30, stdin);
                printf("Novo numero: "); scanf("%d", &aux->Numero);
                strtok(&aux->Nome, "\n");
                strtok(&aux->Endereco, "\n");
            }
            break;
		}
        aux = aux->prox;
	}
	if(encontrado == 0)
        printf("Desculpe, este numero nao foi encontrado em seus contatos.\n\n");
}

void RemoverContato(no *entrada){
    int Num = 0, encontrado = 0;
    printf("Numero que deseja remover: "); scanf("%d", &Num);

    no* aux = entrada;
    no* anterior;
    while( aux != NULL){
        anterior = aux;
        aux = aux->prox;
		if(aux != NULL && aux->Numero == Num) {
            encontrado = 1;
            anterior->prox = aux->prox;
            break;
		}
	}
	if(encontrado == 0)
        printf("Desculpe, este numero nao foi encontrado em seus contatos.\n\n");
}

void AdicionarContato(no *entrada){
	no *novo= (no *) malloc(sizeof(no));
	getchar();

	char Nome[30], Endereco[30];
	int Num = 0;

    printf("Nome: "); fgets (Nome, 30, stdin);
    printf("Endereco: "); fgets (Endereco, 30, stdin);
    printf("Numero: "); scanf("%d", &Num);

    strtok(Nome, "\n");
    strtok(Endereco, "\n");

    if(Num < 0) {
        printf("O numero nao pode ser negativo! Retornando ao menu...");
        return;
    }

    if(JaExistente(entrada, Num)) {
        printf("Este numero ja existe em sua lista!");
        return;
    }
    AdicionarLista(entrada, Nome, Endereco, Num, 1);
	Contagem++;
}

void ListarContatos(no *entrada){
	if(vazia(entrada)){
		printf("Erro! Voce nao possui nenhum contato.\n\n");
		return ;
	}
	no *aux;
	aux = entrada->prox;
	printf("Lista:");
	while( aux != NULL){
		printf("\n\tNumero %d - %s - %s", aux->Numero, aux->Nome, aux->Endereco);
		aux = aux->prox;
	}
	printf("\n\n");
}

