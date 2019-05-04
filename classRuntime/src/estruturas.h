#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_

#include "class.h"

/* Estrutura da pilha de execução dos métodos */
typedef struct pilha_u4
{
    u4 valor;
    struct pilha_u4 * next;
} pilha_u4;


/* frame de execucao do metodo */
typedef struct tipo_frame
{
    class_file * classe;
    t_method_info * metodo;
    t_cp_info * constant_pool;
    u4 pc;
    u4 code_length;
    u1 * code;
    u4 max_locals;
    u4 * variaveis_locais;
    u4 tam_pilha;
    pilha_u4 * pilha;
} frame_execucao;

/* pilha de frames */
typedef struct tipo_pilha_frame
{
    frame_execucao * frame;
    struct tipo_pilha_frame *next;
} pilha_frame;

/* estrutura dos campos */
typedef struct
{
    t_cp_info * constant_pool;    /* constant_pool vinculado ao campo */
    t_field_info * info_campo;    /* info do campo */
    u4 * valor_campo;             /* valor do campo */
} field_value;

/* estrutura da instancia */
typedef struct tipo_instancia
{
    field_value * campos;          /* vetor com os campos do objeto */
    int qtd_campos;                /* quantidades de campos no vetor de campos */
    struct tipo_instancia * next;  /* ponteiro para a proxima instancia da pilha */
} instance;

/* lista de classes carregadas e suas instancias */
typedef struct lista_classe
{
    class_file * classe;
    u1 * class_name;
    int qtd_instancias;     /* qtd de instancias na pilha de instancias */
    instance * instancias;  /* pilha de instancias */
} class_list;


/* estrutura dos arrays */
typedef struct tipo_array
{

    void * array;
    int tam_array;
    u4 tipo_array;

} array;

/* estrutura da pilha de arrays. deve ficar no heap */
typedef struct tipo_pilha_array
{

    array * array_info;
    struct tipo_pilha_array * next;

} pilha_array;

/*estrutura para campos estaticos */
typedef struct pilha_s{

    char * nomeCampo;
    char * tipoCampo;
    u4 * valorCampo;
    struct pilha_s * next;

} static_pilha;

#endif
