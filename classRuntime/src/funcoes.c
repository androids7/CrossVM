#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "estruturas.h"
#include "globais.h"
#include "class.h"
#include "funcoes.h"
#include "auxiliar.h"
#include "math.h"
#include "execucao.h"
#include "class_loader.h"

/*0x00*/
int nop (frame_execucao * frame)
{
    return 0;
}

/*0x01*/
/*insere NULO na pilha de operandos.*/
int aconst_null(frame_execucao * frame)
{

    u4 referencia = 0;
    int * nulo = malloc(sizeof(int));
    nulo = NULL;
    referencia = (u4)nulo;

    frame->pilha = inserir_na_pilha(frame->pilha,referencia);

    return 0;
}

/*0x02*/
/* insere -1 na pilha */
int iconst_m1 (frame_execucao * frame)
{

    u4 valor = -1;
    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    return 0;

}

/*0x03*/
/* insere 0 na pilha */
int iconst_0 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    return 0;

}

/*0x04*/
/* insere 1 na pilha */
int iconst_1 (frame_execucao * frame)
{

    u4 valor = 1;
    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    return 0;

}

/*0x05*/
/* insere 2 na pilha */
int iconst_2 (frame_execucao * frame)
{

    u4 valor = 2;
    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    return 0;

}

/*0x06*/
/* insere 3 na pilha */
int iconst_3 (frame_execucao * frame)
{

    u4 valor = 3;
    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    return 0;

}

/*0x07*/
/* insere 4 na pilha */
int iconst_4 (frame_execucao * frame)
{

    u4 valor = 4;
    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    return 0;

}

/*0x08*/
/* insere 5 na pilha */
int iconst_5 (frame_execucao * frame)
{

    u4 valor = 5;
    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    return 0;

}

/*0x09*/
/* insere 0 (long) na pilha */
int lconst_0 (frame_execucao * frame)
{

    u4 high_bytes = 0;
    u4 low_bytes = 0;

    frame->pilha = inserir_na_pilha (frame->pilha , low_bytes);
    frame->pilha = inserir_na_pilha (frame->pilha , high_bytes);

    return 0;

}

/*0x0a*/
/* insere 1 (long) na pilha */
int lconst_1 (frame_execucao * frame)
{

    u4 high_bytes = 0;
    u4 low_bytes  = 1;

    frame->pilha = inserir_na_pilha (frame->pilha , low_bytes);
    frame->pilha = inserir_na_pilha (frame->pilha , high_bytes);

    return 0;

}

/*0x0b*/
/* insere 0.0 na pilha */
int fconst_0 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    return 0;

}

/*0x0c*/
/* insere 1.0 na pilha */
int fconst_1 (frame_execucao * frame)
{

    u4 valor = 0x3F800000;
    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    return 0;

}

/*0x0d*/
/* insere 2.0 na pilha */
int fconst_2 (frame_execucao * frame)
{

    u4 valor = 0x40000000;
    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    return 0;

}


/*0x0e*/
/* insere 0.0 na pilha */
int dconst_0 (frame_execucao * frame)
{

    u4 aux1 = 0 , aux2 = 0;
    long long l = 0 , valor = 0;
    double  d = 0;
    tipo_double valor_double;

    d = (double)0.0;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/*0x0f*/
/* insere 1.0 na pilha */
int dconst_1 (frame_execucao * frame)
{

    u4 aux1 = 0 , aux2 = 0;
    long long l = 0 , valor = 0;
    double  d = 0;
    tipo_double valor_double;

    d = (double)1.0;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/*0x10*/
/*insere um byte na pilha */
int bipush (frame_execucao * frame)
{

    u4 valor;
    int valor_int = 0 ;

    valor = frame->code[frame->pc++];

    valor_int=(int)valor;

    frame->pilha = inserir_na_pilha (frame->pilha, (u4)valor_int);

    return 0;

}

/*0x11*/
/*insere valor recebido na pilha */
int sipush (frame_execucao * frame)
{

    u1 byte1=0 , byte2=0;
    u4 valor = 0;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    valor =  (byte1 << 8) | byte2;

    frame->pilha = inserir_na_pilha (frame->pilha, valor);

    return 0;

}


/*0x12*/
/*insere do constant_pool na pilha */
int ldc (frame_execucao * frame)
{

    u1 * string;
    u2 indice;
    u4 valor;
    float valor_float;

    indice=frame->code[frame->pc++];

    switch (frame->constant_pool[indice-1].tag)
    {

        /* se do tipo int */
    case 3:
        valor = frame->constant_pool[indice-1].info.integer_info.bytes;
        valor=(int)valor;
#ifdef DEBUG
        printf ("     => valor inteiro sera empilhado.\n");
#endif
        frame->pilha = inserir_na_pilha(frame->pilha,valor);
        break;

        /* se do tipo float */
    case 4:
        valor = frame->constant_pool[indice-1].info.float_info.bytes;
        valor_float = converte_para_float(valor);
#ifdef DEBUG
        printf("     => valor float (%f) sera empilhado.\n",valor_float);
#endif
        frame->pilha = inserir_na_pilha(frame->pilha,valor);
        break;

        /* se do tipo string */
    case 8:
        indice = frame->constant_pool[indice-1].info.string_info.string_index;
        string = frame->constant_pool[indice-1].info.utf8_info.bytes;
        valor = (u4)string;  /* pega o endereco da string para colocar na pilha */
#ifdef DEBUG
        printf ("     => referencia para string sera empilhada. (%s)\n",string);
#endif
        frame->pilha = inserir_na_pilha(frame->pilha,valor);
        break;

    default:
        fprintf(stderr,"ERRO em ldc. Tipo de dado nao encontrado.\n");
        exit(ERROR);
        break;

    }

    return 0;
}

/*0x13*/
/*insere do constant_pool na pilha */
int ldc_w (frame_execucao * frame)
{

    u1 * string;
    u2 indice = 0;
    u4 byte1=0,byte2=0;
    u4 valor=0;

    /* recupera valor que sera empilhado */
    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;

    switch (frame->constant_pool[indice-1].tag)
    {

        /* se do tipo int */
    case 3:
        valor = frame->constant_pool[indice-1].info.integer_info.bytes;
        valor=(int)valor;
#ifdef DEBUG
        printf ("     => valor inteiro sera empilhado.\n");
#endif
        frame->pilha = inserir_na_pilha(frame->pilha,valor);
        break;

        /* se do tipo float */
    case 4:
        valor = frame->constant_pool[indice-1].info.float_info.bytes;
        valor=(float)valor;
#ifdef DEBUG
        printf ("     => valor float sera empilhado.\n");
#endif
        frame->pilha = inserir_na_pilha(frame->pilha,valor);
        break;

        /* se do tipo string */
    case 8:
        indice = frame->constant_pool[indice-1].info.string_info.string_index;
        string = frame->constant_pool[indice-1].info.utf8_info.bytes;
        valor = (u4)string;  /* pega o endereco da string para colocar na pilha */
#ifdef DEBUG
        printf("     => referencia para string sera empilhada. (%s)\n",string);
#endif
        frame->pilha = inserir_na_pilha(frame->pilha,valor);
        break;

    default:
        fprintf(stderr,"ERRO em ldc. Tipo de dado desconhecido.\n");
        exit(ERROR);
        break;

    }

    return 0;
}

/*0x14*/
/*coloca long ou double do constant_pool na pilha*/
int ldc2_w(frame_execucao * frame)
{
    u2 indice;
    u4 byte1=0,byte2=0;
    u4 high_bytes,low_bytes;

    /* recupera valor que sera empilhado */
    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;


    high_bytes = frame->constant_pool[indice-1].info.long_info.high_bytes;
    low_bytes  = frame->constant_pool[indice-1].info.long_info.low_bytes;

#ifdef DEBUG
    printf ("     => valor long/double sera empilhado.\n");
#endif
    frame->pilha = inserir_na_pilha(frame->pilha,low_bytes);
    frame->pilha = inserir_na_pilha(frame->pilha,high_bytes);

    return 0;

}

/*0x15*/
/*empilha valor das variaveis locais no indice recebido */
int iload (frame_execucao * frame)
{

    u4 index = 0, valor = 0;
    index = frame->code[frame->pc++];
    valor = frame->variaveis_locais[index];
#ifdef DEBUG
    printf ("     => retira de var.locais [indice %u] para empilhar.\n",index);
#endif
    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    return 0;
}

/*0x16*/
/* empilha long do vetor de variaveis locais */
int lload (frame_execucao * frame)
{

    u4 index = 0, valor = 0;
    index = frame->code[frame->pc++];

    valor = frame->variaveis_locais[index+1];
#ifdef DEBUG
    printf ("     => retira de var.locais [indice %u] para empilhar.\n",index+1);
#endif
    frame->pilha = inserir_na_pilha(frame->pilha,valor);
    valor = frame->variaveis_locais[index];
#ifdef DEBUG
    printf ("     => retira de var.locais [indice %u] para empilhar.\n",index);
#endif
    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    return 0;

}

/*0x17*/
/*empilha float do vetor de variaveis locais*/
int fload (frame_execucao * frame)
{

    u4 index = 0, valor = 0;
    index = frame->code[frame->pc++];
    valor = frame->variaveis_locais[index];
#ifdef DEBUG
    printf("     => retira de var.locais [indice %u] para empilhar.\n",index);
#endif
    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    return 0;
}

/*0x18*/
/* empilha double do vetor de variaveis locais */
int dload (frame_execucao * frame)
{

    u4 index = 0, valor = 0;
    index = frame->code[frame->pc++];

    valor = frame->variaveis_locais[index+1];
#ifdef DEBUG
    printf ("     => retira de var.locais [indice %u] para empilhar.\n",index+1);
#endif
    frame->pilha = inserir_na_pilha(frame->pilha,valor);
    valor = frame->variaveis_locais[index];
#ifdef DEBUG
    printf("     => retira de var.locais [indice %u] para empilhar.\n",index);
#endif
    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    return 0;

}


/*0x19*/
/* empilha referencia que esta na variavel local */
int aload(frame_execucao * frame)
{

    u4 referencia = 0, indice = 0;
    indice = frame->code[frame->pc++];
    referencia = frame->variaveis_locais[indice];
#ifdef DEBUG
    printf ("     => retira referencia de var.locais [indice %u] para empilhar.\n",indice);
#endif
    frame->pilha = inserir_na_pilha(frame->pilha,referencia);
    return 0;

}

/* 0x1a */
/* Pega o valor da posição 0 no vetor de var.locais e coloca na pilha */
int iload_0 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[0];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x1b */
/* Pega o valor da posição 1 no vetor de var.locais e coloca na pilha */
int iload_1 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[1];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x1c */
/* Pega o valor da posição 2 no vetor de var.locais e coloca na pilha */
int iload_2 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[2];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x1d */
/* Pega o valor da posição 3 no vetor de var.locais e coloca na pilha */
int iload_3 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[3];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x1e */
/* Pega o long da posição 0 e 1 no vetor de var.locais e coloca na pilha */
int lload_0 (frame_execucao * frame)
{

    u4 valor = 0;
    valor = frame->variaveis_locais[1];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);
    valor = frame->variaveis_locais[0];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x1f */
/* Pega o long da posição 1 e 2 no vetor de var.locais e coloca na pilha */
int lload_1 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[2];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);
    valor = frame->variaveis_locais[1];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x20 */
/* Pega o long da posição 2 e 3 no vetor de var.locais e coloca na pilha */
int lload_2 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[3];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);
    valor = frame->variaveis_locais[2];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}


/* 0x21 */
/* Pega o long da posição 3 e 4 no vetor de var.locais e coloca na pilha */
int lload_3 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[4];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);
    valor = frame->variaveis_locais[3];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x22 */
/* Pega o float da posição 0 no vetor de var.locais e coloca na pilha */
int fload_0 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[0];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x23 */
/* Pega o float da posição 1 no vetor de var.locais e coloca na pilha */
int fload_1 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[1];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x24 */
/* Pega o float da posição 2 no vetor de var.locais e coloca na pilha */
int fload_2 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[2];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x25 */
/* Pega o float da posição 3 no vetor de var.locais e coloca na pilha */
int fload_3 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[3];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/*0x26 */
/* Pega o valor da posição 0 e posição 1 no vetor de var.locais (um double) e coloca na pilha */
int dload_0 (frame_execucao * frame)
{

    u4 valor1;
    u4 valor2;

    valor1 = frame->variaveis_locais[0];
    valor2 = frame->variaveis_locais[1];

    frame->pilha =  inserir_na_pilha (frame->pilha, valor2);
    frame->pilha =  inserir_na_pilha (frame->pilha, valor1);

    return 0;
}

/*0x27 */
/* Pega o valor da posição 1 e posição 2 no vetor de var.locais (um double) e coloca na pilha */
int dload_1 (frame_execucao * frame)
{

    u4 valor1;
    u4 valor2;

    valor1 = frame->variaveis_locais[1];
    valor2 = frame->variaveis_locais[2];

    frame->pilha =  inserir_na_pilha (frame->pilha, valor2);
    frame->pilha =  inserir_na_pilha (frame->pilha, valor1);

    return 0;
}

/*0x28 */
/* Pega o valor da posição 2 e posição 3 no vetor de var.locais (um double) e coloca na pilha */
int dload_2 (frame_execucao * frame)
{

    u4 valor1;
    u4 valor2;

    valor1 = frame->variaveis_locais[2];
    valor2 = frame->variaveis_locais[3];

    frame->pilha =  inserir_na_pilha (frame->pilha, valor2);
    frame->pilha =  inserir_na_pilha (frame->pilha, valor1);

    return 0;
}

/*0x29 */
/* Pega o valor da posição 0 e posição 1 no vetor de var.locais (um double) e coloca na pilha */
int dload_3 (frame_execucao * frame)
{

    u4 valor1;
    u4 valor2;

    valor1 = frame->variaveis_locais[3];
    valor2 = frame->variaveis_locais[4];

    frame->pilha =  inserir_na_pilha (frame->pilha, valor2);
    frame->pilha =  inserir_na_pilha (frame->pilha, valor1);

    return 0;
}


/* 0x2a */
/* Pega o valor da posição 0 no vetor de var.locais e coloca na pilha */
int aload_0 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[0];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x2b */
/* Pega o valor da posição 1 no vetor de var.locais e coloca na pilha */
int aload_1 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[1];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x2c */
/* Pega o valor da posição 2 no vetor de var.locais e coloca na pilha */
int aload_2 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[2];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x2d */
/* Pega o valor da posição 2 no vetor de var.locais e coloca na pilha */
int aload_3 (frame_execucao * frame)
{

    u4 valor;
    valor = frame->variaveis_locais[3];
    frame->pilha =  inserir_na_pilha (frame->pilha, valor);

    return 0;
}

/* 0x2e */
/* Tira uma referencia de um array de inteiros e  um indice */
/* Empilha o valor que esta no array no indice dado */
int iaload(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    int * array_inteiro;

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em iaload. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 10)
    {
        fprintf(stderr,"ERRO em iaload. Array nao eh inteiro.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em iaload. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_inteiro = array->array;
    valor = array_inteiro[indice];
    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    return 0;

}

/* 0x2f */
/* Tira uma referencia de um array de longs e  um indice */
/* Empilha o valor que esta no array no indice dado */
int laload(frame_execucao * frame)
{

    u4 indice = 0 , referencia = 0;
    u4 aux1,aux2;
    array * array;
    long long * array_long , valor_long;

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*) referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em laload. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 11)
    {
        fprintf(stderr,"ERRO em laload. Array nao eh long.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em laload. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_long = array->array;
    valor_long = array_long[indice];

    aux1 = valor_long & 0x0000FFFF;
    valor_long>>=32;
    aux2 = valor_long;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}


/* 0x30 */
/* Tira uma referencia de um array de floats e  um indice */
/* Empilha o valor deste array no indice dado */
int faload(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    float * array_float;

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em faload. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 6)
    {
        fprintf(stderr,"ERRO em faload. Array nao eh float.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em faload. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_float = array->array;
    valor = array_float[indice];
    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    return 0;

}

/* 0x31 */
/* Tira uma referencia de um array de doubles e  um indice */
/* Empilha o valor deste array no indice dado */
int daload(frame_execucao * frame)
{

    u4 indice = 0 , referencia = 0,aux1,aux2;
    array * array;
    double * array_double,d,vl_double;
    long long valor,l;
    tipo_double valor_double;

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em daload. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 7)
    {
        fprintf(stderr,"ERRO em daload. Array nao eh double.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em daload. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_double = array->array;
    vl_double = array_double[indice];

    d = (double)vl_double;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/*0x32*/
/* carrega valor de um array */
int aaload (frame_execucao * frame)
{

    u4 index = 0, referencia = 0, valor = 0;
    array * array;
    u4 * array_u4;

    frame->pilha = retirar_da_pilha(frame->pilha,&index);

    frame->pilha = retirar_da_pilha(frame->pilha,&referencia);

    array = (struct tipo_array*)referencia;

    if (array->tipo_array == 12)
    {
        array_u4 = array->array;
        valor = array_u4[index];
        frame->pilha = inserir_na_pilha (frame->pilha,valor);
    }

    return 0;

}

/* 0x33 */
/* Tira uma referencia de um array de boolean/byte e  um indice */
/* Empilha o valor deste array no indice dado */
int baload(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    u1 * array_byte;

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*) referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em baload. NullPointerException.\n");
        exit(ERROR);
    }

    if ((array->tipo_array != 4)&&(array->tipo_array != 8))
    {
        fprintf(stderr,"ERRO em baload. Array nao eh byte/boolean.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em baload. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_byte = array->array;
    valor = array_byte[indice];
    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    return 0;

}

/* 0x34 */
/* Tira uma referencia de um array de char e  um indice */
/* Empilha o valor deste array no indice dado */
int caload(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    char * array_char;

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*) referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em caload. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 5)
    {
        fprintf(stderr,"ERRO em caload. Array nao eh char.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em caload. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_char = array->array;
    valor = array_char[indice];
    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    return 0;

}

/* 0x35 */
/* Tira uma referencia de um array de short e  um indice */
/* Empilha o valor deste array no indice dado */
int saload(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    short * array_short;

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*) referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em saload. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 9)
    {
        fprintf(stderr,"ERRO em saload. Array nao eh short.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em saload. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_short = array->array;
    valor = array_short[indice];
    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    return 0;

}

/*0x36*/
/* tira inteiro da pilha e coloca no vetor de variaveis locais */
int istore (frame_execucao * frame)
{

    u4 index=0 , valor = 0;

    index = frame->code[frame->pc++];
    frame->pilha = retirar_da_pilha (frame->pilha , &valor);
    frame->variaveis_locais[index] = valor;

    return 0;

}

/*0x37*/
/* tira long da pilha e coloca no vetor de variaveis locais */
int lstore (frame_execucao * frame)
{

    u4 index=0 , valor = 0;

    index = frame->code[frame->pc++];
    frame->pilha = retirar_da_pilha (frame->pilha , &valor);
    frame->variaveis_locais[index] = valor;
    valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha , &valor);
    frame->variaveis_locais[index+1] = valor;

    return 0;
}

/*0x38*/
/* tira float da pilha e coloca no vetor de variaveis locais */
int fstore (frame_execucao * frame)
{

    u4 index=0 , valor = 0;

    index = frame->code[frame->pc++];
    frame->pilha = retirar_da_pilha (frame->pilha , &valor);
    frame->variaveis_locais[index] = valor;

    return 0;

}

/*0x39*/
/* tira double da pilha e coloca no vetor de variaveis locais */
int dstore (frame_execucao * frame)
{

    u4 index=0 , valor = 0;

    index = frame->code[frame->pc++];
    frame->pilha = retirar_da_pilha (frame->pilha , &valor);
    frame->variaveis_locais[index] = valor;
    valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha , &valor);
    frame->variaveis_locais[index+1] = valor;

    return 0;
}

/*0x3a*/
/* guarda referencia em uma variavel local indicada */
int astore (frame_execucao * frame)
{

    u4 referencia = 0 , indice = 0;

    indice = frame->code[frame->pc++];

    /* tira referencia da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&referencia);

    frame->variaveis_locais[indice] = referencia;

    return 0;

}

/* 0x3b */
/* Retira da pilha e coloca na posição 1 do vetor */
int istore_0 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[0] = valor;


    return 0;
}

/* 0x3c */
/* Retira da pilha e coloca na posição 1 do vetor */
int istore_1 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[1] = valor;


    return 0;
}

/* 0x3d */
/* Retira da pilha e coloca na posição 2 do vetor */
int istore_2 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[2] = valor;

    return 0;
}

/* 0x3e */
/* Retira da pilha e coloca na posição 3 do vetor */
int istore_3 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[3] = valor;

    return 0;
}


/* 0x3f */
/* Retira da pilha um long e coloca nas posicoes 0 e 1 do vetor */
int lstore_0 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[0] = valor;
    valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[1] = valor;

    return 0;
}

/* 0x40 */
/* Retira da pilha um long e coloca nas posicoes 1 e 2 do vetor */
int lstore_1 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[1] = valor;
    valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[2] = valor;

    return 0;
}

/* 0x41 */
/* Retira da pilha um long e coloca nas posicoes 2 e 3 do vetor */
int lstore_2 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[2] = valor;
    valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[3] = valor;

    return 0;
}

/* 0x42 */
/* Retira da pilha um long e coloca nas posicoes 3 e 4 do vetor */
int lstore_3 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[3] = valor;
    valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[4] = valor;

    return 0;
}

/* 0x43 */
/* Retira float da pilha e coloca na posição 1 do vetor */
int fstore_0 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[0] = valor;


    return 0;
}

/* 0x44 */
/* Retira float da pilha e coloca na posição 1 do vetor */
int fstore_1 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[1] = valor;


    return 0;
}

/* 0x45 */
/* Retira da pilha e coloca na posição 2 do vetor */
int fstore_2 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[2] = valor;

    return 0;
}

/* 0x46 */
/* Retira da pilha e coloca na posição 3 do vetor */
int fstore_3 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[3] = valor;

    return 0;
}

/* 0x47 */
/* Retira da pilha um double e coloca nas posicoes 0 e 1 do vetor */
int dstore_0 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[0] = valor;
    valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[1] = valor;

    return 0;
}

/* 0x48 */
/* Retira da pilha um double e coloca nas posicoes 1 e 2 do vetor */
int dstore_1 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[1] = valor;
    valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[2] = valor;

    return 0;
}

/* 0x49 */
/* Retira da pilha um double e coloca nas posicoes 2 e 3 do vetor */
int dstore_2 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[2] = valor;
    valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[3] = valor;

    return 0;
}

/* 0x4a */
/* Retira da pilha um double e coloca nas posicoes 3 e 4 do vetor */
int dstore_3 (frame_execucao * frame)
{

    u4 valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[3] = valor;
    valor = 0;
    frame->pilha = retirar_da_pilha (frame->pilha, &valor);
    frame->variaveis_locais[4] = valor;

    return 0;
}


/* 0x4b */
/* Tira uma referencia da pilha e coloca na posição 0 do vetor de variaveis locais */
int astore_0(frame_execucao * frame)
{

    u4 valor;
    frame->pilha = retirar_da_pilha(frame->pilha , &valor);
    frame->variaveis_locais[0] = valor;

    return 0;

}

/* 0x4c */
/* Tira uma referencia da pilha e coloca na posição 1 do vetor de variaveis locais */
int astore_1(frame_execucao * frame)
{

    u4 valor;
    frame->pilha = retirar_da_pilha(frame->pilha , &valor);
    frame->variaveis_locais[1] = valor;

    return 0;

}

/* 0x4d */
/* Tira uma referencia da pilha e coloca na posição 2 do vetor de variaveis locais */
int astore_2(frame_execucao * frame)
{

    u4 valor;
    frame->pilha = retirar_da_pilha(frame->pilha , &valor);
    frame->variaveis_locais[2] = valor;

    return 0;

}

/* 0x4e */
/* Tira uma referencia da pilha e coloca na posição 3 do vetor de variaveis locais */
int astore_3(frame_execucao * frame)
{

    u4 valor;
    frame->pilha = retirar_da_pilha(frame->pilha , &valor);
    frame->variaveis_locais[3] = valor;

    return 0;

}

/* 0x4f */
/* Tira uma referencia de um array de inteiros, um indice e um valor */
/* Colocar o valor na posição indicada no array dado */
int iastore(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    int * array_inteiro;

    /* retira valor */
    frame->pilha = retirar_da_pilha(frame->pilha , &valor);

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em iastore. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 10)
    {
        fprintf(stderr,"ERRO em iastore. Array nao eh inteiro.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em iastore. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_inteiro = array->array;
    array_inteiro[indice] = valor;

    return 0;

}

/* 0x50 */
/* Tira uma referencia de um array de longs, um indice e um valor */
/* Colocar o valor na posição indicada no array dado */
int lastore(frame_execucao * frame)
{

    u4 indice = 0  , referencia = 0,high,low;
    array * array;
    long long * array_long,valor_long;

    /* retira valor */
    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor_long = high;
    valor_long<<=32;
    valor_long|=low;

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em lastore. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 11)
    {
        fprintf(stderr,"ERRO em lastore. Array nao eh long.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em lastore. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_long = array->array;
    array_long[indice] = valor_long;

    return 0;

}


/* 0x51 */
/* Tira uma referencia de um array de floats, um indice e um valor */
/* Colocar o valor na posição indicada no array dado */
int fastore(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    float * array_float;

    /* retira valor */
    frame->pilha = retirar_da_pilha(frame->pilha , &valor);

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em fastore. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 6)
    {
        fprintf(stderr,"ERRO em fastore. Array nao eh float.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em fastore. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_float = array->array;
    array_float[indice] = valor;

    return 0;

}

/* 0x52 */
/* Tira uma referencia de um array de doubles, um indice e um valor */
/* Colocar o valor na posição indicada no array dado */
int dastore(frame_execucao * frame)
{

    u4 indice = 0  , referencia = 0, high,low;
    array * array;
    double * array_double,valor_double;
    long long valor_long;

    /* retira valor */
    frame->pilha = retirar_da_pilha(frame->pilha , &high);
    frame->pilha = retirar_da_pilha(frame->pilha , &low);

    valor_long = high;
    valor_long<<=32;
    valor_long|=low;

    valor_double = converte_para_double(valor_long);

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em lastore. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 7)
    {
        fprintf(stderr,"ERRO em lastore. Array nao eh double.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em lastore. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_double = array->array;
    array_double[indice] = valor_double;


    return 0;

}

/* 0x53 */
/* Tira uma referencia de um array de referencias, um indice e um valor */
/* Colocar o valor na posição indicada no array dado */
int aastore(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    u4 * array_u4;

    /* retira valor */
    frame->pilha = retirar_da_pilha(frame->pilha , &valor);

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em aastore. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 12)
    {
        fprintf(stderr,"ERRO em aastore. Array nao eh referencia.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em aastore. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_u4 = array->array;
    array_u4[indice] = valor;

    return 0;

}


/* 0x54 */
/* Tira uma referencia de um array de byte/boolean, um indice e um valor */
/* Colocar o valor na posição indicada no array dado */
int bastore(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    u1 * array_byte;

    /* retira valor */
    frame->pilha = retirar_da_pilha(frame->pilha , &valor);

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em bastore. NullPointerException.\n");
        exit(ERROR);
    }

    if ((array->tipo_array != 4)&&(array->tipo_array!=8))
    {
        fprintf(stderr,"ERRO em bastore. Array nao eh boolean/byte.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em bastore. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_byte = array->array;
    array_byte[indice] = valor;

    return 0;

}

/* 0x55 */
/* Tira uma referencia de um array de char, um indice e um valor */
/* Colocar o valor na posição indicada no array dado */
int castore(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    char * array_char;

    /* retira valor */
    frame->pilha = retirar_da_pilha(frame->pilha , &valor);

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em castore. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 5)
    {
        fprintf(stderr,"ERRO em castore. Array nao eh char.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em bastore. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_char = array->array;
    array_char[indice] = valor;

    return 0;

}

/* 0x56 */
/* Tira uma referencia de um array de short, um indice e um valor */
/* Colocar o valor na posição indicada no array dado */
int sastore(frame_execucao * frame)
{

    u4 indice = 0  , valor = 0, referencia = 0;
    array * array;
    short * array_short;

    /* retira valor */
    frame->pilha = retirar_da_pilha(frame->pilha , &valor);

    /* retira indice */
    frame->pilha = retirar_da_pilha(frame->pilha , &indice);

    /* retira endereço do array */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    array = (struct tipo_array*)referencia;

    if (array==NULL)
    {
        fprintf(stderr,"ERRO em sastore. NullPointerException.\n");
        exit(ERROR);
    }

    if (array->tipo_array != 9)
    {
        fprintf(stderr,"ERRO em sastore. Array nao eh short.\n");
        exit(ERROR);
    }

    if (indice > array->tam_array-1)
    {
        fprintf(stderr,"ERRO em sastore. ArrayIndexOutOfBoundsException.\n");
        exit(ERROR);
    }

    array_short = array->array;
    array_short[indice] = valor;

    return 0;

}

/*0x57*/
/*retira o topo da pilha */
int pop (frame_execucao * frame)
{

    u4 valor;
    frame->pilha = retirar_da_pilha(frame->pilha,&valor);
    return 0;
}


/* 0x59 */
/* Duplica topo da pilha */
int dup(frame_execucao * frame)
{

    u4 valor;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no dup. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor);

    frame->pilha = inserir_na_pilha (frame->pilha , valor);
    frame->pilha = inserir_na_pilha (frame->pilha , valor);

    return 0;
}

/* 0x5a */
/* Duplica topo da pilha */
int dup_x1 (frame_execucao * frame)
{

    u4 valor1=0, valor2=0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no dup_x1. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);

    frame->pilha = inserir_na_pilha (frame->pilha , valor1);
    frame->pilha = inserir_na_pilha (frame->pilha , valor2);
    frame->pilha = inserir_na_pilha (frame->pilha , valor1);

    return 0;
}

/* 0x5a */
/* Duplica topo da pilha */
int dup_x2 (frame_execucao * frame)
{

    u4 valor1=0, valor2=0, valor3=0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no dup_x1. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor3);

    frame->pilha = inserir_na_pilha (frame->pilha , valor1);
    frame->pilha = inserir_na_pilha (frame->pilha , valor3);
    frame->pilha = inserir_na_pilha (frame->pilha , valor2);
    frame->pilha = inserir_na_pilha (frame->pilha , valor1);

    return 0;
}

/* 0x5c */
/* Duplica topo da pilha */
int dup2 (frame_execucao * frame)
{

    u4 valor1=0, valor2=0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no dup_x1. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);

    frame->pilha = inserir_na_pilha (frame->pilha , valor2);
    frame->pilha = inserir_na_pilha (frame->pilha , valor1);
    frame->pilha = inserir_na_pilha (frame->pilha , valor2);
    frame->pilha = inserir_na_pilha (frame->pilha , valor1);

    return 0;
}

/* 0x5a */
/* Duplica topo da pilha */
int dup2_x1 (frame_execucao * frame)
{

    u4 valor1=0, valor2=0, valor3=0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no dup_x1. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor3);

    frame->pilha = inserir_na_pilha (frame->pilha , valor2);
    frame->pilha = inserir_na_pilha (frame->pilha , valor1);
    frame->pilha = inserir_na_pilha (frame->pilha , valor3);
    frame->pilha = inserir_na_pilha (frame->pilha , valor2);
    frame->pilha = inserir_na_pilha (frame->pilha , valor1);

    return 0;
}


/* 0x5a */
/* Duplica topo da pilha */
int dup2_x2 (frame_execucao * frame)
{

    u4 valor1=0, valor2=0, valor3=0, valor4=0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no dup_x1. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor3);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor4);

    frame->pilha = inserir_na_pilha (frame->pilha , valor2);
    frame->pilha = inserir_na_pilha (frame->pilha , valor1);
    frame->pilha = inserir_na_pilha (frame->pilha , valor4);
    frame->pilha = inserir_na_pilha (frame->pilha , valor3);
    frame->pilha = inserir_na_pilha (frame->pilha , valor2);
    frame->pilha = inserir_na_pilha (frame->pilha , valor1);

    return 0;
}

/* 0x5f */
/* Troca topo da pilha */
int swap (frame_execucao * frame)
{

    u4 valor1=0, valor2=0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no swap. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);

    frame->pilha = inserir_na_pilha (frame->pilha , valor1);
    frame->pilha = inserir_na_pilha (frame->pilha , valor2);


    return 0;
}


/*0x60 */
/* soma dois valores da pilha e empilha o resultado */
int iadd (frame_execucao * frame)
{

    u4 valor1=0,valor2=0,soma=0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no iadd. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);

    soma = valor1+valor2;

    frame->pilha = inserir_na_pilha (frame->pilha , soma);

    return 0;
}

/* 0x61 */
int ladd (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0 , soma = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    soma = valor1 + valor2;

    aux1 = soma & 0x0000FFFF;
    soma>>=32;
    aux2 = soma;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/*0x62 */
/* soma dois valores floats da pilha e empilha o resultado */
int fadd (frame_execucao * frame)
{

    u4 valor1=0,valor2=0, valor=0;
    float f1, f2,f, resultado;
    tipo_float valor_float;
    unsigned int i;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no iadd. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);

    f1=converte_para_float(valor1);
    f2=converte_para_float(valor2);

    resultado = f1+f2;

    f = (float)resultado;
    valor_float.f = f;
    i = valor_float.i;
    valor=i;

    frame->pilha = inserir_na_pilha (frame->pilha , valor);

    return 0;
}

/* 0x63 */
int dadd (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    u4 aux1 = 0 , aux2 = 0;
    long long valor1 = 0 , valor2 = 0 , l = 0 , valor = 0;
    double valord1 = 0 , valord2 = 0 , soma = 0 , d = 0;
    tipo_double valor_double;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    valord1 = converte_para_double(valor1);
    valord2 = converte_para_double(valor2);

    soma = valord1 + valord2;

    d = (double)soma;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/* 0x64 */
/* Desempilha dois valores, subtrai e empilha o resultado */
int isub(frame_execucao * frame)
{

    u4 valor1 = 0, valor2 = 0 , sub = 0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no isub. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);

    sub = valor1-valor2;

    frame->pilha = inserir_na_pilha (frame->pilha , sub);

    return 0;
}

/* 0x65 */
/* Desempilha dois valores longs, subtrai e empilha o resultado */
int lsub (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0 , sub = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    sub = valor1 - valor2;

    aux1 = sub & 0x0000FFFF;
    sub>>=32;
    aux2 = sub;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    valor1 = aux2;
    valor1<<=32;
    valor1|=aux1;

    return 0;

}


/*0x66 */
/* subtrai dois valores floats da pilha e empilha o resultado */
int fsub (frame_execucao * frame)
{

    u4 valor1=0,valor2=0,valor=0;
    float f1, f2,f, resultado;
    tipo_float valor_float;
    unsigned int i;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no iadd. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);

    f1=converte_para_float(valor1);
    f2=converte_para_float(valor2);

    resultado = f1-f2;

    f = (float)resultado;
    valor_float.f = f;
    i = valor_float.i;
    valor=i;

    frame->pilha = inserir_na_pilha (frame->pilha , valor);

    return 0;
}

/*0x67 */
/* subtrai dois valores double da pilha e empilha o resultado */

int dsub (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    u4 aux1 = 0 , aux2 = 0;
    long long valor1 = 0 , valor2 = 0 , l = 0 , valor = 0;
    double valord1 = 0 , valord2 = 0 , sub = 0 , d = 0;
    tipo_double valor_double;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    valord1 = converte_para_double(valor1);
    valord2 = converte_para_double(valor2);

    sub = valord1 - valord2;

    d = (double)sub;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}



/*0x68 */
/* multiplica dois valores da pilha e empilha o resultado */
int imul (frame_execucao * frame)
{

    u4 valor1=0,valor2=0,mul=0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no imul. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);

    mul = valor1*valor2;

    frame->pilha = inserir_na_pilha (frame->pilha , mul);

    return 0;
}

/*0x69 */
/* multiplica dois valores (long) da pilha e empilha o resultado */
int lmul (frame_execucao * frame)
{
    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0 , mul = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    mul = valor1 * valor2;

    aux1 = mul & 0x0000FFFF;
    mul>>=32;
    aux2 = mul;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/*0x6a */
/* multiplica dois valores da pilha e empilha o resultado */
int fmul (frame_execucao * frame)
{

    u4 valor1=0,valor2=0,valor=0;
    float f1,f2,multiplica,f;
    tipo_float valor_float;
    unsigned int i;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no imul. Pilha vazia.");
        exit(ERROR);
    }


    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);

    f1=converte_para_float(valor1);
    f2=converte_para_float(valor2);

    multiplica = f1*f2;

    f = (float)multiplica;
    valor_float.f = f;
    i = valor_float.i;
    valor=i;

    frame->pilha = inserir_na_pilha (frame->pilha , valor);

    return 0;
}

/*0x6b */
/* multiplica dois valores double da pilha e empilha o resultado */
int dmul (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    u4 aux1 = 0 , aux2 = 0;
    long long valor1 = 0 , valor2 = 0 , l = 0 , valor = 0;
    double valord1 = 0 , valord2 = 0 , mul = 0 , d = 0;
    tipo_double valor_double;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    valord1 = converte_para_double(valor1);
    valord2 = converte_para_double(valor2);

    mul = valord1 * valord2;

    d = (double)mul;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/*0x6c */
/* divide dois valores da pilha e empilha o resultado */
int idiv (frame_execucao * frame)
{

    u4 valor1=0,valor2=0,div=0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no iadd. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);

    if(valor2==0)
    {
        fprintf(stderr,"Erro em idiv. Dividendo igual a zero.\n");
        exit(ERROR);
    }

    div = valor1/valor2;

    frame->pilha = inserir_na_pilha (frame->pilha , div);

    return 0;
}

/*0x6d */
/* divide dois valores longs da pilha e empilha o resultado */
int ldiv_ (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0 , div = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    if(valor2==0)
    {
        fprintf(stderr,"Erro em idiv. Dividendo igual a zero.\n");
        exit(ERROR);
    }

    div = valor1 / valor2;

    aux1 = div & 0x0000FFFF;
    div>>=32;
    aux2 = div;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}


/*0x6e */
/* divide dois valores floats da pilha e empilha o resultado */
int fdiv (frame_execucao * frame)
{

    u4 valor1=0,valor2=0,valor=0;
    float f1, f2,f, resultado;
    tipo_float valor_float;
    unsigned int i;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no iadd. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);

    f1=converte_para_float(valor1);
    f2=converte_para_float(valor2);

    if (f2==0)
    {
        fprintf(stderr,"ERRO em fdiv. Dividendo igual a zero.\n");
        exit(ERROR);
    }

    resultado = f1/f2;

    f = (float)resultado;
    valor_float.f = f;
    i = valor_float.i;
    valor=i;

    frame->pilha = inserir_na_pilha (frame->pilha , valor);

    return 0;
}

/*0x6f */
/* multiplica dois valores double da pilha e empilha o resultado */
int ddiv (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    u4 aux1 = 0 , aux2 = 0;
    long long valor1 = 0 , valor2 = 0 , l = 0 , valor = 0;
    double valord1 = 0 , valord2 = 0 , div = 0 , d = 0;
    tipo_double valor_double;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    valord1 = converte_para_double(valor1);
    valord2 = converte_para_double(valor2);

    if (valord2==0)
    {
        fprintf(stderr,"ERRO em ddiv. Dividendo igual a zero.\n");
        exit(ERROR);
    }

    div = valord1 / valord2;

    d = (double)div;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/*0x70*/
int irem (frame_execucao * frame)
{

    u4 valor1=0,valor2=0,resultado=0;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    if (valor2==0)
    {
        fprintf(stderr,"Erro em irem. Divisao por ZERO nao permitida.");
        exit(ERROR);
    }

    resultado = valor1-(valor1/valor2)*valor2;

    frame->pilha = inserir_na_pilha(frame->pilha,resultado);


    return 0;


}

/*0x70*/
int lrem (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0, resultado = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    if (valor2==0)
    {
        fprintf(stderr,"Erro em lrem. Divisao por ZERO nao permitida.");
        exit(ERROR);
    }

    resultado = valor1-(valor1/valor2)*valor2;
    aux1 = resultado & 0x0000FFFF;
    resultado>>=32;
    aux2 = resultado;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;
}

/*0x72*/
int frem (frame_execucao * frame)
{


    u4 valor1=0,valor2=0,i,valor;
    float f1=0.0,f2=0.0,f3=0.0, f;
    tipo_float valor_float;

    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);

    f1=converte_para_float(valor1);
    f2=converte_para_float(valor2);

    if (f2!=0)
    {
        f3=fmod(f1,f2);
    }
    else
    {
        fprintf(stderr,"ERRO em frem. Divisao por ZERO nao admitida.\n");
        exit(ERROR);
    }

    f = (float)f3;
    valor_float.f = f;
    i = valor_float.i;
    valor=i;

    frame->pilha = inserir_na_pilha (frame->pilha , valor);

    return 0;
}

/* 0x73 */
int drem_ (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    u4 aux1 = 0 , aux2 = 0;
    long long valor1 = 0 , valor2 = 0 , l = 0 , valor = 0;
    double valord1 = 0 , valord2 = 0,valord3 = 0.0 , d = 0;
    tipo_double valor_double;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    valord1 = converte_para_double(valor1);
    valord2 = converte_para_double(valor2);

    if (valord2!=0)
    {
        valord3=fmod(valord1,valord2);
    }
    else
    {
        fprintf(stderr,"ERRO em drem. Divisao por ZERO nao admitida.\n");
        exit(ERROR);
    }

    d = (double)valord3;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}


/*0x74*/
/*nega inteiro*/
int ineg (frame_execucao * frame)
{

    u4 valor = 0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no ineg. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor);
    frame->pilha = inserir_na_pilha (frame->pilha , -valor);

    return 0;
}

/* 0x75 */
int lneg (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    long long valor = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor = high;
    valor<<=32;
    valor|=low;

    valor = -valor;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}



/*0x76*/
int fneg (frame_execucao * frame)
{


    u4 valor=0,i;
    float f1=0.0, f;
    tipo_float valor_float;

    frame->pilha = retirar_da_pilha (frame->pilha , &valor);

    f1=converte_para_float(valor);
    f1=-f1;

    f = (float)f1;
    valor_float.f = f;
    i = valor_float.i;
    valor=i;

    frame->pilha = inserir_na_pilha (frame->pilha , valor);

    return 0;
}

/* 0x77 */
int dneg (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    u4 aux1 = 0 , aux2 = 0;
    long long valor1 = 0 , l = 0 , valor = 0;
    double valord1 = 0 ,  d = 0;
    tipo_double valor_double;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    valord1 = converte_para_double(valor1);

    valord1=-valord1;

    d = (double)valord1;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}


/*0x78*/
/*faz um shift para esquerda em um int */
int ishl(frame_execucao * frame)
{

    u4 valor1=0,valor2=0,s;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    s = 0x1f & valor2; /* pega os bits menos significativos */

    valor1<<=s;

    frame->pilha = inserir_na_pilha(frame->pilha,valor1);

    return 0;

}

/*0x79*/
/*faz um shift para esquerda em um long */
int lshl(frame_execucao * frame)
{
    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0, s = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);

    valor2 = high;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    s = 0x3f & valor2; /* pega os bits menos significativos */
    valor1<<=s;

    aux1 = valor1 & 0x0000FFFF;
    valor1>>=32;
    aux2 = valor1;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/*0x7a*/
/*faz um shift para direita em um int */
int ishr(frame_execucao * frame)
{
    u4 valor1=0,valor2=0,s;
    int valor_int = 0,sign = 0;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    s = 0x1f & valor2;
    sign = 0x80000000;		/* Ultimo bit setado como 1 */

    /* pega os bits menos significativos */

    valor_int = (int)valor1;
    sign = sign & valor_int;     /*pegando o sinal*/
    valor_int>>=s;
    valor_int|=sign;           /* devolvendo o sinal */

    frame->pilha = inserir_na_pilha(frame->pilha,(u4)valor_int);

    return 0;
}

/*0x7b*/
/*faz um shift para direita em um long */
int lshr(frame_execucao * frame)
{
    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0, s = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);

    valor2 = high;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    s = 0x3f & valor2; /* pega os 6 bits menos significativos */
    valor1>>=s;        /* desloca para a direita S bits */

    aux1 = valor1 & 0x0000FFFF;
    valor1>>=32;
    aux2 = valor1;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;
}

/*0x7c*/
int iushr(frame_execucao * frame)
{

    u4 valor1=0,valor2=0;
    u4 mask = 0x1F;
    u4 res;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    if (valor1 >= 0)
        res = valor1>>(valor2 & mask);
    else
        res = (valor1>>(valor2 & mask)) + (2>>(valor2 & mask));

    frame->pilha = inserir_na_pilha(frame->pilha,res);

    return 0;

}


/*0x7e*/
/*faz um and entre dois ints */
int iand(frame_execucao * frame)
{

    u4 valor1=0,valor2=0;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    valor1&=valor2;

    frame->pilha = inserir_na_pilha(frame->pilha,valor1);

    return 0;

}

/*0x7f*/
/*faz um and entre dois longs */
int land(frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    valor1&= valor2;

    aux1 = valor1 & 0x0000FFFF;
    valor1>>=32;
    aux2 = valor1;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;
}

/*0x80*/
/*faz um or entre dois ints */
int ior(frame_execucao * frame)
{

    u4 valor1=0,valor2=0;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    valor1|=valor2;

    frame->pilha = inserir_na_pilha(frame->pilha,valor1);

    return 0;

}

/*0x81*/
/*faz um or entre dois longs */
int lor(frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    valor1|= valor2;

    aux1 = valor1 & 0x0000FFFF;
    valor1>>=32;
    aux2 = valor1;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;


}

/*0x82*/
/*faz um xor entre dois ints */
int ixor(frame_execucao * frame)
{

    u4 valor1=0,valor2=0;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    valor1^=valor2;

    frame->pilha = inserir_na_pilha(frame->pilha,valor1);

    return 0;

}

/*0x83*/
/*faz um xor entre dois longs */
int lxor (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0 ;
    long long aux1 = 0 , aux2 = 0;


    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    valor1^= valor2;

    aux1 = valor1 & 0x0000FFFF;
    valor1>>=32;
    aux2 = valor1;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;


}
/* 0x84 */
/* incremente valor de variavel local inteira */
int iinc (frame_execucao * frame)
{

    u4 indice = 0 , valor = 0;
    int valor_int;

    indice = frame->code[frame->pc++];
    valor  = frame->code[frame->pc++];

    valor_int = valor;

    frame->variaveis_locais[indice] = frame->variaveis_locais[indice] + valor_int;

    return 0;

}

/* 0x85 */
/* transforma inteiro em long */
int i2l (frame_execucao * frame)
{

    u4 valor=0,aux1,aux2;
    long long valor_long;

    frame->pilha = retirar_da_pilha (frame->pilha,&valor);

    valor_long = (int) valor;


    aux1 = valor_long & 0x0000FFFF;
    valor_long>>=32;
    aux2 = valor_long;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/* 0x86 */
/* transforma inteiro em float */
int i2f (frame_execucao * frame)
{

    u4 valor=0;
    float f;
    tipo_float valor_float;
    unsigned int i;

    frame->pilha = retirar_da_pilha (frame->pilha,&valor);

    f = (int)valor;
    valor_float.f = f;
    i = valor_float.i;
    valor=i;

    frame->pilha = inserir_na_pilha (frame->pilha,valor);

    return 0;

}

/* 0x87 */
/* transforma inteiro em double */
int i2d (frame_execucao * frame)
{

    u4 valor,aux1,aux2;
    long long valor_long=0;
    double d;
    tipo_double valor_double;
    long long l;

    frame->pilha = retirar_da_pilha (frame->pilha,&valor);

    d = (int)valor;
    valor_double.d = d;
    l = valor_double.l;
    valor_long=l;

    aux1 = valor_long & 0x0000FFFF;
    valor_long>>=32;
    aux2 = valor_long;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/*0x88*/
/* transforma long em int */
int l2i(frame_execucao * frame)
{

    u4 high,low;
    long long v_long;
    int v_int;

    frame->pilha = retirar_da_pilha(frame->pilha,&high);
    frame->pilha = retirar_da_pilha(frame->pilha,&low);

    v_long = high;
    v_long<<=32;
    v_long|=low;

    v_int = (long long) v_long;

    frame->pilha = inserir_na_pilha(frame->pilha,v_int);

    return 0;

}

/*0x89*/
int l2f (frame_execucao * frame)
{

    u4 valor,high,low;
    long long v_long;
    float v_float,f;
    tipo_float valor_float;
    int i;

    frame->pilha = retirar_da_pilha(frame->pilha,&high);
    frame->pilha = retirar_da_pilha(frame->pilha,&low);

    v_long = high;
    v_long<<=32;
    v_long|=low;

    v_float=(long long)v_long;

    f = (float)v_float;
    valor_float.f = f;
    i = valor_float.i;
    valor=i;

    frame->pilha = inserir_na_pilha (frame->pilha , (u4)valor);

    return 0;
}

/*0x8a*/
/* transforma double em int */
int l2d(frame_execucao * frame)
{

    u4 high,low,aux1,aux2;
    long long v_long,l,valor;
    double v_double,d;
    tipo_double valor_double;

    frame->pilha = retirar_da_pilha(frame->pilha,&high);
    frame->pilha = retirar_da_pilha(frame->pilha,&low);

    v_long = high;
    v_long<<=32;
    v_long|=low;

    v_double = (long long)v_long;

    d= (double)v_double;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}

/*0x8b*/
/* transforma double em int */
int f2i(frame_execucao * frame)
{

    u4 valor = 0;
    float valor_float;
    int valor_int;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor);

    valor_float = converte_para_float(valor);

    valor_int=(int)valor_float;

    frame->pilha = inserir_na_pilha(frame->pilha,(u4)valor_int);

    return 0;

}

/*0x8c*/
/* transforma float em long */
int f2l(frame_execucao * frame)
{

    u4 valor_u4,aux1,aux2;
    long long v_long;
    float valor_float;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor_u4);

    valor_float = converte_para_float(valor_u4);

    v_long = (long long)valor_float;

    aux1 = v_long & 0x0000FFFF;
    v_long>>=32;
    aux2 = v_long;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}


/*0x8d*/
/* transforma float em double */
int f2d(frame_execucao * frame)
{

    u4 valor_u4,aux1,aux2;
    long long l,valor;
    float valor_float;
    double v_double,d;
    tipo_double valor_double;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor_u4);

    valor_float = converte_para_float(valor_u4);

    v_double = (double)valor_float;

    d= (double)v_double;
    valor_double.d = d;
    l = valor_double.l;
    valor=l;

    aux1 = valor & 0x0000FFFF;
    valor>>=32;
    aux2 = valor;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);

    return 0;

}



/*0x8e*/
/* transforma double em int */
int d2i(frame_execucao * frame)
{


    u4 high,low;
    long long valor_long;
    double valor_double;
    int valor_int;

    /*retira o mais significativo. sobra o menos */
    frame->pilha = retirar_da_pilha(frame->pilha,&high);
    frame->pilha = retirar_da_pilha(frame->pilha,&low);

    valor_long = high;
    valor_long<<=32;
    valor_long|=low;

    valor_double = converte_para_double(valor_long);

    valor_int = (int)valor_double;

    frame->pilha = inserir_na_pilha(frame->pilha,(u4)valor_int);


    return 0;

}

/*0x8f*/
/*transforma double em long*/
int d2l (frame_execucao * frame)
{

    u4 high,low,aux1,aux2;
    long long v_long;
    double v_double;

    frame->pilha = retirar_da_pilha(frame->pilha,&high);
    frame->pilha = retirar_da_pilha(frame->pilha,&low);

    v_long = high;
    v_long<<=32;
    v_long|=low;

    v_double=converte_para_double(v_long);

    v_long = (long long)v_double;

    aux1 = v_long & 0x0000FFFF;
    v_long>>=32;
    aux2 = v_long;

    frame->pilha = inserir_na_pilha (frame->pilha , aux1);
    frame->pilha = inserir_na_pilha (frame->pilha , aux2);


    return 0;
}


/*0x90*/
int d2f (frame_execucao * frame)
{

    u4 valor,high,low;
    long long v_long;
    double v_double;
    float v_float,f;
    tipo_float valor_float;
    int i;

    frame->pilha = retirar_da_pilha(frame->pilha,&high);
    frame->pilha = retirar_da_pilha(frame->pilha,&low);

    v_long = high;
    v_long<<=32;
    v_long|=low;

    v_double=converte_para_double(v_long);

    v_float = (float)v_double;

    f = (float)v_float;
    valor_float.f = f;
    i = valor_float.i;
    valor=i;

    frame->pilha = inserir_na_pilha (frame->pilha , valor);

    return 0;
}


/*0x91*/
/* transforma int em byte */
int i2b(frame_execucao * frame)
{


    char byte = 0;
    u4 valor = 0;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor);

    byte = (u1)valor;

    frame->pilha = inserir_na_pilha(frame->pilha,(u4)byte);

    return 0;

}

/*0x92*/
/* transforma int em char */
int i2c(frame_execucao * frame)
{

    char c;
    u4 valor = 0;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor);

    frame->pilha = inserir_na_pilha(frame->pilha,c);

    return 0;

}

/*0x93*/
/* transforma int em short */
int i2s(frame_execucao * frame)
{

    u2 short_int = 0;
    u4 valor = 0;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor);

    short_int = (signed short)valor;

    frame->pilha = inserir_na_pilha(frame->pilha,short_int);

    return 0;

}

/* 0x94 */
int lcmp (frame_execucao * frame)
{

    u4 high = 0 , low = 0;
    long long valor1 = 0 , valor2 = 0  ;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    if (valor1>valor2)  frame->pilha = inserir_na_pilha (frame->pilha , (u4)1);
    if (valor1==valor2) frame->pilha = inserir_na_pilha (frame->pilha , (u4)0);
    if (valor1<valor2)  frame->pilha = inserir_na_pilha (frame->pilha , (u4)-1);

    return 0;

}


/*0x95 */
/* compara dois floats */
int fcmpl (frame_execucao * frame)
{

    u4 valor1=0,valor2=0;
    float f1=0.0, f2=0.0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no fcmpl. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);

    f1=converte_para_float(valor1);
    f2=converte_para_float(valor2);

    if (f1>f2)  frame->pilha = inserir_na_pilha (frame->pilha , (u4)1);
    if (f1==f2) frame->pilha = inserir_na_pilha (frame->pilha , (u4)0);
    if (f1<f2)  frame->pilha = inserir_na_pilha (frame->pilha , (u4)-1);

    return 0;
}


/*0x96 */
/* compara dois floats */
int fcmpg (frame_execucao * frame)
{

    u4 valor1=0,valor2=0;
    float f1=0.0, f2=0.0;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no fcmpl. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha , &valor2);
    frame->pilha = retirar_da_pilha (frame->pilha , &valor1);

    f1=converte_para_float(valor1);
    f2=converte_para_float(valor2);

    if (f1>f2)  frame->pilha = inserir_na_pilha (frame->pilha , (u4)1);
    if (f1==f2) frame->pilha = inserir_na_pilha (frame->pilha , (u4)0);
    if (f1<f2)  frame->pilha = inserir_na_pilha (frame->pilha , (u4)-1);

    return 0;
}

/*0x97 */
/* compara dois doubles */
int dcmpl (frame_execucao * frame)
{

    long long valor1=0,valor2=0;
    u4 high,low;
    double valord1,valord2;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no dcmpl. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    valord1 = converte_para_double(valor1);
    valord2 = converte_para_double(valor2);

    if (valord1>valord2)  frame->pilha = inserir_na_pilha (frame->pilha , 1);
    if (valord1==valord2) frame->pilha = inserir_na_pilha (frame->pilha , 0);
    if (valord1<valord2)  frame->pilha = inserir_na_pilha (frame->pilha , -1);

    return 0;
}

/*0x98 */
/* compara dois doubles */
int dcmpg (frame_execucao * frame)
{

    long long valor1=0,valor2=0;
    u4 high,low;
    double valord1,valord2;

    if (frame->pilha == NULL)
    {
        fprintf(stderr,"ERRO! Erro no dcmpl. Pilha vazia.");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor2 = high;
    valor2<<=32;
    valor2|=low;

    frame->pilha = retirar_da_pilha (frame->pilha,&high);
    frame->pilha = retirar_da_pilha (frame->pilha,&low);

    valor1 = high;
    valor1<<=32;
    valor1|=low;

    valord1 = converte_para_double(valor1);
    valord2 = converte_para_double(valor2);

    if (valord1>valord2)  frame->pilha = inserir_na_pilha (frame->pilha , 1);
    if (valord1==valord2) frame->pilha = inserir_na_pilha (frame->pilha , 0);
    if (valord1<valord2)  frame->pilha = inserir_na_pilha (frame->pilha , -1);

    return 0;
}



/*0x99*/
/* compara com 0. se for igual, pula  para instrucao informada */
int ifeq (frame_execucao * frame)
{

    u1 byte1=0 , byte2=0;
    u4 pulo = 0, valor = 0;
    u4 pc_inicial = frame->pc;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    pulo =  (byte1 << 8) | byte2;

    frame->pilha = retirar_da_pilha (frame->pilha , &valor);

    if ((int)valor == 0)
    {
        frame->pc = pc_inicial + (short)pulo - 1;
    }

    return 0;
}

/*0x9a*/
/* compara com 0. se for igual, pula  para instrucao informada */
int ifne (frame_execucao * frame)
{

    u1 byte1=0 , byte2=0;
    u4 pulo = 0, valor = 0;
    u4 pc_inicial = frame->pc;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    pulo =  (byte1 << 8) | byte2;

    frame->pilha = retirar_da_pilha (frame->pilha , &valor);

    if ((int)valor != 0)
    {
        frame->pc = pc_inicial + (short)pulo - 1;
    }

    return 0;
}

/*0x9b*/
/* compara com 0. se for igual, pula  para instrucao informada */
int iflt (frame_execucao * frame)
{

    u1 byte1=0 , byte2=0;
    u4 pulo = 0, valor = 0;
    u4 pc_inicial = frame->pc;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    pulo =  (byte1 << 8) | byte2;

    frame->pilha = retirar_da_pilha (frame->pilha , &valor);

    if ((int)valor < 0)
    {
        frame->pc = pc_inicial + (short)pulo - 1;
    }

    return 0;
}

/*0x9c*/
/* compara com 0. se for igual, pula  para instrucao informada */
int ifge (frame_execucao * frame)
{

    u1 byte1=0 , byte2=0;
    u4 pulo = 0, valor = 0;
    u4 pc_inicial = frame->pc;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    pulo =  (byte1 << 8) | byte2;

    frame->pilha = retirar_da_pilha (frame->pilha , &valor);

    if ((int)valor >= 0)
    {
        frame->pc = pc_inicial + (short)pulo - 1;
    }

    return 0;
}

/*0x9d*/
/* compara com 0. se for igual, pula  para instrucao informada */
int ifgt (frame_execucao * frame)
{

    u1 byte1=0 , byte2=0;
    u4 pulo = 0, valor = 0;
    u4 pc_inicial = frame->pc;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    pulo =  (byte1 << 8) | byte2;

    frame->pilha = retirar_da_pilha (frame->pilha , &valor);

    if ((int)valor > 0)
    {
        frame->pc = pc_inicial + (short)pulo - 1;
    }

    return 0;
}

/*0x9e*/
/* compara com 0. se for igual, pula  para instrucao informada */
int ifle (frame_execucao * frame)
{

    u1 byte1=0 , byte2=0;
    u4 pulo = 0, valor = 0;
    u4 pc_inicial = frame->pc;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    pulo =  (byte1 << 8) | byte2;

    frame->pilha = retirar_da_pilha (frame->pilha , &valor);


    if ((int)valor <= 0)
    {
        frame->pc = pc_inicial + (short)pulo - 1;
    }

    return 0;
}

/*0x9f*/
/* compara dois valores retirados da pilha. se for =, pula para instrucao dada */
int if_icmpeq       (frame_execucao * frame)
{
    u4 valor1=0,valor2=0;
    u1 byte1=0 , byte2=0;
    u4 valor = 0;
    u4 pc_inicial = frame->pc;


    /* recupera valor do pulo da instrucao */
    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    valor =  (byte1 << 8) | byte2;

    /* retira valor 2 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);

    /* retira valor 1 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    if (valor1==valor2)
    {
        frame->pc = pc_inicial + (short)valor - 1;
    }

    return 0;

}

/*0xa0*/
/* compara dois valores retirados da pilha. se for !=, pula para instrucao dada */
int if_icmpne       (frame_execucao * frame)
{
    u4 valor1=0,valor2=0;
    u1 byte1=0 , byte2=0;
    u4 valor = 0;
    u4 pc_inicial = frame->pc;


    /* recupera valor do pulo da instrucao */
    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    valor =  (byte1 << 8) | byte2;

    /* retira valor 2 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);

    /* retira valor 1 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    if (valor1!=valor2)
    {
        frame->pc = pc_inicial + (short)valor - 1;
    }

    return 0;

}



/*0xa1*/
/* compara dois valores retirados da pilha. se for <, pula para instrucao dada */
int if_icmplt       (frame_execucao * frame)
{
    u4 valor1=0,valor2=0;
    u1 byte1=0 , byte2=0;
    u4 valor = 0;
    u4 pc_inicial = frame->pc;


    /* recupera valor do pulo da instrucao */
    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    valor =  (byte1 << 8) | byte2;

    /* retira valor 2 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);

    /* retira valor 1 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    if (valor1<valor2)
    {
        frame->pc = pc_inicial + (short)valor - 1;
    }

    return 0;

}

/* 0xa2 */
/* compara dois valores retirados da pilha. se for >=, pula para instrucao dada */
int if_icmpge(frame_execucao * frame)
{

    u4 valor1=0,valor2=0;
    u1 byte1=0 , byte2=0;
    u4 valor = 0;
    u4 pc_inicial = frame->pc;


    /* recupera valor do pulo da instrucao */
    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    valor =  (byte1 << 8) | byte2;

    /* retira valor 2 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);

    /* retira valor 1 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    if (valor1>=valor2)
    {
        frame->pc = pc_inicial + (short)valor - 1;
    }

    return 0;

}

/* 0xa3 */
/* compara dois valores retirados da pilha. se for >, pula para instrucao dada */
int if_icmpgt(frame_execucao * frame)
{

    u4 valor1=0,valor2=0;
    u1 byte1=0 , byte2=0;
    u4 valor = 0;
    u4 pc_inicial = frame->pc;


    /* recupera valor do pulo da instrucao */
    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    valor =  (byte1 << 8) | byte2;

    /* retira valor 2 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);

    /* retira valor 1 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    if (valor1>valor2)
    {
        frame->pc = pc_inicial + (short)valor - 1;
    }

    return 0;

}

/* 0xa4 */
/* compara dois valores retirados da pilha. se for <=, pula para instrucao dada */
int if_icmple(frame_execucao * frame)
{

    u4 valor1=0,valor2=0;
    u1 byte1=0 , byte2=0;
    u4 valor = 0;
    u4 pc_inicial = frame->pc;


    /* recupera valor do pulo da instrucao */
    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    valor =  (byte1 << 8) | byte2;

    /* retira valor 2 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor2);

    /* retira valor 1 da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor1);

    if (valor1<=valor2)
    {
        frame->pc = pc_inicial + (short)valor - 1;
    }

    return 0;

}

/* 0xa7 */
int goto_(frame_execucao * frame)
{

    u1 byte1=0 , byte2=0;
    u4 valor = 0;
    u4 pc_inicial = frame->pc;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    valor =  (byte1 << 8) | byte2;

    frame->pc = pc_inicial + (short)valor - 1;

    return 0;

}

/*0xa9*/
/*metodo retorna para um chamador */
int ret (frame_execucao * frame)
{

    u4 valor=0,index=0;
    index = frame->code[frame->pc++];
    valor = frame->variaveis_locais[index];
    frame->pc = valor;

    return 0;

}

/*0xaa*/
/* acessa tabela para pular para instrucao */
int tableswitch (frame_execucao * frame)
{

    int i;
    u4 defaultbyte=0, byte1,byte2,byte3,byte4;
    u4 valor,high,low,jump,pc_inicial;

    pc_inicial = frame->pc;

    while(frame->pc%4!=0)
    {
        frame->pc++;
    }

    byte1=frame->code[frame->pc++];
    byte2=frame->code[frame->pc++];
    byte3=frame->code[frame->pc++];
    byte4=frame->code[frame->pc++];
    defaultbyte = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    byte1=frame->code[frame->pc++];
    byte2=frame->code[frame->pc++];
    byte3=frame->code[frame->pc++];
    byte4=frame->code[frame->pc++];
    low = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    byte1=frame->code[frame->pc++];
    byte2=frame->code[frame->pc++];
    byte3=frame->code[frame->pc++];
    byte4=frame->code[frame->pc++];
    high = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor);

    i = low;

    do
    {

        byte1=frame->code[frame->pc++];
        byte2=frame->code[frame->pc++];
        byte3=frame->code[frame->pc++];
        byte4=frame->code[frame->pc++];
        jump = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

        if (i==valor)
        {
            frame->pc = pc_inicial + jump - 1;
            return 0;
        }

        i++;

    }
    while (i<=high);

    frame->pc = pc_inicial + defaultbyte - 1;

    return 0;

}


/*0xab*/
/* acessa tabela para pular para instrucao */
int lookupswitch (frame_execucao * frame)
{

    int i;
    u4 defaultbyte=0, byte1,byte2,byte3,byte4;
    u4 valor,npairs,jump,key,pc_inicial;

    pc_inicial = frame->pc;

    while(frame->pc%4!=0)
    {
        frame->pc++;
    }


    byte1=frame->code[frame->pc++];
    byte2=frame->code[frame->pc++];
    byte3=frame->code[frame->pc++];
    byte4=frame->code[frame->pc++];
    defaultbyte = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    byte1=frame->code[frame->pc++];
    byte2=frame->code[frame->pc++];
    byte3=frame->code[frame->pc++];
    byte4=frame->code[frame->pc++];
    npairs = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    frame->pilha = retirar_da_pilha(frame->pilha,&valor);

    for (i=0 ; i<npairs ; i++)
    {

        byte1=frame->code[frame->pc++];
        byte2=frame->code[frame->pc++];
        byte3=frame->code[frame->pc++];
        byte4=frame->code[frame->pc++];
        key = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

        byte1=frame->code[frame->pc++];
        byte2=frame->code[frame->pc++];
        byte3=frame->code[frame->pc++];
        byte4=frame->code[frame->pc++];
        jump = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

        if (key==valor)
        {
            frame->pc = pc_inicial + jump - 1;
            return 0;
        }

    }

    frame->pc = pc_inicial + defaultbyte - 1;

    return 0;

}

/* 0xac */
/* metodo retorna um inteiro para o chamador */
int ireturn(frame_execucao * frame)
{

    u4 valor = 0;
    pilha_frame * frame_aux;

    if (frames_em_execucao->next==NULL)
    {
        fprintf(stderr,"Erro no ireturn. Nao ha metodo para retorno.\n");
        exit(ERROR);
    }

    frame->pilha = retirar_da_pilha(frame->pilha,&valor);
    /* insere na pilha do chamador o valor */
    frames_em_execucao->next->frame->pilha = inserir_na_pilha(frames_em_execucao->next->frame->pilha, valor);

    /* encerra frame atual */
    frame_aux = frames_em_execucao;
    frames_em_execucao = frames_em_execucao->next;
    free(frame_aux);

    frame->pc = frame->code_length;

    return 0;
}

/* 0xad */
/* metodo retorna um long para o chamador */
int lreturn(frame_execucao * frame)
{

    u4 high,low;
    pilha_frame * frame_aux;

    if (frames_em_execucao->next==NULL)
    {
        fprintf(stderr,"Erro no lreturn. Nao ha metodo para retorno.\n");
        exit(ERROR);
    }

    /*insere o valor do double na pilha do metodo chamador */
    frame->pilha = retirar_da_pilha(frame->pilha,&high);
    frame->pilha = retirar_da_pilha(frame->pilha,&low);

    frames_em_execucao->next->frame->pilha = inserir_na_pilha(frames_em_execucao->next->frame->pilha, low);
    frames_em_execucao->next->frame->pilha = inserir_na_pilha(frames_em_execucao->next->frame->pilha, high);

    /* encerra frame atual */
    frame_aux = frames_em_execucao;
    frames_em_execucao = frames_em_execucao->next;
    free(frame_aux);

    frame->pc = frame->code_length;

    return 0;
}

/* 0xae */
/* metodo retorna um float para o chamador */
int freturn(frame_execucao * frame)
{

    u4 valor = 0;
    pilha_frame * frame_aux;

    if (frames_em_execucao->next==NULL)
    {
        fprintf(stderr,"Erro no freturn. Nao ha metodo para retorno.\n");
        exit(ERROR);
    }

    /*insere o valor do float na pilha do metodo chamador */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor);
    frames_em_execucao->next->frame->pilha = inserir_na_pilha(frames_em_execucao->next->frame->pilha, valor);

    /* encerra frame atual */
    frame_aux = frames_em_execucao;
    frames_em_execucao = frames_em_execucao->next;
    free(frame_aux);

    frame->pc = frame->code_length;

    return 0;
}

/* 0xaf */
/* metodo retorna um double para o chamador */
int dreturn(frame_execucao * frame)
{

    u4 high,low;
    pilha_frame * frame_aux;

    if (frames_em_execucao->next==NULL)
    {
        fprintf(stderr,"Erro no dreturn. Nao ha metodo para retorno.\n");
        exit(ERROR);
    }

    /*insere o valor do double na pilha do metodo chamador */
    frame->pilha = retirar_da_pilha(frame->pilha,&high);
    frame->pilha = retirar_da_pilha(frame->pilha,&low);

    frames_em_execucao->next->frame->pilha = inserir_na_pilha(frames_em_execucao->next->frame->pilha, low);
    frames_em_execucao->next->frame->pilha = inserir_na_pilha(frames_em_execucao->next->frame->pilha, high);

    /* encerra frame atual */
    frame_aux = frames_em_execucao;
    frames_em_execucao = frames_em_execucao->next;
    free(frame_aux);

    frame->pc = frame->code_length;

    return 0;
}

/* 0xb0 */
/* metodo retorna uma referencia para o chamador */
int areturn(frame_execucao * frame)
{

    u4 valor = 0;
    pilha_frame * frame_aux;

    if (frames_em_execucao->next==NULL)
    {
        fprintf(stderr,"Erro no areturn. Nao ha metodo para retorno.\n");
        exit(ERROR);
    }

    /*insere o valor do float na pilha do metodo chamador */
    frame->pilha = retirar_da_pilha(frame->pilha,&valor);
    frames_em_execucao->next->frame->pilha = inserir_na_pilha(frames_em_execucao->next->frame->pilha, valor);

    /* encerra frame atual */
    frame_aux = frames_em_execucao;
    frames_em_execucao = frames_em_execucao->next;
    free(frame_aux);

    frame->pc = frame->code_length;

    return 0;
}

/* 0xb1 */
/* finaliza execucao do frame */
int return_ (frame_execucao * frame)
{

    pilha_frame * frame_aux;

    frame_aux = frames_em_execucao;
    frames_em_execucao = frames_em_execucao->next;
    free(frame_aux);

    frame->pc = frame->code_length;

    return 0;
}

/* 0xb2 */
int getstatic(frame_execucao * frame)
{

    int i , j , classe_carregada , achou_campo;
    u1 byte1, byte2;
    u2 indice = 0, indiceClasse, indiceCampo, indiceDescriptor;
    u2 indiceNomeCampoPesq,indiceTipoCampoPesq;
    u4 valor,valor2;
    char * nomeCampo, * nomeClasse , *nomeDescriptor;
    char * nomeCampoInstancia,*tipoCampoInstancia;
    instance * instancia;
    static_pilha * campo_estatico;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;

    /* indice aponta para uma constant pool do tipo Fieldref */
    /* recupera indice/nome da classe e no name_and_type do fieldref */
    indiceClasse = frame->constant_pool[indice-1].info.fieldref_info.class_index;
    indiceClasse = frame->constant_pool[indiceClasse-1].info.class_info.name_index;
    nomeClasse = (char*) frame->constant_pool[indiceClasse-1].info.utf8_info.bytes;

    indiceCampo = frame->constant_pool[indice-1].info.fieldref_info.name_and_type_index;
    indiceCampo = frame->constant_pool[indiceCampo-1].info.nameandtype_info.name_index;
    nomeCampo  = (char*) frame->constant_pool[indiceCampo-1].info.utf8_info.bytes;

    indiceDescriptor = frame->constant_pool[indice-1].info.fieldref_info.name_and_type_index;
    indiceDescriptor = frame->constant_pool[indiceDescriptor-1].info.nameandtype_info.descriptor_index;
    nomeDescriptor = (char*) frame->constant_pool[indiceDescriptor-1].info.utf8_info.bytes;


    /* se for a classe System/PrintStream, não faz nada */
    /* se nao for, chama o metodo */
    if ( (strcmp(nomeClasse,"java/lang/System")!=0) && (strcmp(nomeCampo,"out")!=0) &&
            (strcmp(nomeDescriptor,"Ljava/io/PrintStream;")!=0) )
    {


        campo_estatico = pilha_static;

        while (instancia != NULL)
        {

            if ( (strcmp(campo_estatico->nomeCampo,nomeCampo)==0) && (strcmp(campo_estatico->tipoCampo,nomeDescriptor)==0) )
            {

                if ((nomeDescriptor[0]=='J')||(nomeDescriptor[0]=='D'))
                {
                    valor = campo_estatico->valorCampo[0];
                    valor2 = campo_estatico->valorCampo[1];
                    frame->pilha = inserir_na_pilha(frame->pilha,valor2);
                    frame->pilha = inserir_na_pilha(frame->pilha,valor);
                }
                else
                {
                    valor = campo_estatico->valorCampo[0];
                    frame->pilha = inserir_na_pilha(frame->pilha,valor);

                }
                return 0;
            }

            campo_estatico = campo_estatico->next;

        }





    }
    else
    {

        /* se for PrintStream - coloca valor generico na pilha */
        valor = 999999999;
        frame->pilha =  inserir_na_pilha (frame->pilha,valor);

    }

    return 0;
}

/* 0xb3 */
int putstatic(frame_execucao * frame)
{

    int i , j , achou_campo, ind, classe_iniciada;
    u1 byte1, byte2;
    u2 indice = 0, gda_indice ;
    u2 indiceNomeCampo, indiceTipoCampo, indiceNomeClasse, indiceNomeCampoPesq , indiceTipoCampoPesq;
    u2 indiceTipo, indiceCampo, indiceSuperClasse;
    char * nomeCampo, * tipoCampo , *nomeClasse , *nomeCampoInstancia , *tipoCampoInstancia;
    char *nomeTipoClasse , * nomeCampoClasse;
    char *nomeSuperClasse;
    u4 referencia , valor, valor2;
    instance * instancia;
    static_pilha *campo_estatico,*new_campo;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;
    gda_indice = indice;

    indice = frame->constant_pool[indice-1].info.fieldref_info.name_and_type_index;

    indiceNomeCampo = frame->constant_pool[indice-1].info.nameandtype_info.name_index;
    nomeCampo = (char*) frame->constant_pool[indiceNomeCampo-1].info.utf8_info.bytes;

    indiceTipoCampo = frame->constant_pool[indice-1].info.nameandtype_info.descriptor_index;
    tipoCampo = (char*) frame->constant_pool[indiceTipoCampo-1].info.utf8_info.bytes;

    indiceNomeClasse = frame->constant_pool[gda_indice-1].info.fieldref_info.class_index;
    indiceNomeClasse = frame->constant_pool[indiceNomeClasse-1].info.class_info.name_index;
    nomeClasse = (char*) frame->constant_pool[indiceNomeClasse-1].info.utf8_info.bytes;


#ifdef DEBUG
    printf ("     => nome classe: %s\n",nomeClasse);
    printf ("     => nome campo: %s\n", nomeCampo);
    printf ("     => tipo campo: %s \n",tipoCampo);
#endif

    /* recupera valor que sera incluido no campo*/
    valor = 0 ;
    valor2 = 0;

    if ((tipoCampo[0] == 'J') || (tipoCampo[0] == 'D') )
    {
        frame->pilha = retirar_da_pilha(frame->pilha,&valor);
        frame->pilha = retirar_da_pilha(frame->pilha,&valor2);
    }
    else
    {
        frame->pilha = retirar_da_pilha(frame->pilha,&valor);
    }

    campo_estatico = pilha_static;

    while (campo_estatico != NULL)
    {

        if ( (strcmp(campo_estatico->nomeCampo,nomeCampo)==0) && (strcmp(campo_estatico->tipoCampo,tipoCampo)==0) )
        {

            if (tipoCampo[0]=='J')
            {
                campo_estatico->valorCampo[0] = valor;
                campo_estatico->valorCampo[1] = valor2;
            }
            else
            {
                campo_estatico->valorCampo[0] = valor;

            }
            return 0;
        }

        campo_estatico = campo_estatico->next;

    }


#ifdef DEBUG
    printf ("     => cria novo campo [%s] em static.\n",nomeCampo);
#endif

    new_campo = malloc(sizeof(static_pilha));
    new_campo->nomeCampo = nomeCampo;
    new_campo->tipoCampo = tipoCampo;
    if ((tipoCampo[0] == 'J') || (tipoCampo[0] == 'D') )
    {
        new_campo->valorCampo = calloc (2,sizeof(u4));
        new_campo->valorCampo[0] = valor;
        new_campo->valorCampo[1] = valor2;
    }
    else
    {
        new_campo->valorCampo = malloc (sizeof(u4));
        new_campo->valorCampo[0] = valor;
    }

    new_campo->next = pilha_static;
    pilha_static = new_campo;

    return 0;

}



/* 0xb4 */
int getfield(frame_execucao * frame)
{

    int i ,  y, achou_campo, achou_classe;
    u1 byte1, byte2;
    u2 indice = 0, gda_indice ;
    u2 indiceNomeCampo, indiceTipoCampo, indiceNomeClasse;
    char * nomeCampo, * tipoCampo , *nomeClasse , *nomeCampoInstancia , *tipoCampoInstancia;
    u4 referencia , valor, valor1,valor2;
    instance * instancia;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;
    gda_indice = indice;

    indice = frame->constant_pool[indice-1].info.fieldref_info.name_and_type_index;

    indiceNomeCampo = frame->constant_pool[indice-1].info.nameandtype_info.name_index;
    nomeCampo = (char*) frame->constant_pool[indiceNomeCampo-1].info.utf8_info.bytes;

    indiceTipoCampo = frame->constant_pool[indice-1].info.nameandtype_info.descriptor_index;
    tipoCampo = (char*) frame->constant_pool[indiceTipoCampo-1].info.utf8_info.bytes;

    /* localiza a classe da instancia */
    gda_indice = frame->constant_pool[gda_indice-1].info.fieldref_info.class_index;
    indiceNomeClasse = frame->constant_pool[gda_indice-1].info.class_info.name_index;
    nomeClasse = (char*) frame->constant_pool[indiceNomeClasse-1].info.utf8_info.bytes;

    /* recupera a classe a qual pertence o objeto */
    achou_classe = 0;
    for (i = 0 ; i<qtd_classes ; i++)
    {
        if (strcmp((char*)classlist[i].class_name,nomeClasse) == 0)
        {
            achou_classe = 1;
            break;
        }
    }
#ifdef DEBUG
    printf ("     => nome classe: %s\n" , nomeClasse);
    printf ("     => nome campo: %s\n", nomeCampo);
    printf ("     => tipo campo: %s \n",tipoCampo);
#endif

    /*retira da pilha a referencia do objeto */
    frame->pilha = retirar_da_pilha(frame->pilha , &referencia);
    instancia = (struct tipo_instancia*)referencia;

    if (instancia == NULL)
    {
        fprintf(stderr,"ERRO em getfield. Objeto nulo.\n");
        exit(ERROR);
    }

    /* procura nos campos da instancia o campo desejado */
    achou_campo = 0;
    for (y = 0; y < instancia->qtd_campos ; y++)
    {

        indice = instancia->campos[y].info_campo->name_index;
        nomeCampoInstancia = (char*)instancia->campos[y].constant_pool[indice-1].info.utf8_info.bytes;

        indice = instancia->campos[y].info_campo->descriptor_index;
        tipoCampoInstancia = (char*)instancia->campos[y].constant_pool[indice-1].info.utf8_info.bytes;

        if ( (strcmp(nomeCampo,nomeCampoInstancia)==0) && (strcmp(tipoCampo,tipoCampoInstancia)==0) )
        {
            achou_campo = 1;

            if ((tipoCampo[0]=='J') || (tipoCampo[0]=='D'))
            {
                valor1 = instancia->campos[y].valor_campo[0];
                valor2 = instancia->campos[y].valor_campo[1];
                frame->pilha = inserir_na_pilha(frame->pilha,valor2);
                frame->pilha = inserir_na_pilha(frame->pilha,valor1);
            }
            else
            {
                valor = instancia->campos[y].valor_campo[0];
                frame->pilha = inserir_na_pilha(frame->pilha,valor);


            }
            return 0;
        }

    }

    if (achou_campo == 0)
    {
        fprintf(stderr,"ERRO em getfield. Campo não localizado na instancia.\n");
        exit(ERROR);
    }

    return 0;
}

/* 0xb5 */
int putfield(frame_execucao * frame)
{

    int i , j , achou_campo, ind, classe_iniciada;
    u1 byte1, byte2;
    u2 indice = 0, gda_indice ;
    u2 indiceNomeCampo, indiceTipoCampo, indiceNomeClasse, indiceNomeCampoPesq , indiceTipoCampoPesq;
    u2 indiceTipo, indiceCampo, indiceSuperClasse;
    char * nomeCampo, * tipoCampo , *nomeClasse , *nomeCampoInstancia , *tipoCampoInstancia;
    char *nomeTipoClasse , * nomeCampoClasse;
    char *nomeSuperClasse;
    u4 referencia , valor, valor2;
    instance * instancia;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;
    gda_indice = indice;

    indice = frame->constant_pool[indice-1].info.fieldref_info.name_and_type_index;

    indiceNomeCampo = frame->constant_pool[indice-1].info.nameandtype_info.name_index;
    nomeCampo = (char*) frame->constant_pool[indiceNomeCampo-1].info.utf8_info.bytes;

    indiceTipoCampo = frame->constant_pool[indice-1].info.nameandtype_info.descriptor_index;
    tipoCampo = (char*) frame->constant_pool[indiceTipoCampo-1].info.utf8_info.bytes;
#ifdef DEBUG
    printf ("     => nome campo: %s\n", nomeCampo);
    printf ("     => tipo campo: %s \n",tipoCampo);
#endif

    /* recupera valor que sera incluido no campo*/
    valor = 0 ;
    valor2=0;

    if ((tipoCampo[0] == 'J') || (tipoCampo[0] == 'D') )
    {
        frame->pilha = retirar_da_pilha(frame->pilha,&valor);
        frame->pilha = retirar_da_pilha(frame->pilha,&valor2);
    }
    else
    {
        frame->pilha = retirar_da_pilha(frame->pilha,&valor);
    }


    /* recupera o objeto */
    referencia = 0;
    frame->pilha = retirar_da_pilha(frame->pilha,&referencia);

    instancia = (struct tipo_instancia*)referencia;

    /* localiza o campo da instancia que sera alterado */
    for (j = 0 ; j < instancia->qtd_campos ; j++)
    {

        indiceNomeCampoPesq = instancia->campos[j].info_campo->name_index;
        nomeCampoInstancia = (char*)instancia->campos[j].constant_pool[indiceNomeCampoPesq-1].info.utf8_info.bytes;

        indiceTipoCampoPesq = instancia->campos[j].info_campo->descriptor_index;
        tipoCampoInstancia = (char*)instancia->campos[j].constant_pool[indiceTipoCampoPesq-1].info.utf8_info.bytes;


        if ( (strcmp(nomeCampoInstancia,nomeCampo)==0) && (strcmp(tipoCampoInstancia,tipoCampo)==0) )
        {

            if (tipoCampo[0]=='J')
            {
                instancia->campos[j].valor_campo[0] = valor;
                instancia->campos[j].valor_campo[1] = valor2;
            }
            else
            {
                instancia->campos[j].valor_campo[0] = valor;

            }
            return 0;
        }

    }
#ifdef DEBUG
    printf ("     => cria novo campo [%s] na instancia.\n",nomeCampo);
#endif


    /* localiza a classe */
    gda_indice = frame->constant_pool[gda_indice-1].info.fieldref_info.class_index;
    indiceNomeClasse = frame->constant_pool[gda_indice-1].info.class_info.name_index;
    nomeClasse = (char*) frame->constant_pool[indiceNomeClasse-1].info.utf8_info.bytes;

    classe_iniciada = 0;
    for (i=0 ; i<qtd_classes ; i++)
    {

        if (strcmp(nomeClasse,(char*)classlist[i].class_name)==0)
        {
            classe_iniciada = 1;
            break;
        }
    }

    if (classe_iniciada == 0)
    {
        fprintf(stderr,"ERRO em putfield. Classe nao localizada.\n");
        exit(ERROR);
    }


    while(1)
    {

        /* se a classe for encontrada, localiza o campo nesta classe */
        achou_campo = 0;
        for (j=0 ; j<classlist[i].classe->fields_count ; j++)
        {

            indiceCampo = classlist[i].classe->fields[j].name_index;
            nomeCampoClasse = (char*)classlist[i].classe->constant_pool[indiceCampo-1].info.utf8_info.bytes;

            indiceTipo = classlist[i].classe->fields[j].descriptor_index;
            nomeTipoClasse = (char*)classlist[i].classe->constant_pool[indiceTipo-1].info.utf8_info.bytes;

            if ( (strcmp(nomeCampoClasse,nomeCampo)==0) && (strcmp(nomeTipoClasse,tipoCampo)==0))
            {
                achou_campo = 1;
                break;
            }

        }

        if (achou_campo == 1)  break;

        /* procura na super classe */
        indiceSuperClasse = classlist[i].classe->super_class;
        indiceSuperClasse = classlist[i].classe->constant_pool[indiceSuperClasse-1].info.class_info.name_index;
        nomeSuperClasse = (char*)classlist[i].classe->constant_pool[indiceSuperClasse-1].info.utf8_info.bytes;

        classe_iniciada = 0;
        for (i = 0; i < qtd_classes ; i++)
        {
            if( strcmp((char*)classlist[i].class_name,nomeSuperClasse)==0)
            {
                classe_iniciada=1;
                break;
            }
        }

        if (classe_iniciada==0)
        {
            fprintf(stderr,"ERRO em putfield. Super Classe nao encontrada.\n");
            exit(ERROR);
        }

    }

    instancia->qtd_campos++;
    instancia->campos = (field_value*) realloc (instancia->campos , instancia->qtd_campos*sizeof(field_value));
    if (instancia->campos == NULL)
    {
        fprintf(stderr,"ERRO em putfield na alocacao de memoria.\n");
        exit(ERROR);
    }

    ind = instancia->qtd_campos-1;

    instancia->campos[ind].constant_pool = classlist[i].classe->constant_pool;
    instancia->campos[ind].info_campo = &classlist[i].classe->fields[j];

    if ((tipoCampo[0] == 'J') || (tipoCampo[0] == 'D') )
    {
        instancia->campos[ind].valor_campo = calloc (2,sizeof(u4));
        instancia->campos[ind].valor_campo[0] = valor;
        instancia->campos[ind].valor_campo[1] = valor2;
    }
    else
    {
        instancia->campos[j].valor_campo = malloc (sizeof(u4));
        instancia->campos[j].valor_campo[0] = valor;
    }

    return 0;


}


/* 0xb6 */
/* chama execucao de metodo */
int invokevirtual(frame_execucao * frame)
{
    int sinal=0;
    int i , j , classe_iniciada, qtd_metodos, inteiro;
    int valor1, valor2;
    float valor_float;
    long long valor_long;
    double valor_double;
    u1 byte1, byte2, *string;
    u2 indice = 0, indiceClasse , indiceMetodo , indiceDescritor;
    u2 indiceMetodoPesq , indiceDescritorPesq, indiceSuperClasse;
    u4 valor;
    llts t;
    char *nomeClasse , *nomeMetodo , *nomeDescritor, *nomeSuperClasse;
    char *nomeMetodoPesq , *nomeDescritorPesq, valor_char;
    frame_execucao *frame_aux;
    t_method_info * metodo;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;

    /* indice aponta para uma constant pool do tipo Methodref */
    /* recupera dados do metodo - classe, metodo e descritor */
    indiceClasse = frame->constant_pool[indice-1].info.methodref_info.class_index;
    indiceClasse = frame->constant_pool[indiceClasse-1].info.class_info.name_index;
    nomeClasse = (char*) frame->constant_pool[indiceClasse-1].info.utf8_info.bytes;

    indice = frame->constant_pool[indice-1].info.methodref_info.name_and_type_index;
    indiceMetodo = frame->constant_pool[indice-1].info.nameandtype_info.name_index;
    nomeMetodo = (char*) frame->constant_pool[indiceMetodo-1].info.utf8_info.bytes;

    indiceDescritor = frame->constant_pool[indice-1].info.nameandtype_info.descriptor_index;
    nomeDescritor = (char*) frame->constant_pool[indiceDescritor-1].info.utf8_info.bytes;


    if ((strcmp("java/io/PrintStream",nomeClasse)==0)&&
            ( (strcmp("println",nomeMetodo)!=0) || (strcmp("print",nomeMetodo)!=0) ) )
    {


        if (frame->pilha == NULL)
        {
            fprintf(stderr,"ERRO em invoke virtual! Pilha do frame vazia.\n");
            exit(ERROR);
        }
        i=0;
        while (nomeDescritor[i]!=')')

        {

            switch (nomeDescritor[i])
            {

            case 'I':
                frame->pilha = retirar_da_pilha(frame->pilha,&valor);
                inteiro = valor;
                if (strcmp("println",nomeMetodo)==0)
                    printf("%d", inteiro);
                else
                    printf("%d", inteiro);
                i++;
                break;
            case 'C':
                frame->pilha = retirar_da_pilha(frame->pilha,&valor);
                valor_char = (int)valor;
                if (strcmp("println",nomeMetodo)==0)
                    printf("%c", valor_char);
                else
                    printf("%c", valor_char);
                i++;
                break;

            case 'D':
                frame->pilha = retirar_da_pilha(frame->pilha,&valor);
                valor_long = valor;
                valor_long<<=32;
                frame->pilha = retirar_da_pilha(frame->pilha,&valor);
                valor_long|=valor;

                valor_double = converte_para_double(valor_long);

                if (strcmp("println",nomeMetodo)==0)
                    printf("%lf", valor_double);
                else
                    printf("%lf", valor_double);
                i++;
                break;

            case 'F':
                frame->pilha = retirar_da_pilha(frame->pilha,&valor);
                valor_float = converte_para_float (valor);

                if (strcmp("println",nomeMetodo)==0)
                    printf("%f", valor_float);
                else
                    printf("%f", valor_float);
                i++;
                break;

            case 'J':
                frame->pilha = retirar_da_pilha(frame->pilha,&valor);
                valor_long = valor;
                valor1 = valor_long;
                valor_long<<=32;
                frame->pilha = retirar_da_pilha(frame->pilha,&valor);
                valor_long|=valor;
                t.u = valor;
                valor2 = valor;

                if (strcmp("println",nomeMetodo)==0)
                    if((valor1 == 0xFFFFFFFF) || (valor1 == 0)) {
                        if(valor2 < 65536)
                            printf("%d", t.i);
                    } else {

                    }
                else
                    if((valor1 == 0xFFFFFFFF) || (valor1 == 0)) {
                        if(valor2 < 65536)
                            printf("%d", t.i);
                    } else {

                    }
                i++;
                break;

            case 'L':
                frame->pilha = retirar_da_pilha(frame->pilha,&valor);
                string=(u1*)valor; /* valor na pilha eh o endereco da string a ser printada */
                if (strcmp("println",nomeMetodo)==0)
                    printf("%s",string);
                else
                    printf("%s",string);
                while (nomeDescritor[i]!=';') i++;
                break;

            default:
                i++;
                break;
            }

        }
        if (strcmp("println",nomeMetodo)==0) printf("\n");

    }
    else
    {

        /*procurar a classe para ver se já foi iniciada*/
        classe_iniciada = 0;
        for (i = 0; i < qtd_classes ; i++)
        {
            if( strcmp((char*)classlist[i].class_name, nomeClasse)==0)
            {
                classe_iniciada=1;
                break;
            }
        }

        if(!classe_iniciada)
        {
            fprintf(stderr, "BRUUUUBLES\n");
            exit(ERROR);
        }

        while(1)
        {
            /* localizar o metodo nesta classe */
            qtd_metodos = classlist[i].classe->methods_count;
            for (j = 0; j < qtd_metodos; j++)
            {

                indiceMetodoPesq = classlist[i].classe->methods[j].name_index;
                nomeMetodoPesq   = (char*) classlist[i].classe->constant_pool[indiceMetodoPesq-1].info.utf8_info.bytes;

                indiceDescritorPesq = classlist[i].classe->methods[j].descriptor_index;
                nomeDescritorPesq   = (char*) classlist[i].classe->constant_pool[indiceDescritorPesq-1].info.utf8_info.bytes;

                if ( (strcmp(nomeMetodo,nomeMetodoPesq)==0) && (strcmp(nomeDescritor,nomeDescritorPesq)==0) )
                {
                    metodo = &classlist[i].classe->methods[j];
                    frame_aux = (frame_execucao*) iniciar_frame (classlist[i].classe,metodo);
#ifdef DEBUG
                    printf ("     => vai executar metodo %s da classe %s.\n",nomeMetodoPesq,(char*)classlist[i].class_name);
#endif
                    executar_metodo(frame_aux);
                    return 0;
                }
            }


            /* nao encontrou - procura na super classe */
            indiceSuperClasse = classlist[i].classe->super_class;
            indiceSuperClasse = classlist[i].classe->constant_pool[indiceSuperClasse-1].info.class_info.name_index;
            nomeSuperClasse = (char*)classlist[i].classe->constant_pool[indiceSuperClasse-1].info.utf8_info.bytes;

            classe_iniciada = 0;
            for (i = 0; i < qtd_classes ; i++)
            {
                if( strcmp((char*)classlist[i].class_name,nomeSuperClasse)==0)
                {
                    classe_iniciada=1;
                    break;
                }
            }
        }
    }

    return 0;
}

/* 0xb7 */
/* chama execucao de metodo */
int invokespecial(frame_execucao * frame)
{

    int i , j , qtd_metodos , classe_iniciada;
    u1 byte1, byte2;
    u2 indice = 0, indiceClasse , indiceMetodo , indiceDescritor , indiceMetodoPesq , indiceDescritorPesq;
    u4 valor;
    char *nomeClasse , *nomeMetodo , *nomeDescritor , *nomeMetodoPesq , *nomeDescritorPesq;
    frame_execucao *frame_aux;
    t_method_info * metodo;
    char nomeCompleto[100];
    FILE *fp;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;

    /* indice aponta para uma constant pool do tipo Methodref */
    /* recupera dados do metodo - classe, metodo e descritor */
    indiceClasse = frame->constant_pool[indice-1].info.methodref_info.class_index;
    indiceClasse = frame->constant_pool[indiceClasse-1].info.class_info.name_index;
    nomeClasse = (char*) frame->constant_pool[indiceClasse-1].info.utf8_info.bytes;

    indice = frame->constant_pool[indice-1].info.methodref_info.name_and_type_index;
    indiceMetodo = frame->constant_pool[indice-1].info.nameandtype_info.name_index;
    nomeMetodo = (char*) frame->constant_pool[indiceMetodo-1].info.utf8_info.bytes;

    indiceDescritor = frame->constant_pool[indice-1].info.nameandtype_info.descriptor_index;
    nomeDescritor = (char*) frame->constant_pool[indiceDescritor-1].info.utf8_info.bytes;

    /* se for o metodo init não faz nada */
    /* se nao for, deve executar o metodo - TODO*/
    if ( (strcmp("java/lang/Object",nomeClasse)==0) && (strcmp("<init>",nomeMetodo)==0) )
    {

        frame->pilha = retirar_da_pilha(frame->pilha,&valor);
        return 0;

    }

    /*procurar a classe para ver se já foi iniciada*/
    classe_iniciada = 0;
    for (i = 0; i < qtd_classes ; i++)
    {

        if(strcmp((char*)classlist[i].class_name,nomeClasse)==0)
        {
            classe_iniciada=1;
            break;
        }
    }

    /* iniciar classe, se nao tiver sido iniciada */
    if (classe_iniciada == 0)
    {

        strcpy(nomeCompleto,classpath);
        strcat(nomeCompleto,nomeClasse);
        strcat(nomeCompleto,".class");

        fp = fopen(nomeCompleto,"rb");
        if (fp == NULL)
        {
            fprintf(stderr,"Erro ao abrir arquivo %s.\n",nomeCompleto);
            exit(ERROR);
        }

        leitura_classfile(fp);
        fclose(fp);

        /*procurar novamente a classe*/
        classe_iniciada = 0;
        for (i = 0; i < qtd_classes ; i++)
        {

            if(strcmp((char*)classlist[i].class_name,nomeClasse)==0)
            {
                classe_iniciada=1;
                break;
            }
        }
    }

    if (classe_iniciada == 0)
    {
        fprintf(stderr,"ERRO em invokespecial. Classe nao foi carregada corretamente.\n");
        exit(ERROR);
    }



    /* localizar o metodo nesta classe */
    qtd_metodos = classlist[i].classe->methods_count;

    for (j = 0; j < qtd_metodos; j++)
    {

        indiceMetodoPesq = classlist[i].classe->methods[j].name_index;
        nomeMetodoPesq   = (char*) classlist[i].classe->constant_pool[indiceMetodoPesq-1].info.utf8_info.bytes;

        indiceDescritorPesq = classlist[i].classe->methods[j].descriptor_index;
        nomeDescritorPesq   = (char*) classlist[i].classe->constant_pool[indiceDescritorPesq-1].info.utf8_info.bytes;

        if ( (strcmp(nomeMetodo,nomeMetodoPesq)==0) && (strcmp(nomeDescritor,nomeDescritorPesq)==0) )
        {
            metodo = &classlist[i].classe->methods[j];
            frame_aux = (frame_execucao*) iniciar_frame (classlist[i].classe,metodo);
#ifdef DEBUG
            printf ("     => vai executar metodo %s da classe %s.\n",nomeMetodo,nomeClasse);
#endif
            executar_metodo(frame_aux);
            return 0;
        }


    }

    fprintf(stderr,"ERRO. Metodo nao localizado para invokespecial.\n");
    exit(ERROR);

    return 0;

}

/* 0xb8 */
/* Executa método estático */
int invokestatic(frame_execucao * frame)
{

    int i, j, classe_carregada, qtd_metodos;
    u1 byte1, byte2;
    u2 indice = 0, indiceClasse , indiceMetodo , indiceDescritor;
    u2 indiceMetodoPesq , indiceDescritorPesq;
    char *nomeClasse , *nomeMetodo , *nomeDescritor;
    char *nomeMetodoPesq , *nomeDescritorPesq;
    frame_execucao *frame_aux;
    t_method_info * metodo;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;

    indiceClasse = frame->constant_pool[indice-1].info.methodref_info.class_index;
    indiceClasse = frame->constant_pool[indiceClasse-1].info.class_info.name_index;
    nomeClasse = (char*) frame->constant_pool[indiceClasse-1].info.utf8_info.bytes;

    indice = frame->constant_pool[indice-1].info.methodref_info.name_and_type_index;
    indiceMetodo = frame->constant_pool[indice-1].info.nameandtype_info.name_index;
    nomeMetodo = (char*) frame->constant_pool[indiceMetodo-1].info.utf8_info.bytes;

    indiceDescritor = frame->constant_pool[indice-1].info.nameandtype_info.descriptor_index;
    nomeDescritor = (char*) frame->constant_pool[indiceDescritor-1].info.utf8_info.bytes;

    /* verifica se classe ja esta carregada */

    for (i = 0; i < qtd_classes; i++)
    {
        if(strcmp((char*)classlist[i].class_name,nomeClasse)==0)
        {
            classe_carregada=1;
            break;
        }
    }

    if (classe_carregada == 0)
    {
        fprintf(stderr,"TODO - inicializar classe.");
        exit(ERROR);
    }

    /* TODO - testar se metodo eh estatico */

    qtd_metodos = classlist[i].classe->methods_count;
    j=0;

    for (j = 0; j < qtd_metodos; j++)
    {

        indiceMetodoPesq = classlist[i].classe->methods[j].name_index;
        nomeMetodoPesq   = (char*) classlist[i].classe->constant_pool[indiceMetodoPesq-1].info.utf8_info.bytes;

        indiceDescritorPesq = classlist[i].classe->methods[j].descriptor_index;
        nomeDescritorPesq   = (char*) classlist[i].classe->constant_pool[indiceDescritorPesq-1].info.utf8_info.bytes;

        if ( (strcmp(nomeMetodo,nomeMetodoPesq)==0) && (strcmp(nomeDescritor,nomeDescritorPesq)==0) )
        {
            metodo = &classlist[i].classe->methods[j];
            frame_aux = (frame_execucao*) iniciar_frame (classlist[i].classe,metodo);
            executar_metodo(frame_aux);
            return 0;
        }


    }

    fprintf(stderr,"ERRO. Metodo nao localizado para invokestatic.\n");
    exit(ERROR);

}


/* 0xbb*/
/* cria nova instancia da classe */
int new_ (frame_execucao * frame)
{

    int i , classe_iniciada;
    u1 byte1, byte2;
    u2 indice = 0, indiceClasse;
    u4 valor;
    char *nomeClasse;
    char nomeCompleto[100];
    FILE *fp;
    instance *new_instance;

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;

    indiceClasse = frame->constant_pool[indice-1].info.class_info.name_index;
    nomeClasse = (char*) frame->constant_pool[indiceClasse-1].info.utf8_info.bytes;

    /* verifica se classe ja foi iniciada */
    classe_iniciada=0;
    for (i = 0; i <qtd_classes; i++)
    {
        if ( strcmp((char*)classlist[i].class_name,nomeClasse)==0)
        {
            classe_iniciada=1;
            break;
        }
    }

    /* iniciar classe, se nao tiver sido iniciada */
    if (classe_iniciada == 0)
    {

        strcpy(nomeCompleto,classpath);
        strcat(nomeCompleto,nomeClasse);
        strcat(nomeCompleto,".class");

        fp = fopen(nomeCompleto,"rb");
        if (fp == NULL)
        {
            fprintf(stderr,"Erro ao abrir arquivo %s.\n",nomeCompleto);
            exit(ERROR);
        }

        leitura_classfile(fp);
        fclose(fp);

    }

    new_instance = (instance*)inserir_nova_instancia(nomeClasse);
#ifdef DEBUG
    printf ("     => criada instancia da classe %s\n",nomeClasse);
#endif
    valor = (u4)new_instance;

    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    return 0;
}


/* 0xbc */
/* cria novo array */
int newarray (frame_execucao * frame)
{

    int i;
    u4 count = 0 , atype = 0 , referencia = 0;
    u1 * array_u1;
    u2 * array_short;
    int * array_int;
    char * array_char;
    float * array_float;
    long long * array_long;
    double * array_double;
    array * new_array;

    frame->pilha = retirar_da_pilha (frame->pilha,&count);
    atype = frame->code[frame->pc++];

    /* inicializa novo array */
    new_array = malloc(sizeof(array));
    new_array->array = NULL;
    new_array->tam_array = count;
    new_array->tipo_array = atype;


    switch (atype)
    {

    case 4 : /* array de boolean */
    case 8 : /* array de byte */
        array_u1 = calloc (count,sizeof(u1));
        for (i=0; i<count; i++) array_u1[i] = 0;
        new_array->array = array_u1;
#ifdef DEBUG
        printf ("     => novo array de byte/boolean de tamanho %u\n",count);
#endif
        break;

    case  5: /* array de char */
        array_char = calloc (count,sizeof(char));
        for (i=0; i<count; i++) array_char[i] = ' ';
        new_array->array = array_char;
#ifdef DEBUG
        printf ("     => novo array de char de tamanho %u\n",count);
#endif
        break;


    case  6: /* array de float */
        array_float = calloc (count,sizeof(float));
        for (i=0; i<count; i++) array_float[i] = 0;
        new_array->array = array_float;
#ifdef DEBUG
        printf ("     => novo array de float de tamanho %u\n",count);
#endif
        break;

    case  7: /* array de double */
        array_double = calloc (count,sizeof(double));
        for (i=0; i<count; i++) array_double[i] = 0;
        new_array->array = array_double;
#ifdef DEBUG
        printf ("     => novo array de double de tamanho %u\n",count);
#endif
        break;

    case 9: /* array de short */
        array_short = calloc (count,sizeof(short));
        for (i=0; i<count; i++) array_short[i] = 0;
        new_array->array = array_short;
#ifdef DEBUG
        printf ("     => novo array de short de tamanho %u\n",count);
#endif
        break;

    case 10: /* array de inteiro */
        array_int = calloc (count,sizeof(int));
        for (i=0; i<count; i++) array_int[i] = 0;
        new_array->array = array_int;
#ifdef DEBUG
        printf ("     => novo array de inteiro de tamanho %u\n",count);
#endif
        break;

    case 11: /* array de long */
        array_long = calloc (count,sizeof(long long));
        for (i=0; i<count; i++) array_long[i] = 0;
        new_array->array = array_long;
#ifdef DEBUG
        printf ("     => novo array de long de tamanho %u\n",count);
#endif
        break;

    default:
        fprintf(stderr,"ERRO em newarray. Tipo de dado desconhecido.\n");
        exit(ERROR);
        break;

    }

    /* empilha endereço do array na pilha de execução */
    referencia = (u4)new_array;
    frame->pilha = inserir_na_pilha(frame->pilha,referencia);

    /* empilha array na pilha de arrays do heap */
    if (arrays==NULL)
    {
        arrays = malloc(sizeof(array));
        arrays->array_info = new_array;
        arrays->next = NULL;
    }
    else
    {
        arrays->next = arrays;
        arrays->array_info = new_array;
    }

    return 0;
}

/* 0xbd */
/* cria novo array de referencias */
int anewarray (frame_execucao * frame)
{

    int i;
    u4 count=0 , byte1 = 0 , byte2=0 , indice = 0  , referencia=0;
    u4 * array_u4;
    array * new_array;

    frame->pilha = retirar_da_pilha (frame->pilha,&count);

    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    indice =  (byte1 << 8) | byte2;

    /* inicializa novo array */
    new_array = malloc(sizeof(array));
    new_array->array = NULL;
    new_array->tam_array = count;
    new_array->tipo_array = 12; /*referencia - criado nesta implementacao */

    array_u4 = calloc (count,sizeof(u4));
    for (i=0; i<count; i++) array_u4[i] = 0;
    new_array->array = array_u4;
#ifdef DEBUG
    printf ("     => novo array de referencia de tamanho %u\n",count);
#endif

    /* empilha endereço do array na pilha de execução */
    referencia = (u4)new_array;
    frame->pilha = inserir_na_pilha(frame->pilha,referencia);

    /* empilha array na pilha de arrays do heap */
    if (arrays==NULL)
    {
        arrays = malloc(sizeof(array));
        arrays->array_info = new_array;
        arrays->next = NULL;
    }
    else
    {
        arrays->next = arrays;
        arrays->array_info = new_array;
    }

    return 0;
}

/*0xbe*/
/*empilha tamanho do array recebido*/
int arraylength (frame_execucao * frame)
{

    u4 referencia = 0, tam_array = 0;
    array * array;

    frame->pilha=retirar_da_pilha(frame->pilha,&referencia);

    array=(struct tipo_array*)referencia;

    tam_array = array->tam_array;

    frame->pilha=inserir_na_pilha(frame->pilha,tam_array);

    return 0;


}


/* 0xc6*/
/* se referencia retirada da pilha for nula, pula para instrucao */
int ifnull(frame_execucao * frame)
{

    void * referencia;
    u4 endereco = 0;
    u1 byte1=0 , byte2=0;
    u4 valor = 0;

    /* offset de pulo da instrucao */
    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    valor =  (byte1 << 8) | byte2;

    /* retira referencia da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&endereco);
    referencia = (void*)endereco;

    if (referencia==NULL)
    {
        frame->pc = frame->pc + valor;
        return 0;
    }
    else
    {
        return 0;
    }

}

/* 0xc7*/
/* se referencia retirada da pilha nao for nula, pula para instrucao */
int ifnonnull(frame_execucao * frame)
{

    void * referencia;
    u4 endereco = 0;
    u1 byte1=0 , byte2=0;
    u4 valor = 0;

    /* offset de pulo da instrucao */
    byte1 = frame->code[frame->pc++];
    byte2 = frame->code[frame->pc++];
    valor =  (byte1 << 8) | byte2;

    /* retira referencia da pilha */
    frame->pilha = retirar_da_pilha(frame->pilha,&endereco);
    referencia = (void*)endereco;

    if (referencia==NULL)
    {
        return 0;

    }
    else
    {

        frame->pc = frame->pc + valor;
        return 0;
    }

}

/*0xc9*/
/*jump subroutine */
int jsr_w(frame_execucao * frame)
{

    u4 branchbyte1=0,branchbyte2=0,branchbyte3=0,branchbyte4=0;
    u4 pulo = 0,valor=0;

    branchbyte1=frame->code[frame->pc++];
    branchbyte2=frame->code[frame->pc++];
    branchbyte3=frame->code[frame->pc++];
    branchbyte4=frame->code[frame->pc++];
    pulo = (branchbyte1 << 24) | (branchbyte2 << 16) | (branchbyte3 << 8) | branchbyte4;

    /* guarda endereco da proxima instrucao na pilha */
    valor = frame->pc;
    frame->pilha = inserir_na_pilha(frame->pilha,valor);

    /* pula instrucao */
    frame->pc = frame->pc + pulo;

    return 0;

}


pilha_u4 * inserir_na_pilha (pilha_u4 * pilha, u4 valor)
{

    pilha_u4 *novo;

    if (pilha == NULL)
    {
        pilha = malloc (sizeof(pilha_u4));
        pilha->valor = valor;
        pilha->next = NULL;
    }
    else
    {
        novo = malloc (sizeof(pilha_u4));
        novo->valor = valor;
        novo->next = pilha;
        pilha = novo;
    }
#ifdef DEBUG
    printf ("     => inserido na pilha: %u\n", valor);
#endif

    return pilha;

}

pilha_u4 * retirar_da_pilha (pilha_u4 * pilha , u4 * valor)
{

    pilha_u4 * aux;

    if (pilha == NULL)
    {
        fprintf(stderr,"Pilha esta vazia. Erro ao remover da pilha.\n");
        exit(ERROR);
    }
    else
    {
        *valor = (u4)pilha->valor;
        aux = pilha;
        pilha = pilha->next;
        free(aux);
    }
#ifdef DEBUG
    printf("     => retirado da pilha: %u\n", *valor);
#endif

    return pilha;

}

float converte_para_float (u4 valor)
{

    /* int bits,s,e,m; */
    float retorno=0.0;
    tipo_float valor_float;

    /* bits=valor;
     s = ((bits >> 31) == 0) ? 1 : -1;
     e = ((bits >> 23) & 0xff);
     m = (e == 0) ? (bits & 0x7fffff) << 1 : (bits & 0x7fffff) | 0x800000;
     retorno = s * m * pow(2,e-150);*/

    valor_float.i = valor;
    retorno = valor_float.f;

    return retorno;

}

double converte_para_double (long long valor)
{

    /*long long bits , s , e , m; */
    double retorno;
    tipo_double valor_double;

    /*  bits = valor;

      s = ((bits >> 63) == 0) ? 1 : -1;
      e = ((bits >> 52) & 0x7ffL);
      m = (e == 0) ? (bits & 0xfffffffffffffL) << 1 :	(bits & 0xfffffffffffffL) | 0x10000000000000L;
      retorno =  s * m * pow (2,e-1075); */

    valor_double.l = valor;
    retorno = valor_double.d;

    return retorno;

}

