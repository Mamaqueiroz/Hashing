#include <stdio.h>
#include <string.h>
#include <math.h>

void Pesquisa()
{

        FILE *mi;//pega a quantidade de arquivos que contem
        mi = fopen("entrada.txt", "r");
        int n;
        fscanf(mi,"%d", n);
        fclose(mi);


        char busca[101];
        char auxiliar[21];
        int i, j = 0;
        //tem o caso de haver apenas uma palavra que um loop para distinguir as palavras com espaços nao sera o suficiente
        //Entao apos a tentativa de separar as palavras a leitura deve ser realizada novamente

        scanf("%[^\n]s", busca);//leitura de  mais de uma palavra;
        getchar();

        for(i = 0; busca[i] != '\0'; i++)// ira separar as palavras para depois abrir o arquivo;
        {
                if(busca[i] != ' ')// testa se ha um espaço o qual indicara o fim de uma palavra e o começo de outra
                {
                        auxiliar[j] = busca[i];//copia para a outra string
                        j++;
                }
                else{//se for igual a espaço, encerra a copia e manda a palavra para uma funçao que abre o arquivo
                        //e calcula qual a relevancia do arquivo para a busca
                        auxiliar[j] = '\0';
                        LeituraDoArq(auxiliar,n);//A busca sera executada e o print na tela sera feito pela propria funçao
                        auxiliar[0] = '\0';//Da um restart na palavra
                        j = 0;//E reinia a sua contagem

                }
        }
        auxiliar[j] = '\0';
        LeituraDoArq(auxiliar, n);
}

int LeituraDoArq(char busca[], int n)
{

        FILE *fp;
        char retirado[21];
        int rept, arquivo;
        double relevancia;

        fp = fopen("teste.txt", "r");

        while(fscanf(fp,"%s", retirado) != EOF)//pega a palavra do arquivo
        {
                if(!strcmp(retirado, busca))//compara com a primeira palavra que foi pesquisada
                {//se for igual sera efetuado o calculo de relevancia
                        while(fscanf(fp,"%d %d",&rept, &arquivo))//calcula a relevancia para cada par de numeros
                        {
                                relevancia =+ CalculoRelevancia(rept, n, 1);//funçao que gera a relevancia
                        }
                }
        }
        return
}

double CalculoRelevancia(int rept, int n, int aux)
{
        if(aux == 1)//calculo do w
        {
                return rept*(log(n)/n);
        }


}

void Mostrar()
{
        FILE *ed;
        char item[21];
        int rept, arquivo;

        ed = fopen("teste.txt", "r");

        while(fscanf(ed,"%s", item) != EOF)
        {
                printf("%s ", item);
                while(fscanf(ed, "%d %d", rept, arquivo))
                {
                        printf("%d %d ", rept,arquivo);
                }
        }
}

int main()
{

        int decisao;

        printf("1.Pesquisa\n2.Mostrar tabela com indices invertidos\n");
        scanf("%d", &decisao);
        if(decisao == 1)
        {
                Pesquisa();
        }
        else
        {
                Mostrar();
        }
        return 0;
}
