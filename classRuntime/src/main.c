/**********************************************************
Marco Antonio Marques   09/0124375
Alexandre Lucchesi      09/0104471
Rodrigo Marcal          10/0056946
Kabongo Patrick

 ******************* Includes *****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "class.h"
#include "auxiliar.h"
#include "class_loader.h"
#include "estruturas.h"
#include "execucao.h"
#define MAIN
#include "globais.h"
#undef MAIN
/*********************************************************/

int main(int argc, char *argv[])
{

    t_method_info * metodo; /* ponteiro para o metodo main */
    frame_execucao * frame; /* frame para execucao do metodo main */
    char nomearquivo[100];
    int i,j,tam_nome_arq;
    FILE* fp; /* ponteiro para arquivo que sera feita a leitura */
    int exibe_arquivo_class = 0;

    /* inicializa area heap */
    classlist = NULL;
    qtd_classes = 0;
    arrays = NULL;
    frames_em_execucao = malloc (sizeof (pilha_frame));
    frames_em_execucao->frame = NULL;
    frames_em_execucao->next = NULL;
    frame = NULL;
    metodo = NULL;

    if (argc == 1)    /* se o parametro nao for informado, o programa pede para o usuario digitar o nome do arquivo */
    {
        printf("\n\n\n");
        printf("JVM - Para executar, digite ./jvm nome_do_arquivo.class\n");
        printf("Se desejar ver o arquivo class montado antes da execucao,\n digite ./jvm nome_do_arquivo.class -e\n");
        printf("\n\n\n");
        exit(0);

    }
    else   /* caso contrario, o nome do parametro eh o nome do arquivo */
    {
        fp = fopen(argv[1], "rb");
        if ( (argc == 3)  && (strcmp(argv[2],"-e")==0))
            exibe_arquivo_class = 1;
    }

    /* localiza o caminho do arquivo, a ser usado quando for necessario abrir outro arquivo .class */
    strcpy(nomearquivo,argv[1]);
    tam_nome_arq = strlen(nomearquivo);

    for (i=tam_nome_arq-1 ; i>0 ; i--)
    {
        if (nomearquivo[i]=='/') break;
    }

    if (i!=0)
    {

        for(j=0; j<i+1; j++)
        {
            classpath[j]=nomearquivo[j];
        }
        classpath[j]='\0';
    }
    else
    {
        classpath[0]='\0';
    }

    if (!fp)
    {
        fprintf(stderr, "ERRO! Nao foi possivel abrir arquivo %s.\n",argv[1]);
        exit(FILE_ERROR);
    }

    /* le o arquivo class e o deixa montado na memória */
    leitura_classfile(fp);
    fclose(fp);

    if (exibe_arquivo_class==1) exibe_classfile(classlist[0].classe);

#ifdef DEBUG
    printf("\nDebug esta ativado. Deseja pausar execucao a cada operacao? [0/1] ");
    scanf("%d",&opcao_stop);
    fflush(stdin);
#endif

    /* executa clinit - se tiver */
    metodo = NULL;
    metodo = (t_method_info*) localizar_metodo_pelo_nome(classlist[0].classe,"<clinit>");
    if (metodo != NULL)
    {
        frame = (frame_execucao*) iniciar_frame (classlist[0].classe , metodo);
#ifdef DEBUG
        printf ("DEBUG=> Iniciada execucao do metodo clinit.\n");
#endif
        executar_metodo(frame);
    }

    metodo = NULL;
    /* executa metodo main */
    metodo = (t_method_info*) localizar_metodo_pelo_nome(classlist[0].classe,"main");
    if (metodo == NULL)
    {
        fprintf(stderr, "ERRO. Classe nao possui metodo main.\n");
        exit(ERROR);
    }
    else
    {
        frame = (frame_execucao*) iniciar_frame (classlist[0].classe , metodo);
#ifdef DEBUG
        printf ("DEBUG=> Iniciada execucao do metodo main.\n");
#endif
        executar_metodo(frame);
    }


    return EXIT_SUCCESS;
}



