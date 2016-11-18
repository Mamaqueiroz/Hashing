#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento
{
        char palavra[21];
        int qnt_no_arquivo;
        int arquivo;
        struct elemento * prox;
        struct elemento * lado;
}t_elemento;

int InterFace(char nomeArq[], t_elemento hashing[]);
void CriaIndiceInvertido(t_elemento hashing[], char nome[], int controle);
void CriarArquivo(t_elemento hashing[]);
void Inicializar(t_elemento hashing[]);
void DeixarMin(char nome[]);

//programa com coisas a mais a partir daqui
void Mostrar();
void Pesquisa();
