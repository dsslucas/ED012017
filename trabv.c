/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Algoritmos e Programação de Computadores – 1/2017

Alunos: Lucas da Silva Souza, João Ricardo Ferreira Costa
Matriculas: 16/0013020 e 16/0009936
Turma: B
Versão do compilador: GCC 4.7.1

Descricao: Trabalho Obrigatorio 01.
Jogo de Batalha Naval entre dois players. */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define A 10 /*Mude este valor para mudar o tamanho do mapa. O padrão deste valor é 10, o que significa um mapa de tamanho 10 x 10*/

int fatorMult = A * A;
float maxEspeciais = 0.35; //Um mínimo de 12% de veículos (carros, cargueiros, etc) deve ser gerado ou então o gerador irá tentar novamente.

typedef struct Dados {
    int revelados;
    int EspeciaisGerados;
    int posicoes[A][A]; //Esta variavel irá guardar o "mapa" deste jogador.
    int visualizado[A][A];
    int ultX;
    int ultY;
} _Info;

/*IDs dos objetos no mapa:
1 = Objeto nulo / Espaço vazio
2 = Submarino (2 partes)
-> 21 = Submarino base
-> 22 = Submarino parte 2
3 = Cruzeiros (3 partes)
-> 31 = Cruzeiro base
-> 32 = Cruzeiro parte 2 (meio)
-> 33 = Cruzeiro final
4 = Cargueiros (4 partes)
-> 41 = Cargueiro base
-> 42 = Cargueiro parte 2
-> 43 = Cargueiro parte 3
-> 44 = Cargueiro final*/

int TamanhoProp(int propID) {
    int tamanhoProp = 1;
    if(propID == 2)
        tamanhoProp = 2;
    if(propID == 3)
        tamanhoProp = 3;
    if(propID == 4)
        tamanhoProp = 4;
    if(propID == 5)
        tamanhoProp = 2;
    return tamanhoProp;
}

struct Dados gerarBordas(struct Dados entrada) { //Assim as embarcações não poderão colidir.
    struct Dados teste = entrada;
    for(int X = 0; X < A; X++) {
        for(int Y = 0; Y < A; Y++) {
            if(teste.posicoes[X][Y] == 22 || teste.posicoes[X][Y] == 33 || teste.posicoes[X][Y] == 44 || teste.posicoes[X][Y] == 52)
                if(Y < A) teste.posicoes[X][Y + 1] = 2;
        }
    }
    return teste;
};

int verificarSpawn(struct Dados entrada, int propID, int X, int Y) {
    int Aux = 0;
    int tamanho = TamanhoProp(propID - 4);

    for(int Z = 0; Z < tamanho; Z++) {
        if(Y + Z >= A)
            return 0;
        if(entrada.posicoes[X][Y + Z] == -1) {
            Aux += 1;
        }
        else
            return 0;
    }
    if(Aux == tamanho)
        return 1;
    printf("Falhei aqui. X %d Y %d tamanho %d aux %d\n", X, Y, tamanho, Aux);
    return 0;
}

struct Dados gerarMapa(int ID) {
    struct Dados retorno;
    for(int X = 0; X < A; X++)
        for(int Y = 0; Y < A; Y++) {
            retorno.posicoes[X][Y] = -1; //Aqui inicializamos os valores da matriz.
            retorno.visualizado[X][Y] = 0;
            retorno.revelados = 0;
            retorno.EspeciaisGerados = 0;
            retorno.ultX = -1;
            retorno.ultY = -1;
        }
    for(int X = 0; X < A; X++) {
        for(int Y = 0; Y < A; Y++) {
            retorno = gerarBordas(retorno);
            if(retorno.posicoes[X][Y] != -1)
                continue;
            int num = rand() % (9 + 1);
            if(num >= 0 && num <= 5)
                retorno.posicoes[X][Y] = 1; //Gerar um espaço vazio neste quadrado.
            else {
                if(verificarSpawn(retorno, num, X, Y) == 1) {
                    if(num == 6) {
                        retorno.posicoes[X][Y] = 21;
                        retorno.posicoes[X][Y + 1] = 22;
                        retorno.EspeciaisGerados += 2;
                    }
                    else if(num == 7) {
                        retorno.posicoes[X][Y] = 31;
                        retorno.posicoes[X][Y + 1] = 32;
                        retorno.posicoes[X][Y + 2] = 33;
                        retorno.EspeciaisGerados += 3;
                    }
                    else if(num == 8) {
                        retorno.posicoes[X][Y] = 41;
                        retorno.posicoes[X][Y + 1] = 42;
                        retorno.posicoes[X][Y + 2] = 43;
                        retorno.posicoes[X][Y + 3] = 44;
                        retorno.EspeciaisGerados += 4;
                    }
                    else if(num == 9) {
                        retorno.posicoes[X][Y] = 51;
                        retorno.posicoes[X][Y + 1] = 52;
                        retorno.EspeciaisGerados += 2;
                    }
                    retorno = gerarBordas(retorno);
                }
            }
        }
    }
    for(int X = 0; X < A; X++)
        for(int Y = 0; Y < A; Y++)
            if(retorno.posicoes[X][Y] == -1)
                retorno.posicoes[X][Y] = 1; //Converte os espaços pulados (Devido as bordas) em espaços vazios, aceitos por funções.
    if(retorno.EspeciaisGerados > (maxEspeciais * fatorMult))
        retorno = gerarMapa(ID);
    return retorno;
}

void mostrarMapa(struct Dados entrada, int Secreto, int modoFinal, int ID) {
    if(Secreto == 1) {
        if(ID != -1) {
            printf("\nMapa do player %d\n\n", ID);
            printf("---------------------\n");
        }
        for(int X = 0; X < A; X++) {
            for(int Y = 0; Y < A; Y++) {
                if(entrada.visualizado[X][Y] == 1 || modoFinal == 1) {
                    if(entrada.posicoes[X][Y] == 21 || entrada.posicoes[X][Y] == 31 || entrada.posicoes[X][Y] == 41 || entrada.posicoes[X][Y] == 51)
                        printf("<|");
                    else if(entrada.posicoes[X][Y] == 22 || entrada.posicoes[X][Y] == 33 || entrada.posicoes[X][Y] == 44 || entrada.posicoes[X][Y] == 52)
                        printf(">|");
                    else if(entrada.posicoes[X][Y] == 32 || entrada.posicoes[X][Y] == 42 || entrada.posicoes[X][Y] == 43)
                        printf("=|");
                    else
                        printf(" |");
                }
                else
                    printf(" |");
            }
            printf("\n");
        }
    }
    else {
        for(int X = 0; X < A; X++) {
            for(int Y = 0; Y < A; Y++) {
                printf("%d|", entrada.posicoes[X][Y]);
            }
            printf("\n");
        }
    }
}

int main(){
    srand(time(NULL));
    _Info dados_Player1 = gerarMapa(1);
    _Info dados_Player2 = gerarMapa(2);
    printf("Bem vindo ao jogo de Batalha Naval! Siga as instrucoes abaixo:\n");
    printf("INSTRUCOES:\n- Este jogo deve ser jogado apenas com 2 pessoas;\n- Cada um dos jogadores devera dar coordenadas X e Y;\n");
    printf("- Nao podera haver repeticao de coordenadas;\n- Este tabuleiro ha 10 linhas e colunas;\n- Boa sorte!\n");

    int Turno = 0;
    int atkX = -1;
    int atkY = -1;
    int continuarLoop = 1;

    while(continuarLoop == 1) {
        atkX = -1;
        atkY = -1;
        struct Dados inimigoDados;
        struct Dados localDados;
        if(Turno == 0) {
            inimigoDados = dados_Player2;
            localDados = dados_Player1;
        }
        if(Turno == 1) {
            inimigoDados = dados_Player1;
            localDados = dados_Player2;
        }
        printf("\nTurno do player %d!\n", Turno + 1);
        mostrarMapa(inimigoDados, 1, 0, Turno == 1? 1 : 2);
        printf("---------------------\n");
        if(localDados.ultX >= 0) {
            printf("Sua ultima jogada foi em X %d Y %d", localDados.ultX, localDados.ultY);
            if(inimigoDados.posicoes[localDados.ultX][localDados.ultY] != 1 && inimigoDados.posicoes[localDados.ultX][localDados.ultY] != 2)
                printf(", encontrando parte de uma embarcacao.\n");
            else
                printf(", nao encontrando nenhuma parte de embarcacoes.\n");
        }
        while(1 == 1) {
            printf("Capitao, onde devemos atacar agora? Me passe as coordenadas!\nX: ");
            scanf("%d", &atkX);
            while(atkX < 0 || atkX > A - 1) {
                printf("Desculpe, nao entendi as coordenadas que me passou.\nX:");
                scanf("%d", &atkX);
            }
            printf("Y: ");
            scanf("%d", &atkY);
            while(atkY < 0 || atkY > A - 1) {
                printf("Desculpe, nao entendi as coordenadas que me passou.\nY:");
                scanf("%d", &atkY);
            }
            if(inimigoDados.visualizado[atkY][atkX] == 1) {
                printf("Senhor, devo alerta-lo que este alvo ja foi atacado! Por favor nos envie novas coordenadas!\n");
                continue;
            }
            localDados.ultX = atkY;
            localDados.ultY = atkX;
            break;
        }
        printf("Ataque realizado com sucesso!");
        inimigoDados.visualizado[atkY][atkX] = 1;
        if(inimigoDados.posicoes[atkY][atkX] != 1 && inimigoDados.posicoes[atkY][atkX] != 2 && inimigoDados.posicoes[atkY][atkX] != -1) {
            printf("Parece que acertamos algo, capitao!\n");
            inimigoDados.revelados++;
            if(inimigoDados.revelados == inimigoDados.EspeciaisGerados) {
                printf("\nO player %d ganhou, destruindo %d partes de embarcacoes!\n", (Turno + 1), inimigoDados.EspeciaisGerados);
                getchar();
                getchar();
                continuarLoop = 0;
                break;
            }
            else
                printf("Ate o momento voce tem %d pontos.", inimigoDados.revelados);
        }
        if(Turno == 0) { dados_Player2 = inimigoDados; Turno = 1; }
        else if(Turno == 1) { dados_Player1 = inimigoDados; Turno = 0; }
        continue;
    }
    printf("Mapa final - Player 1\n");
    mostrarMapa(dados_Player1, 1, 1, -1);
    printf("\n\nMapa final - Player 2\n");
    mostrarMapa(dados_Player2, 1, 1, -1);
}
