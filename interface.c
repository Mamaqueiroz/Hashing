#include "interface.h"

int InterFace(char nomeArq[], t_elemento hashing[])
{
        FILE *fp;
        fp = fopen(nomeArq, "r");
        char nome[21];
        static int controle = 1;
        if(fp == NULL)
        {
                printf("Arquivo nao encontrado\n");
                return 0;
        }

        while(fscanf(fp,"%s ", nome) != EOF) //Vai abrir o arquivo com as frases e assim vamos chamar a função hashing
        {
                DeixarMin(nome);
                CriaIndiceInvertido(hashing, nome, controle);
        }
        fclose(fp);
        controle++;
        return 0;
}

void DeixarMin(char nome[])
{
        int i;
        for(i = 0; nome[i] != '\0'; i++)
        {
                if(nome[i] < 97)
                {
                        nome[i] += 32;
                }
        }
}

void Inicializar(t_elemento hashing[])
{
        int i;
        for(i = 0; i < 26; i++)
        {
                hashing[i].prox = NULL;
        }
}

void CriarArquivo(t_elemento hashing[])//cria o arquivo com todos as palavras
{
        FILE *ls;
        t_elemento * novo = (t_elemento *) malloc(sizeof(t_elemento));
        ls = fopen("teste.txt", "a+");

        int i;
        for(i = 0; i < 26; i++)//vai percorrer todo o hashing
        {
                if(hashing[i].prox != NULL){// Garantia de que ha algo
                        novo = hashing[i].prox;
                        fprintf(ls, "%s %d %d ", novo->palavra, novo->qnt_no_arquivo, novo->arquivo);// ira colocar no arquivo a primeira palavra
                        if(novo->lado != NULL)// e seu dados
                        {// se tiver mais de um arquivo com a mesma palavra ele ira checar e printar
                                t_elemento * auxiliar = (t_elemento *) malloc(sizeof(t_elemento));
                                auxiliar = novo->lado;
                                fprintf(ls, "%d %d", auxiliar->qnt_no_arquivo, auxiliar->arquivo);
                                while(auxiliar->lado != NULL)// ira verificar os n arquivos
                                {
                                        auxiliar = auxiliar->lado;
                                        fprintf(ls, "%d %d", auxiliar->qnt_no_arquivo, auxiliar->arquivo);
                                }

                        }
                        //Se a palavra nao aparecer em nenhuma outro arquivo printa a quebra de linha e verefica os outros
                        fprintf(ls,"\n");
                        while(novo->prox != NULL)//Se houver mais palavras com o mesmo indice ele ira olhar e repetir o processo de colocar no arquivo
                        {
                                novo = novo->prox;
                                fprintf(ls, "%s %d %d", novo->palavra, novo->qnt_no_arquivo, novo->arquivo);// ira colocar no arquivo a primeira palavra
                                if(novo->lado != NULL)// e seu dados
                                {// se tiver mais de um arquivo com a mesma palavra ele ira checar e printar
                                        t_elemento * auxiliar = (t_elemento *) malloc(sizeof(t_elemento));
                                        auxiliar = novo->lado;
                                        fprintf(ls, "%d %d", auxiliar->qnt_no_arquivo, auxiliar->arquivo);
                                        while(auxiliar->lado != NULL)// ira verificar os n arquivos
                                        {
                                                auxiliar = auxiliar->lado;
                                                fprintf(ls, "%d %d", auxiliar->qnt_no_arquivo, auxiliar->arquivo);
                                        }

                                }
                                fprintf(ls,"\n");
                        }
                }
        }
        fclose(ls);
        return;
}

void CriaIndiceInvertido(t_elemento hashing[], char nome[], int controle)
{
        int i;
        int indice;
        t_elemento * novo = (t_elemento *) malloc(sizeof(t_elemento));
        t_elemento * auxiliar = (t_elemento *) malloc(sizeof(t_elemento));
        int flag = 0;// flag para determinar quando um novo sera colocado quando houver duas palavras iguais em arquivos diferentes
        int flag_local = 0; // flag para colocar uma nova palavra quando tiver varias outras

        if(nome[0] < 97)
        {
                nome[0]+=32;
        }
        indice = nome[0] - 97;

        if((hashing[indice]).prox == NULL)//Quando a tabela estiver vazia no indice referente a letra
        {
                strcpy(novo->palavra, nome);//copia o novo para a estrutura
                novo->qnt_no_arquivo = 1;// inicia o contador da palavra;
                novo->arquivo = controle;//indica qual o arquivo oriundo
                novo->prox = NULL;
                novo->lado = NULL;
                hashing[indice].prox = novo;// liga o ponteiro do vetor para a celula
        }
        else//Agora a tabela tem alguma coisa
        {//Nessa situaçao ha duas possibildades, uma palavra com a mesma inicial, ou a mesma palavra

                auxiliar = (hashing[indice]).prox;//auxiliar recebe a primeira celula do ponteiro do vetor
                //comparar a palavra com auxiliar
                //se o nome for igual a palavra dentro da celula forem iguais e o controle tb ira qnt_no_arquivo ++
                //se o controle nao for igual, o ponteiro irmao sera criada para indicar que a palavra aparece em outro arquivo
                //se as palavras forem diferentes havera uma reordenação das celulas
                if(!strcmp(auxiliar->palavra, nome))// se as palavras forem iguais
                {
                        if(controle == auxiliar->arquivo)//e o arquivo for o mesmo
                        {
                                auxiliar->qnt_no_arquivo++;//incrementa a quantidade por arquivo;
                        }
                        else// se nao é um novo arquivo tem que colocar ao lado
                        {//alem disso tem que haver o teste para saber se ja ha algo ao lado pelo fato de serem N arquivos
                                if(auxiliar->lado == NULL)
                                {
                                        novo->qnt_no_arquivo = 1;
                                        novo->arquivo = controle;
                                        auxiliar->lado = novo;
                                }
                                else//se tiver algo do lado sera necessario checar ate qual ou ir ate o final
                                {
                                        while(auxiliar->lado != NULL)//vai checar onde tem um controle igual ou ira ate o final para criar uma nova
                                        {
                                                auxiliar = auxiliar->lado;
                                                if(auxiliar->arquivo == controle)//checa o arquivo em que esta
                                                {
                                                        auxiliar->qnt_no_arquivo ++;
                                                        break;//cancela o loop
                                                        flag = 1;// modifica a flag para indicar que a palavra ja foi incrementada
                                                }
                                        }
                                        if(flag == 0)//caso o auxiliar->lado seja null, pode ser o inicio de um novo arquivo
                                        {//e nesse arquivo pode ter uma palavra igual
                                                novo->qnt_no_arquivo = 1;
                                                novo->arquivo = controle;
                                                auxiliar->lado = novo;
                                        }
                                        flag = 0;
                                }
                        }

                }
                else//caso as palavras sejam diferentes
                {
                        //tem que implementar um loop para saber qual palavra veio primeiro
                        for(i = 1; nome[i]!= '\0' && auxiliar->palavra[i] != '\0';i++)
                        {
                                if(nome[i] > auxiliar->palavra[i])//a palavra que ira entrar é depois alfabeticamente
                                {//Duas possibilidades se o auxiliar -> prox = NULL ou diferente;
                                        if(auxiliar->prox == NULL)
                                        {
                                                strcpy(novo->palavra, nome);//copia o novo para a estrutura
                                                novo->qnt_no_arquivo = 1;// inicia o contador da palavra;
                                                novo->arquivo = controle;//indica qual o arquivo oriundo
                                                novo->prox = NULL;
                                                novo->lado = NULL;
                                                auxiliar->prox = novo;
                                                break;//apenas liga o auxiliar no novo e acaba o loop
                                        }
                                        else
                                        {//Aqui sera feito duas referencias para fins de comparaçao;
                                        //Exemplo aa ab ae
                                        //Sera colocado ac
                                        //auxiliar ta em aa e referencial ab
                                        //ai sera checado se ac é antes de ab(referencia)
                                        //se sim sera colocado ac entre
                                        //As comparaçoes so seram feitas com o referencial
                                                t_elemento * referencial = (t_elemento *) malloc(sizeof(t_elemento));
                                                referencial = auxiliar->prox;
                                                while(auxiliar->prox != NULL && flag_local == 0)//ira percorrer toda a lista do hashing
                                                //flag ira determinar se foi colocado ou nao a palavra antes do final
                                                //A condiçao desse loop é para evitar justamente o referencial ser nao ser NULL
                                                {//ate achar algo, e para ajudar sera posto uma novo referencial para o anterior
                                                        for(i = 1; nome[i]!= '\0' && referencial->palavra[i] != '\0';i++)
                                                        {
                                                                if(nome[i] < referencial->palavra[i])//a palavra q sera colocada
                                                                //esta entre auxiliar e referencial
                                                                {//tem que haver a modificação dos ponteiros
                                                                        strcpy(novo->palavra, nome);//copia o novo para a estrutura
                                                                        novo->qnt_no_arquivo = 1;// inicia o contador da palavra;
                                                                        novo->arquivo = controle;//indica qual o arquivo oriundo
                                                                        novo->prox = referencial;
                                                                        novo->lado = NULL;
                                                                        auxiliar->prox = novo;
                                                                        flag_local = 1;
                                                                        break;
                                                                }
                                                                else//a palavra a ser colocada sera depois da q esta
                                                                {
                                                                        auxiliar = auxiliar->prox;//avança os dois para checar
                                                                        referencial = referencial->prox;
                                                                        break;
                                                                }//Agora se o prox do auxiliar for NULL, significa q chegou ao fim
                                                        }//e a palavra nao foi adicionada logo tem q ser adicionada no final
                                                }
                                                if(flag_local == 0)//confirma se foi ou nao colocado alguma coisa antes
                                                {//se nao sera a ultima palavra
                                                        strcpy(novo->palavra, nome);//copia o novo para a estrutura
                                                        novo->qnt_no_arquivo = 1;// inicia o contador da palavra;
                                                        novo->arquivo = controle;//indica qual o arquivo oriundo
                                                        novo->prox = NULL;
                                                        novo->lado = NULL;
                                                        auxiliar->prox = novo;
                                                }
                                        }

                                }
                                else//se o nome for menor entao tudo que vem depois é menor logo é so colocar ele antes
                                {//nova celula q o prox sera o o auxiliar e o ponteiro do hash aponta para o novo;
                                        strcpy(novo->palavra, nome);//copia o novo para a estrutura
                                        novo->qnt_no_arquivo = 1;// inicia o contador da palavra;
                                        novo->arquivo = controle;//indica qual o arquivo oriundo
                                        novo->prox = auxiliar;
                                        novo->lado = NULL;
                                        hashing[indice].prox = novo;
                                        break;
                                }
                        }
                }

        }
}


//programa com coisas a mais a partir daqui
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

void Pesquisa()
{
        //O que eu tenho q pesquisar para saber qual o mais relevante
        //1. QUANTIDADE DE PALAVRAS QUE SAO DIFERENTES DENTRO DO ARQUIVO
        //2.QUANTIDADE DE ARQUIVO
        //3.QUANTIDADE DE VEZES Q A PALAVRA REPETE DENTRO DO ARQUIVO
        //Isso tem que ser feito para o conjunto de arquivos dentro de entrada.txt

        //SOLUÇAO
        //1. ACESSA O ARQUIVO DO INDICE GERADO(teste.txt) E PROCURA TODOS OS 1, 2, ... , N DENTRO DELE
        //2. PRIMEIRA LINHA DO ARQUIVO ENTRADA TE DAR ISSO
        //3. COM O ARQUIVO DE REFERENCIA DA PRA FAZER ISSO COM A  TESTE.TXT


        char busca[101];
        char pal_bus[21];
        int i, j = 0;

        scanf("%[^\n]s", busca);// ler a busca q a pessoa digitar, mais de uma palavra
        getchar();
        //separar as palavras

        while(arquivo <= qnt_arquivo)// ira repetir o processo para a quantidade x de arquivos
        {
                for(i = 0; busca[i] != '\0'; i++)// ira separar as palavras so q tem q ser executado isso para cada arquivo
                {
                        if(busca[i] != ' ')
                        {
                                pal_bus[j] = busca[i];
                                j++;
                        }
                        else
                        {
                                pal_bus[j] = '\0';// nesse momento a primeira palavra é encontrada
                                //funcao
                                //essa funcao vai me retornar um double que é a relevancia do arquivo
                                //tem q organizar essa relevancia de algum modo
                                //ISSO EU NAO SEI FAZER
                                //do maior para o menor
                                pal_bus[0] = '\0';//zera a palavra q eu estou buscando e parte para a  proxima
                                j = 0;

                        }
                }
        }
}
