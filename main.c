#include "interface.h"

//O que tem que fazer aqui


//Tem que abrir um arquivo em que nele contem o nome dos outros arquivos
//O nome dos arquivos dentro do mestre deve ser aberto e cada um contem frases
//Essas frases devem ser analisadas e jogadas em uma tabela hashing
//Essa tabela hashing vai ser a que organiza as palavras em ordem alfabetica
//Hashing a ser implementado sera uma tabela de 26 espaços que seriam um vetor de ponteiros
//Cada ponteiro ira indicar para uma letra e apos isso sera processado uma função para ajustar a sequencia.


//Tem q ter uma estrutra para armazenar as palavras


int main()
{
        char nomeArq[30];
        int qnt;
        FILE *fl;
        t_elemento hashing[26];


        fl = fopen("entrada.txt", "r");
        if(fl == NULL)
        {
                printf("Arquivo de entrada nao encontrado\n");
                return 0;
        }
        fscanf(fl,"%d", &qnt);
        Inicializar(hashing);

        while(fscanf(fl,"%s",nomeArq) != EOF)
        {
                InterFace(nomeArq, hashing);
        }
        CriarArquivo(hashing);// cria o arquivo do indice invertido
        fclose(fl);
        //programa novo
        int decisao;

        printf("1.Pesquisa\n2.Mostrar tabela com indices invertidos\n");
        scanf("%d", &decisao);
        if(decisao == 1)
        {
                Pesquisa(qnt);
        }
        else
        {
                Mostrar();
        }

        return 0;
}
