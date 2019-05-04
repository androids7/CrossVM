#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "class.h"
#include "estruturas.h"
#include "globais.h"
#include "execucao.h"
#include "auxiliar.h"
#include "funcoes.h"


/* cria novo objeto (instancia) da classe
   as instancias sao criadas e empilhadas no class_list correspondente */
instance * inserir_nova_instancia(char * nomeClasse)
{

    int j , qtd_fields;
    instance * new_instance;
    class_list * classe_atual;
    char * tipoCampo;
    u2 indiceTipoCampo;

    /* localiza a classe cuja instancia deve ser criada - nome da classe eh recebida como parametro */
    classe_atual = (class_list*)localizar_classe_pelo_nome(nomeClasse);
    if (classe_atual == NULL)
    {
        fprintf(stderr,"ERRO. Classe inexistente. Instancia nao pode ser criada.\n");
        exit(ERROR);
    }

    /* inicializa estrutura */
    new_instance = malloc(sizeof(instance));
    new_instance->campos = NULL;
    new_instance->next  = NULL;

    qtd_fields = classe_atual->classe->fields_count;
    new_instance->qtd_campos = qtd_fields;

    /* monta os campos do objeto - se ele tiver */
    if (qtd_fields > 0)
    {

        new_instance->campos = (field_value*) calloc (qtd_fields,sizeof(field_value));

        for (j=0 ; j<qtd_fields ; j++)
        {

            new_instance->campos[j].info_campo = &classe_atual->classe->fields[j];
            new_instance->campos[j].constant_pool = classe_atual->classe->constant_pool;

            indiceTipoCampo = classe_atual->classe->fields[j].descriptor_index;
            tipoCampo = (char*)classe_atual->classe->constant_pool[indiceTipoCampo-1].info.utf8_info.bytes;

            if ((tipoCampo[0] == 'J') || (tipoCampo[0] == 'D'))
            {
                new_instance->campos[j].valor_campo = calloc (2,sizeof(u4));
                new_instance->campos[j].valor_campo[0]=0;
                new_instance->campos[j].valor_campo[1]=0;
            }
            else
            {
                new_instance->campos[j].valor_campo = malloc (sizeof(u4));
                new_instance->campos[j].valor_campo[0] = 0;
            }
        }
    }

    /* coloca a instancia na pilha de instancias de sua classe correspondente */

    if (classe_atual->instancias == NULL)
    {

        classe_atual->instancias = new_instance;

    }
    else
    {

        new_instance->next = classe_atual->instancias;
        classe_atual->instancias = new_instance->next;

    }

    return new_instance;

}


/* localiza metodo no constant_pool pelo seu nome */
t_method_info * localizar_metodo_pelo_nome (class_file * classfile , char * nome_metodo)
{

    int i , qtd_metodos, index;
    qtd_metodos = classfile->methods_count;

    for (i = 0 ; i<qtd_metodos ; i++)
    {
        index = classfile->methods[i].name_index;
        if (strcmp ((char*)classfile->constant_pool[index-1].info.utf8_info.bytes , nome_metodo) == 0 )
            return &classfile->methods[i];
    }

    return NULL;

}


/* localiza classe no class_list atraves de seu nome */
class_list * localizar_classe_pelo_nome (char * nomeClasse)
{

    int i;
    for (i=0 ; i<qtd_classes ; i++)
    {
        if (strcmp((char*)classlist[i].class_name,nomeClasse)==0)
            return &classlist[i];
    }

    return NULL;

}

/* inicia frame para execucao de metodo */
frame_execucao * iniciar_frame (class_file * classfile , t_method_info * metodo)
{

    u2 index;
    u4 valor,high,low;
    frame_execucao * new_frame;
    pilha_frame * novo_frame_atual;
    int i , achou_code , qtd_atributos, qtd_args, metodo_instancia, achou_referencia;
    char * descriptor , *nomeMetodo;

    /* inicia alocacao do frame */
    new_frame = (frame_execucao*) malloc (sizeof(frame_execucao));
    new_frame->classe = classfile;
    new_frame->metodo = metodo;
    new_frame->pc = 0;
    new_frame->constant_pool = classfile->constant_pool;

    /* procurar atributo do tipo code */
    qtd_atributos = metodo->attributes_count;
    achou_code = 0;

    for (i=0 ; i<qtd_atributos ; i++)
    {
        index = metodo->attributes[i].attribute_name_index;
        if (strcmp ((char*)classfile->constant_pool[index-1].info.utf8_info.bytes , "Code") == 0)
        {
            achou_code = 1;
            break;
        }
    }

    if (achou_code == 0)
    {
        fprintf(stderr, "ERRO! Metodo nao possui atributo Code.\n");
        exit(ERROR);
    }

    new_frame->code_length = metodo->attributes[i]._info.code.code_length;
    new_frame->code = metodo->attributes[i]._info.code.code;


    /*Vetor de variaveis locais*/
    new_frame->max_locals = metodo->attributes[i]._info.code.max_locals;
    new_frame->variaveis_locais = malloc (new_frame->max_locals * (sizeof (u4)));

    /* Pilha do frame */
    new_frame->tam_pilha = metodo->attributes[i]._info.code.max_stack;
    new_frame->pilha = NULL;

    /* Conta argumentos de entrada método */
    index = metodo->descriptor_index;
    descriptor = (char *) classfile->constant_pool[index-1].info.utf8_info.bytes;

    i = 0;
    qtd_args = new_frame->max_locals-1;
    achou_referencia = 0;

    while (descriptor[i]!=')')
    {

        valor = 0;

        switch (descriptor[i])
        {
        case 'B':
            frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&valor);
            new_frame->variaveis_locais[qtd_args] = valor;
            i++;
            qtd_args--;
            break;
        case 'C':
            frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&valor);
            new_frame->variaveis_locais[qtd_args] = valor;
            i++;
            qtd_args--;
            break;
        case 'D':
            frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&high);
            frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&low);
            new_frame->variaveis_locais[qtd_args] = low;
            qtd_args--;
            new_frame->variaveis_locais[qtd_args] = high;
            i++;
            qtd_args--;
            break;
        case 'F':
            frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&valor);
            new_frame->variaveis_locais[qtd_args] = valor;
            i++;
            qtd_args--;
            break;
        case 'I':
            frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&valor);
            new_frame->variaveis_locais[qtd_args] = valor;
            i++;
            qtd_args--;
            break;
        case 'J':
            frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&high);
            frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&low);
            new_frame->variaveis_locais[qtd_args] = low;
            qtd_args--;
            new_frame->variaveis_locais[qtd_args] = high;
            i++;
            qtd_args--;
            break;
        case 'L':
            i++;
            while (descriptor[i]!=';') i++;
            if (frames_em_execucao->frame != NULL)
            {
                frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&valor);
                new_frame->variaveis_locais[qtd_args] = valor;
            }
            qtd_args--;
            achou_referencia = 1;
            break;
        case 'S':
            frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&valor);
            new_frame->variaveis_locais[qtd_args] = valor;
            i++;
            qtd_args--;
            break;
        case 'Z':
            frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&valor);
            new_frame->variaveis_locais[qtd_args] = valor;
            i++;
            qtd_args--;
            break;
        default:
            i++;
            break;
        }

    }

    /* verifica se codigo tem getfield ou putfield - se tiver precisa passar o objeto na posicao 1 */
    metodo_instancia = 0;
    for (i=0 ; i<new_frame->code_length ; i++)
    {
        if ( (new_frame->code[i]==0xb4) || (new_frame->code[i]==0xb5) )
        {
            metodo_instancia = 1;
            break;
        }
    }

    /* metodo construtor deve ter o endereco do objeto na primeira posicao do vetor */
    nomeMetodo = (char*)classfile->constant_pool[metodo->name_index-1].info.utf8_info.bytes;
    if( ( (strcmp(nomeMetodo,"<init>")==0) || (metodo_instancia==1) ) && (strcmp(nomeMetodo,"main")!=0) )
    {
        valor=0;
        frames_em_execucao->frame->pilha = retirar_da_pilha(frames_em_execucao->frame->pilha,&valor);
        new_frame->variaveis_locais[0] = valor;
    }

    /* atualiza pilha de frames em execucao */
    novo_frame_atual = malloc (sizeof (pilha_frame));
    novo_frame_atual->frame = new_frame;
    novo_frame_atual->next  = frames_em_execucao;
    frames_em_execucao = novo_frame_atual;

    return new_frame;

}


void executar_metodo(frame_execucao * frame)
{
    int opcode=0;

    int (*vetorFuncoes[])(frame_execucao*) =
    {
        nop,aconst_null,iconst_m1,iconst_0,iconst_1,iconst_2,iconst_3,iconst_4,iconst_5,lconst_0,lconst_1,  /*10 */
        fconst_0,fconst_1,fconst_2,dconst_0,dconst_1,bipush,sipush,ldc,ldc_w,ldc2_w, /*20*/
        iload,lload,fload,dload,aload,iload_0,iload_1,iload_2,iload_3,lload_0,
        lload_1,lload_2,lload_3,fload_0,fload_1,fload_2,fload_3,dload_0,dload_1,dload_2, /*40*/
        dload_3,aload_0,aload_1,aload_2,aload_3,iaload,laload,faload,daload,aaload, /*50*/
        baload,caload,saload,istore,lstore,fstore,dstore,astore,istore_0,istore_1, /*60*/
        istore_2,istore_3,lstore_0,lstore_1,lstore_2,lstore_3,fstore_0,fstore_1,fstore_2,fstore_3, /*70 */
        dstore_0,dstore_1,dstore_2,dstore_3,astore_0,astore_1,astore_2,astore_3,iastore,lastore,   /* 80 */
        fastore,dastore,aastore,bastore,castore,sastore,pop,NULL,dup,dup_x1, /*90*/
        dup_x2,dup2,dup2_x1,dup2_x2,NULL,iadd,ladd,fadd,dadd,isub,   /*100 */
        lsub,fsub,dsub,imul,lmul,fmul,dmul,idiv,ldiv_,fdiv,ddiv,irem,lrem,frem,drem_,ineg,lneg,fneg,dneg,ishl,   /*120 */
        lshl,ishr,lshr,iushr,NULL,iand,land,ior,lor,ixor,lxor,iinc,i2l,i2f,i2d,l2i,l2f,l2d,f2i,f2l,   /*140 */
        f2d,d2i,d2l,d2f,i2b,i2c,i2s,lcmp,fcmpl,fcmpg,dcmpl,dcmpg,ifeq,ifne,iflt,ifge,ifgt,ifle,if_icmpeq,if_icmpne,   /* 160 */
        if_icmplt,if_icmpge,if_icmpgt,if_icmple,NULL,NULL,goto_,NULL,ret,tableswitch,    /*170*/
        lookupswitch,ireturn,lreturn,freturn,dreturn,areturn,return_,getstatic,putstatic,getfield, /*180 */
        putfield,invokevirtual,invokespecial,invokestatic,NULL,NULL,new_,newarray,anewarray,arraylength, /*190*/
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,ifnull,ifnonnull,NULL, /*200*/
        jsr_w,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
    };


    while (frame->pc < frame->code_length)
    {

        opcode = frame->code[frame->pc++];
        #ifdef DEBUG
        printf("\nDEBUG=> OPCODE: 0x%x (%s)\n", opcode , (char *)VetorNomeFuncoes[opcode]);
        #endif

        if ( vetorFuncoes[opcode] == 0)
        {
            fprintf(stderr,"Funcao %s nao implementada. (%x/%d)\n", VetorNomeFuncoes[opcode],opcode,(int)opcode);
            exit(ERROR);
        }

        vetorFuncoes[opcode](frame);

        STOP

    }
    return ;

}

