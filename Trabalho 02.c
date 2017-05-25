/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Algoritmos e Programação de Computadores – 1/2017

Alunos: Lucas da Silva Souza, Gustavo Costa 
Matriculas: 16/0013020, (MATRICULA A CONFIRMAR)
Turma: B
Versão do compilador: GCC 4.7.1

Descricao: Trabalho Obrigatorio 01.
Jogo de Batalha Naval entre dois players. */

#include <stdio.h>
#include <stdlib.h>

/*Funções de salvamento e carregamento de dados
    Carregar()
    Salvar()*/

FILE* fp;

struct Contato {
    char Nome[30];
    char Endereco[30];
    int Numero;
    int nulo;
};
struct Contato Contatos[500];
int numContatos = 0;
int Iniciado = 0;

void Salvar() {
    fp = fopen("lista.txt", "w+");
    int i = 0;

    for(i=0; i <= numContatos; i++){
        fprintf(fp,"nome%d:%s\n", i, Contatos[i].Nome);
        fprintf(fp,"endereco%d:%s\n", i, Contatos[i].Endereco);
        fprintf(fp,"numero%d:%d\n", i, Contatos[i].Numero);
    }
    fclose(fp);
}

void Carregar() {
    fp = fopen("lista.txt", "r+");
    int iEndereco = 0;
    int iNumero = 0;
    int iNome = 0;
    char line[256];
    char* lixo;

    while (fgets(line, sizeof(line), fp)) {
        if(strncmp(line, "nome", 4) == 0) {
            const char* linha_aux = line;
            while (*linha_aux != ':') {
                linha_aux++;
            }
            linha_aux++;

            printf("%s", linha_aux);
            strcpy(Contatos[iNome].Nome, linha_aux);
            iNome = iNome + 1;
        }
        else if(strncmp(line, "endereco", 8) == 0) {
            const char* linha_aux = line;
            while (*linha_aux != ':') {
                linha_aux++;
            }
            linha_aux++;

            printf("%s", linha_aux);
            strcpy(Contatos[iEndereco].Endereco, linha_aux);
            iEndereco = iEndereco + 1;
        }
        else if(strncmp(line, "numero", 6) == 0) {
            const char* linha_aux = line;
            while (*linha_aux != ':') {
                linha_aux++;
            }
            linha_aux++;

            printf("%s", linha_aux);
            Contatos[iNumero].Numero = (int)strtof(linha_aux, &lixo);
            iNumero = iNumero + 1;
        }
    }
}

void ListarContatos() {
    printf("\nAtualmente voce possui %d contatos", numContatos);
    printf("\nListagem:");
    for(int X = 0; X < numContatos; X++) {
        printf("\n\tNome: %s\n\tNumero: %d\n\tEndereco: %s\n", Contatos[X].Nome, Contatos[X].Numero, Contatos[X].Endereco);
    }
}

void AjustarLista(int Modificado) { //Função responsável por reorganizar a lista de tal forma que contatos novos tenham espaço para serem adicionados.
    for(int X = Modificado; X < numContatos; X++) {
        Contatos[X] = Contatos[X+1];
    }
    numContatos--;
    Salvar();
}

void ModificarContato(int X, char* Nome, char* Endereco, int Numero) {
    strcpy(Contatos[X].Nome, Nome);
    strcpy(Contatos[X].Endereco, Endereco);
    Contatos[X].Numero = Numero;
    printf("\nO contato de numero %d foi modificado com sucesso.", Contatos[X].Numero);
    Salvar();
}

void AdicionarContato(char* Nome, char* Endereco, int Numero, int Invisivel) {
    strcpy(Contatos[numContatos].Nome, Nome);
    strcpy(Contatos[numContatos].Endereco, Endereco);
    Contatos[numContatos].nulo = 0;
    Contatos[numContatos].Numero = Numero;
    if(Invisivel != 1)
        printf("\nO contato de numero %d foi adicionado com sucesso.\n", Contatos[numContatos].Numero);

    numContatos++;
    Salvar();
}

void OrdenarLista(int Modo) {
    if(Modo == 1) {
        int aux = 0;
        int _numContatos = numContatos;
        struct Contato lista[500];

        while(aux < _numContatos) {
            int menorNumero = -1;
            int menorNumeroID = -1;
            for(int X = 0; X < numContatos; X++) {
                if(Contatos[X].Numero < menorNumero || menorNumero == -1) {
                    menorNumero = Contatos[X].Numero;
                    menorNumeroID = X;
                }
            }

            strcpy(lista[aux].Nome, Contatos[menorNumeroID].Nome);
            strcpy(lista[aux].Endereco, Contatos[menorNumeroID].Endereco);
            lista[aux].Numero = Contatos[menorNumeroID].Numero;

            aux++;
            AjustarLista(menorNumeroID);
        }

        for(int X = 0; X < _numContatos; X++) {
            AdicionarContato(lista[X].Nome, lista[X].Endereco, lista[X].Numero, 1);
            /*strcpy(Contatos[X].Nome, lista[X].Nome);
            strcpy(Contatos[X].Endereco, lista[X].Endereco);
            Contatos[X].Numero = lista[X].Numero;*/
        }
    }
    Salvar();
}

void Intro() {
    if(Iniciado == 0) {
       // Carregar();

        printf("Seja bem vindo a agenda telefonica 2000! Selecione uma opcao abaixo.");
        printf("\n1 - Listar Contatos");
        printf("\n2 - Adicionar Contato");
        printf("\n3 - Editar Contato");
        printf("\n4 - Remover Contato");
        printf("\n5 - Ordenar Lista\n\n");
    }
    Iniciado = 1;
}

int main() {
    Intro();

    while(1 == 1) {
        int Selecao = 0;
        scanf("%d", &Selecao);

        if(Selecao == 1)
            ListarContatos();

        else if(Selecao == 2) {
            char Nome[30];
            char Endereco[30];
            int Num = 0;

            getchar();
            printf("Nome: ");
            fgets (&Nome, 30, stdin);
            printf("Endereco: ");
            fgets (&Endereco, 30, stdin);
            printf("Numero: ");
            scanf("%d", &Num);

            int aux = 0;
            for(int X=0; X < numContatos; X++) {
                if(Contatos[X].Numero == Num) {
                    aux = 1;
                }
            }

            if(aux == 1) {
                printf("\nEste numero ja foi encontrado em sua agenda, por favor use a funcao de editar contatos caso queira modifica-lo.");
                continue;
            }

            strtok(Nome, "\n");
            strtok(Endereco, "\n");
            AdicionarContato(Nome, Endereco, Num, 0);
        }

        else if(Selecao == 3) {
            char Nome[30];
            char Endereco[30];
            int Num = 0;
            int base = 0;

            getchar();
            printf("Insira o numero telefonico de quem deseja modificar: ");
            scanf("%d", &base);

            int aux = 0;
            for(int X=0; X < numContatos; X++) {
                if(Contatos[X].Numero == base) {
                    aux = 1;

                    getchar();
                    printf("Insira um novo nome: ");
                    fgets (&Nome, 30, stdin);
                    printf("Insira um novo endereco: ");
                    fgets (&Endereco, 30, stdin);
                    printf("Insira um novo numero: ");
                    scanf("%d", &Num);

                    strtok(Nome, "\n");
                    strtok(Endereco, "\n");
                    ModificarContato(X, Nome, Endereco, Num);
                }
            }

            if(aux == 0) {
                printf("\nEste numero nao foi encontrado em sua agenda, retornando ao menu principal.");
            }
        }

        else if(Selecao == 4) {
            char Nome[30];
            char Endereco[30];
            int Num = 0;
            int base = 0;

            getchar();
            printf("Insira o numero telefonico de quem deseja remover: ");
            scanf("%d", &base);

            int aux = 0;
            for(int X=0; X < numContatos; X++) {
                if(Contatos[X].Numero == base) {
                    aux = 1;
                    int resposta = 0;

                    while(resposta != 1 && resposta != 2) {
                        printf("\nDeseja realmente remover %s de sua lista? Digite [1] para sim ou [2] para não.\nSua resposta: ", Contatos[X].Nome);
                        scanf("%d", &resposta);

                        if(resposta == 1)
                            AjustarLista(X);
                        else if(resposta == 2)
                            break;
                    }
                }
            }

            if(aux == 0) {
                printf("\nEste numero nao foi encontrado em sua agenda, retornando ao menu principal.");
            }
        }

        else if(Selecao == 5) {
            OrdenarLista(1);
            printf("Lista organizada com base nos numeros dos contatos.\n\n");
        }

        else {
            printf("Desculpe, voce digitou uma opcao invalida. Opcoes:");
            printf("\n1 - Listar Contatos");
            printf("\n2 - Adicionar Contato");
            printf("\n3 - Editar Contato");
            printf("\n4 - Remover Contato");
            printf("\n5 - Ordenar Lista\n\n");
        }
    }
}
