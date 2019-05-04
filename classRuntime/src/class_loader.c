#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "class_loader.h"
#include "auxiliar.h"
#include "globais.h"
#include "funcoes.h"


void leitura_classfile(FILE *fp)
{

    u2 count;
    u2 index_classe;
    u2 index_utf8;
    int i, index;
    u1 tagvalue;
    class_file * classfile;

    /* inicia o ponteiro para funcoes e as posicoes sao os valores do tag, para pode passa-lo nos indices para chamar a funcao
           apropriada */
    /* vetor de ponteiros para as funcoes */
    int (*vetFuncoes[])(t_cp_info*, FILE*, int) =
    {
        NULL, butf8, NULL, binteger, bfloat, blong, bdouble, bclass, bstring, bfieldref,
        bmethodref, binterfacemethodref, bnamenadtype
    };


    /* aloca o espaco do classfile */
    classfile = (class_file*) malloc(sizeof(class_file));

    /* verifica se o numero magico eh CAFEBABE */
    classfile->magic = readu4(fp);
    if(classfile->magic != 0xCAFEBABE)
    {
        fprintf(stderr, "O arquivo informado eh invalido.\n");
        exit(INVALID_FILE_FORMAT);
    }

    /* verifica a minor_version */
    classfile->minor_version = readu2(fp);
    /* verifica a major_version */
    classfile->major_version = readu2(fp);

    /* TODO - corrigir teste abaixo!! */
    if (classfile->major_version >= 55)
    {
        fprintf(stderr,"Erro na versao.\n");
        exit (ERROR);
    }

    /* verifica quantidade do pool de constantes */
    classfile->constant_pool_count = readu2(fp);
    count = classfile->constant_pool_count;

    /* atribui este ponteiro para um vetor de count elementos */
    classfile->constant_pool = (t_cp_info*) calloc(count, sizeof(t_cp_info));

    /* faz um loop e para cada iteracao, salva na posicao corrente do vetor de structs o cp_info lido */
    for (i = 0; i < count - 1; i++)
    {
        /* le a tag da cp_info */
        tagvalue=readu1(fp);
        /* aplica a funcao determinada pela tag */
        i = vetFuncoes[tagvalue](classfile->constant_pool, fp, i);
    }

    /* verifica flag de acesso */
    classfile->access_flags = readu2(fp);

    /* verifica nome/dados da classe corrente */
    classfile->this_class = readu2(fp);

    /* verifica nome/dados da super classe */
    classfile->super_class = readu2(fp);

    /* verifica quantidade de interfaces */
    classfile->interfaces_count = readu2(fp);
    count = classfile->interfaces_count;

    if (count > 0)
    {
        /* aloca espaco para as interfaces */
        classfile->interfaces = (u2*) calloc(count, sizeof(u2));
        if (!classfile->interfaces)
        {
            fprintf(stderr, "OutOfMemoryError.\n");
            exit(-4);
        }

        /* verifica as interfaces */
        for (i=0; i<count; i++)
            classfile->interfaces[i] = readu2(fp);
    }


    /* verifica quantidade de fields */
    classfile->fields_count = readu2(fp);
    count = classfile->fields_count;

    if (count>0)
    {

        /* aloca espaço para os fields */
        classfile->fields = (t_field_info*) calloc(count, sizeof(t_field_info));

        /* leitura dos fields */
        for (i=0; i<count; i++)
            leitura_dos_fields(&classfile->fields[i], fp, classfile);

    }

    /* verifica quantidade de metodos */
    classfile->methods_count = readu2(fp);
    count = classfile->methods_count;

    if (count>0)
    {
        /* aloca o espaço dos metodos */
        classfile->methods = (t_method_info*) calloc(count, sizeof(t_method_info));

        /* leitura dos metodos */
        for (i = 0; i < count; i++)
            leitura_dos_metodos(&classfile->methods[i], fp, classfile);
    }

    /* verifica quantidade de atributos da classe */
    classfile->attributes_count = readu2(fp);
    count = classfile->attributes_count;

    if (count>0)
    {
        /*aloca espaço para os atributos da classe */
        classfile->attributes = (t_attribute_info*) calloc(count, sizeof(t_attribute_info));

        /* leitura dos atributos da classe */
        for (i=0; i<count; i++)
            leitura_dos_atributos(&classfile->attributes[i],fp, classfile);
    }


    /* insere classe na lista de classes carregadas */

    if (qtd_classes == 0)
    {

        qtd_classes++;
        classlist = (class_list*) malloc (sizeof(class_list));
        classlist[0].classe = classfile;

        /* recupera nome da classe */
        index_classe =  classlist[0].classe->this_class;
        index_utf8 = classlist[0].classe->constant_pool[index_classe-1].info.class_info.name_index;
        classlist[0].class_name = classlist[0].classe->constant_pool[index_utf8-1].info.utf8_info.bytes;
        classlist[0].qtd_instancias = 0;
        classlist[0].instancias = NULL;

    }
    else
    {

        qtd_classes++;
        index = qtd_classes-1;
        classlist = (class_list*) realloc (classlist , qtd_classes*sizeof(class_list));
        classlist[index].classe = classfile;

        /* recupera nome da classe */
        index_classe =  classlist[index].classe->this_class;
        index_utf8 = classlist[index].classe->constant_pool[index_classe-1].info.class_info.name_index;
        classlist[index].class_name = classlist[index].classe->constant_pool[index_utf8-1].info.utf8_info.bytes;
        classlist[index].qtd_instancias = 0;
        classlist[index].instancias = NULL;

    }


}

/* ========== FUNCOES DE LEITURA DOS DADOS DO CONSTANT POLL (do vetor de funcoes) ===================== */

int bclass(t_cp_info* info, FILE* fp, int position)
{
    u2 name_index;
    info[position].tag = 7;
    name_index = readu2(fp);
    info[position].info.class_info.name_index = name_index;
    return position;
}
int bfieldref(t_cp_info* info, FILE* fp, int position)
{
    u2 class_index;
    u2 name_and_type_index;
    info[position].tag = 9;
    class_index = readu2(fp);
    info[position].info.fieldref_info.class_index = class_index;
    name_and_type_index = readu2(fp);
    info[position].info.fieldref_info.name_and_type_index = name_and_type_index;
    return position;
}
int bmethodref(t_cp_info* info, FILE* fp, int position)
{
    u2 class_index;
    u2 name_and_type_index;
    info[position].tag = 10;
    class_index = readu2(fp);
    info[position].info.methodref_info.class_index = class_index;
    name_and_type_index = readu2(fp);
    info[position].info.methodref_info.name_and_type_index =
        name_and_type_index;
    return position;
}
int binterfacemethodref(t_cp_info* info, FILE* fp, int position)
{
    u2 class_index;
    u2 name_and_type_index;
    info[position].tag = 11;
    class_index = readu2(fp);
    info[position].info.interfacemethod_info.class_index = class_index;
    name_and_type_index = readu2(fp);
    info[position].info.interfacemethod_info.name_and_type_index =
        name_and_type_index;
    return position;
}
int bstring(t_cp_info* info, FILE* fp, int position)
{
    u2 string_index;
    info[position].tag = 8;
    string_index = readu2(fp);
    info[position].info.string_info.string_index = string_index;
    return position;
}
int binteger(t_cp_info* info, FILE* fp, int position)
{
    u4 bytes;
    info[position].tag = 3;
    bytes = readu4(fp);
    info[position].info.integer_info.bytes = bytes;
    return position;
}
int bfloat(t_cp_info* info, FILE* fp, int position)
{
    u4 bytes;
    info[position].tag = 4;
    bytes = readu4(fp);
    info[position].info.float_info.bytes = bytes;
    return position;
}
int blong(t_cp_info* info, FILE* fp, int position)
{
    u4 high_bytes;
    u4 low_bytes;
    info[position].tag = 5;
    high_bytes = readu4(fp);
    low_bytes = readu4(fp);
    info[position].info.long_info.high_bytes = high_bytes;
    info[position].info.long_info.low_bytes = low_bytes;
    return position + 1;
}
int bdouble(t_cp_info* info, FILE* fp, int position)
{
    u4 high_bytes;
    u4 low_bytes;
    info[position].tag = 6;
    high_bytes = readu4(fp);
    low_bytes = readu4(fp);
    info[position].info.double_info.high_bytes = high_bytes;
    info[position].info.double_info.low_bytes = low_bytes;
    return position + 1;
}
int bnamenadtype(t_cp_info* info, FILE* fp, int position)
{
    u2 name_index;
    u2 descriptor_index;
    info[position].tag = 12;
    name_index = readu2(fp);
    info[position].info.nameandtype_info.name_index = name_index;
    descriptor_index = readu2(fp);
    info[position].info.nameandtype_info.descriptor_index = descriptor_index;
    return position;
}
int butf8(t_cp_info* info, FILE* fp, int position)
{
    u2 length;
    u1* bytes;
    info[position].tag = 1;
    length = readu2(fp);
    info[position].info.utf8_info.length = length;
    bytes = (u1*) malloc(length * sizeof(u1) + 1);
    fread(bytes, sizeof(u1), length, fp);
    bytes[length] = '\0';
    info[position].info.utf8_info.bytes = bytes;
    return position;
}

/* ====== FIM DAS FUNCOES DE LEITURA DO CONSTANT POOL ======================= */

void leitura_dos_metodos(t_method_info * method , FILE *fp, class_file * classfile)
{

    int count, i;

    method->access_flags = readu2(fp);

    method->name_index = readu2(fp);

    method->descriptor_index = readu2(fp);

    method->attributes_count = readu2(fp);
    count = method->attributes_count;

    /* aloca espaco para atributos do m\E9todo */
    method->attributes = (t_attribute_info*) calloc(count, sizeof(t_attribute_info));

    if (!method->attributes)
    {
        fprintf(stderr, "OutOfMemoryError.\n");
        exit(-4);
    }

    /* leitura dos atributos do metodo */
    for (i = 0; i < count; i++)
    {
        leitura_dos_atributos(&method->attributes[i],fp, classfile);
    }

}

void leitura_dos_atributos (t_attribute_info * att , FILE *fp, class_file * classfile)
{

    int i;
    u2 index;
    u4 count;

    att->attribute_name_index = readu2(fp);
    index = att->attribute_name_index - 1;

    att->attribute_length = readu4(fp);

    /* atributo do tipo Code */
    if(strcmp((char*)classfile->constant_pool[index].info.utf8_info.bytes,"Code") == 0)
    {

        att->_info.code.attribute_name_index =  att->attribute_name_index;
        att->_info.code.attribute_length     =  att->attribute_length;

        att->_info.code.max_stack = readu2(fp);

        att->_info.code.max_locals = readu2(fp);

        att->_info.code.code_length = readu4(fp);
        count = att->_info.code.code_length;

        /* aloca espaco para o codigo */
        att->_info.code.code = (u1*) calloc(count, sizeof(u1));
        if (!att->_info.code.code )
        {
            fprintf(stderr, "OutOfMemoryError.\n");
            exit(-4);
        }

        /* leitura do codigo */
        for (i=0 ; i < count ; i++)
            att->_info.code.code[i] = readu1(fp);

        att->_info.code.exception_table_length = readu2(fp);

        /* TODO - leitura da tabela de excecoes - arquivo class atual nao possui */

        att->_info.code.attributes_count = readu2(fp);
        count = att->_info.code.attributes_count;

        /* aloca espaco para os atributos do codigo */
        att->_info.code.attributes = (t_attribute_info*) calloc(count, sizeof(t_attribute_info));
        if (!att->_info.code.attributes)
        {
            fprintf(stderr, "OutOfMemoryError.\n");
            exit(-4);
        }

        /* leitura dos atributos do codigo */
        for (i=0 ; i < count ; i++)
            leitura_dos_atributos(&att->_info.code.attributes[i],fp, classfile);


    } /* fim atributo tipo Code */

    /* Atributo do tipo LineNumberTable */
    if(strcmp((char*)classfile->constant_pool[index].info.utf8_info.bytes,"LineNumberTable") == 0)
    {

        att->_info.line_number_table.attribute_name_index =  att->attribute_name_index;
        att->_info.line_number_table.attribute_length     =  att->attribute_length;

        att->_info.line_number_table.line_number_table_length = readu2(fp);
        count = att->_info.line_number_table.line_number_table_length ;

        /* aloca espaco */
        att->_info.line_number_table.line_number_table = (t_line_number_table*) calloc(count, sizeof(t_line_number_table));
        if (!att->_info.line_number_table.line_number_table)
        {
            fprintf(stderr, "OutOfMemoryError.\n");
            exit(-4);
        }

        /* le o line number table */
        for (i=0; i<count; i++)
        {
            att->_info.line_number_table.line_number_table[i].start_pc = readu2(fp);
            att->_info.line_number_table.line_number_table[i].line_number = readu2(fp);
        }

    } /* fim atributo LineNumberTable */

    /* Atributo do tipo SourceFile */
    if(strcmp((char*)classfile->constant_pool[index].info.utf8_info.bytes,"SourceFile") == 0)
    {

        att->_info.sourcefile.attribute_name_index =  att->attribute_name_index;
        att->_info.sourcefile.attribute_length     =  att->attribute_length;
        att->_info.sourcefile.sourcefile_index     =  readu2(fp);

    }   /* fim atributo tipo SourceFile */

}


void leitura_dos_fields(t_field_info * field, FILE *fp, class_file * classfile)
{

    int i, count;

    field->access_flags = readu2(fp);

    field->name_index = readu2(fp);

    field->descriptor_index = readu2(fp);

    field->attributes_count = readu2(fp);
    count = field->attributes_count;

    if(count>0)
    {
        /*aloca espaco dos atributos*/
        field->attributes = (t_attribute_info*) calloc(count, sizeof(t_attribute_info));

        /*leitura dos atributos do field */
        for(i=0; i<count; i++)
            leitura_dos_atributos(&field->attributes[i],fp, classfile);

    }

}

void exibe_classfile(class_file * classfile)
{
    int i,j;
    u2 indice;
    u1 tag;
    char * string = (char*) malloc (200*sizeof(char));
    long long valor_long = 0;
    double valor_double = 0;

    printf("\nEXIBICAO DO .class\n\n");

    printf("minor_version.........: %u\n", classfile->minor_version);
    printf("major_version.........: %u\n", classfile->major_version);
    printf("constant_pool_count...: %u\n", classfile->constant_pool_count);
    string = recupera_nome_flag (classfile->access_flags);
    printf("access_flag...........: 0x%04x [%s]\n",classfile->access_flags,string);
    string = recupera_nome_classe(classfile->constant_pool, classfile->this_class);
    printf("this_class............: #%u [%s]\n", classfile->this_class,string);
    string = recupera_nome_classe(classfile->constant_pool, classfile->super_class);
    printf("super_class...........: #%u [%s]\n", classfile->super_class,string);
    printf("interfaces_count......: %u\n",classfile->interfaces_count);
    printf("fields_count..........: %u\n",classfile->fields_count);
    printf("methods_count.........: %u\n",classfile->methods_count);
    printf("attributes_count......: %u\n",classfile->attributes_count);

    printf("\n");


    for(i=0 ; i < classfile->constant_pool_count ; i++)
    {
        tag = classfile->constant_pool[i].tag;
        switch(tag)
        {
        case CONSTANT_Class:
            printf("[%2d] tag : 7 (CONSTANT_Class)\n",i+1);
            indice = classfile->constant_pool[i].info.class_info.name_index;
            string = recupera_string(classfile->constant_pool,indice);
            printf("name_index: #%u [%s]\n\n", indice,string);
            break;

        case CONSTANT_Fieldref:
            printf("[%2d] tag : 9 (CONSTANT_Fieldref)\n",i+1);
            indice = classfile->constant_pool[i].info.fieldref_info.class_index;
            string = recupera_nome_classe(classfile->constant_pool,indice);
            printf("class_index.........: #%u [%s]\n", indice,string);
            indice = classfile->constant_pool[i].info.fieldref_info.name_and_type_index;
            string = recupera_name_type(classfile->constant_pool,indice);
            printf("name_and_type_index.: #%u [%s]\n\n",  indice,string);
            break;

        case CONSTANT_Methodref:
            printf("[%2d] tag : 10 (CONSTANT_Methodref)\n",i+1);
            indice = classfile->constant_pool[i].info.methodref_info.class_index;
            string = recupera_nome_classe(classfile->constant_pool,indice);
            printf("class_index.........: #%u [%s]\n",indice,string);
            indice = classfile->constant_pool[i].info.methodref_info.name_and_type_index;
            string = recupera_name_type(classfile->constant_pool,indice);
            printf("name_and_type_index.: #%u [%s]\n\n",indice,string);
            break;

        case CONSTANT_InterfaceMethodref:
            printf("[%2d] tag : 11 (CONSTANT_InterfaceMethodref)", i+1);
            indice = classfile->constant_pool[i].info.interfacemethod_info.class_index;
            string = recupera_nome_classe(classfile->constant_pool,indice);
            printf("class_index.........: #%u [%s]\n", indice,string );
            indice = classfile->constant_pool[i].info.interfacemethod_info.name_and_type_index;
            string = recupera_name_type(classfile->constant_pool,indice);
            printf("name_and_type_index.: #%u [%s]\n\n", indice,string);
            break;

        case CONSTANT_String:
            printf("[%2d] tag : 8 (CONSTANT_String)\n", i+1);
            indice = classfile->constant_pool[i].info.string_info.string_index;
            string = recupera_string(classfile->constant_pool,indice);
            printf("string_index: #%u [%s]\n\n", indice,string);
            break;

        case CONSTANT_Integer:
            printf("[%2d] tag : 3 (CONSTANT_Integer)\n", i+1);
            printf("bytes: %x\n\n", classfile->constant_pool[i].info.integer_info.bytes);
            break;

        case CONSTANT_Float:
            printf("[%2d] tag : 4 (CONSTANT_Float)\n", i+1);
            printf("bytes: 0x%x\n\n", classfile->constant_pool[i].info.float_info.bytes);
            break;

        case CONSTANT_Long:
            printf("[%2d] tag : 5 (CONSTANT_Long)\n", i+1);
            printf("high_bytes.: 0x%x\n", classfile->constant_pool[i].info.long_info.high_bytes);
            printf("low_bytes..: 0x%x\n\n", classfile->constant_pool[i].info.long_info.low_bytes);

            valor_long = classfile->constant_pool[i].info.double_info.high_bytes ;
            valor_long<<=32;
            valor_long|=classfile->constant_pool[i].info.double_info.low_bytes;
            printf("Long.....: %lld\n\n",valor_long);
            i++;
            break;

        case CONSTANT_Double:
            printf("[%2d] tag : 6 (CONSTANT_Double)\n", i+1);
            printf("high_bytes.: 0x%x\n", classfile->constant_pool[i].info.double_info.high_bytes);
            printf("low_bytes..: 0x%x\n", classfile->constant_pool[i].info.double_info.low_bytes);

            valor_long = classfile->constant_pool[i].info.double_info.high_bytes ;
            valor_long<<=32;
            valor_long|=classfile->constant_pool[i].info.double_info.low_bytes;
            valor_double = converte_para_double(valor_long);

            printf("Double.....: %.3lf\n\n",valor_double);
            i++;
            printf("[%2d] (large numeric continued)\n", i+1);
            break;

        case CONSTANT_NameAndType:
            printf("[%2d] tag : 12 (CONSTANT_NameAndType)\n", i+1);
            indice = classfile->constant_pool[i].info.nameandtype_info.name_index;
            string = recupera_string(classfile->constant_pool,indice);
            printf("name_index.......: #%u [%s]\n", indice,string );
            indice = classfile->constant_pool[i].info.nameandtype_info.descriptor_index;
            string = recupera_string(classfile->constant_pool , indice );
            printf("descriptor_index.: #%u [%s]\n\n", indice,string);
            break;

        case CONSTANT_Utf8:
            printf("[%2d] tag : 1 (CONSTANT_Utf8)\n", i+1);
            printf("length: %u\n", classfile->constant_pool[i].info.utf8_info.length);
            printf("string: %s\n",classfile->constant_pool[i].info.utf8_info.bytes);
            printf("\n");
            break;

        default:
            break;
        } /* fim do switch */


    } /* fim do for */


    for (i=0; i<classfile->interfaces_count; i++)
    {
        printf("\t[%d] %u\n", i , classfile->interfaces[i]);
    }

    /* exibe fields */
    for (i=0; i<classfile->fields_count; i++)
    {
        printf("\nField %d\n\n",i+1);
        indice = classfile->fields[i].name_index;
        string = recupera_string(classfile->constant_pool,indice);
        printf("name_index........: #%u [%s]\n",indice,string);
        indice = classfile->fields[i].descriptor_index;
        string = recupera_string(classfile->constant_pool,indice);
        printf("descriptor_index..: #%u [%s]\n",indice,string);
        indice = classfile->fields[i].access_flags;
        string = recupera_nome_flag(indice);
        printf("access_flags......: 0x%04x [%s]\n",indice,string);
        printf("attributes count..: %u\n",classfile->fields[i].attributes_count);

        if (classfile->fields[i].attributes_count > 0)
        {
            printf("\nAtributos do Field %d", i+1);
            for (j=0; j<classfile->fields[i].attributes_count; j++)
                exibe_atributos(&classfile->fields[i].attributes[j],classfile);
        }

    }    /* fim do exibe fields */


    for (i=0; i<classfile->methods_count; i++)
    {

        printf("\nMETODO %d\n\n",i+1);
        indice = classfile->methods[i].name_index;
        string = recupera_string(classfile->constant_pool,indice);
        printf("name_index.......: #%u [%s]\n",indice,string);
        indice = classfile->methods[i].descriptor_index;
        string = recupera_string(classfile->constant_pool,indice);
        printf("descriptor_index.: #%u [%s]\n",indice,string);
        indice = classfile->methods[i].access_flags;
        string = recupera_nome_flag(indice);
        printf("access_flags.....: 0x%04x [%s]\n",indice,string);
        printf("attributes_count.: %u\n",classfile->methods[i].attributes_count);

        for (j=0; j<classfile->methods[i].attributes_count; j++)
        {
            printf("\nAtributo %d do Metodo %d\n", j+1 , i+1);
            exibe_atributos(&classfile->methods[i].attributes[j], classfile);

        }
    }

    for (i=0; i<classfile->attributes_count; i++)
    {
        printf("\nAtributo %d da Classe\n\n", i+1);
        exibe_atributos(&classfile->attributes[i],classfile);
    }

    printf("\nFIM DO ARQUIVO CLASS.\n\n\n");


    /*TERMINAR AQUI*/
}

void exibe_atributos(t_attribute_info * att, class_file * classfile)
{

    u2 index;
    int i, y;
    u4 indice;
    char * string = (char*) malloc (200*sizeof(char));

    index = att->attribute_name_index - 1;

    if(strcmp((char*)classfile->constant_pool[index].info.utf8_info.bytes,"Code") == 0)
    {

        printf("\nAtributo do tipo Code\n\n");
        indice = att->attribute_name_index;
        string = recupera_string(classfile->constant_pool , indice);
        printf("attribute_name_index...: #%u [%s]\n", indice,string);
        printf("attribute_length.......: %u\n",att->attribute_length);
        printf("max_stack..............: %u\n",att->_info.code.max_stack);
        printf("max_locals.............: %u\n",att->_info.code.max_locals);
        printf("code_length............: %u\n",att->_info.code.code_length);
        exibe_codigo(att->_info.code.code_length , att->_info.code.code);
        printf("exception_table_length.: %u\n",att->_info.code.exception_table_length);
        printf("attributes_count.......: %u\n", att->_info.code.attributes_count);

        for(i=0; i<att->_info.code.attributes_count; i++)
        {
            printf("\nAtributo do Code\n");
            exibe_atributos(&att->_info.code.attributes[i],classfile);
        }

    }

    if(strcmp((char*)classfile->constant_pool[index].info.utf8_info.bytes,"LineNumberTable") == 0)
    {

        printf("\nAtributo do tipo LineNumberTable\n\n");
        indice = att->attribute_name_index;
        string = recupera_string(classfile->constant_pool,indice);
        printf("attribute_name_index.....: #%u [%s]\n", indice,string);
        printf("attribute_length.........: %u\n",att->attribute_length);
        printf("line_number_table_length.: %u\n",att->_info.line_number_table.line_number_table_length);

        printf("\n|---------------------------------|\n");
        printf("|   Nr.  | start pc | line number |\n");
        printf("|---------------------------------|\n");

        for(y=0; y<att->_info.line_number_table.line_number_table_length; y++)
        {

            printf("|  %4d  |  %6u  |   %8u  |\n",y,att->_info.line_number_table.line_number_table[y].start_pc,att->_info.line_number_table.line_number_table[y].line_number );
            printf("|---------------------------------|\n");

        }

        getchar();

    }    /* fim do LineNumberTable */

    if(strcmp((char*)classfile->constant_pool[index].info.utf8_info.bytes,"SourceFile") == 0)
    {

        printf("\nAtributo do tipo SourceFile\n\n");
        indice = att->attribute_name_index;
        string = recupera_string(classfile->constant_pool,indice);
        printf("attribute_name_index..: #%u [%s]\n", indice,string);
        printf("attribute_length......: %u\n",att->attribute_length);
        indice = att->_info.sourcefile.sourcefile_index;
        string = recupera_string(classfile->constant_pool,indice);
        printf("sourcefile_index......: #%u [%s]\n",indice,string);

    }    /* fim do SourceFile */


}

char * recupera_nome_flag (u4 access_flag)
{

    switch (access_flag)
    {

    case 0x0001 :
        return "public";
    case 0x0002 :
        return "private";
    case 0x0009 :
        return "public static";
    case 0x0021 :
        return "public";
    default     :
        return '\0';

    }

    return NULL;

}

char * recupera_nome_classe (t_cp_info * constantPool, u2 indice)
{

    t_cp_info *cp = constantPool;

    /* vai ate o indice apontado, que eh uma CONSTANT_Class */
    cp = constantPool + indice - 1;

    /* o valor em Class.name_index aponta para uma CONSTANT_Utf8 com a string da classe */
    indice = cp->info.class_info.name_index;

    /* vai até o indice da CONSTANT_Utf8 */
    cp = constantPool + indice - 1;

    /* devolve o nome da classe */
    return (char*)cp->info.utf8_info.bytes;

}

char * recupera_string (t_cp_info *constantPool, u2 indice)
{

    t_cp_info *cp = constantPool;
    cp = constantPool;

    /* vai até o índice, que aponta para um CONSTANT_Utf8 */
    cp = constantPool + indice - 1;

    /* retorna string */

    return (char*)cp->info.utf8_info.bytes;

}

char * recupera_name_type (t_cp_info *constantPool, u2 indice)
{

    t_cp_info *cp = constantPool;
    u2 indice2;
    int tam_string;
    char * string1, *string2;

    /* vai até o índice, que aponta para um CONSTANT_NameAndType */
    cp = constantPool + indice - 1;

    /* NameAndType.name_index - aponta para uma Utf8 com o nome */
    /* NameAndType.descriptor_index - aponta para uma Utf8 com o descriptor */
    indice  = cp->info.nameandtype_info.name_index;
    indice2 = cp->info.nameandtype_info.descriptor_index;

    /* primeiro indice Utf8 */
    cp = constantPool;
    cp = constantPool + indice - 1;

    /* primeira parte da string */
    tam_string = cp->info.utf8_info.length;
    string1 = (char*) malloc (tam_string*sizeof(char));
    strcpy(string1,(char*)cp->info.utf8_info.bytes);

    /* segundo indice Utf8 */
    cp = constantPool;
    cp = constantPool + indice2 - 1;

    /* segunda parte da string */
    tam_string = cp->info.utf8_info.length;
    string2 = (char*) malloc (tam_string*sizeof(char));
    strcpy(string2,(char*)cp->info.utf8_info.bytes);

    return strcat(string1,string2);

}




void exibe_codigo(u4 code_length, u1 * code)
{

    int i,j;
    u4 inicial,byte1,byte2,byte3,byte4,key,jump;
    u4 npairs,defaultbyte,low,high;

    printf("\nCodigo:\n\n");

    for (i=0; i<code_length; i++)
    {

        switch (code[i])
        {
        case 0x00:
            printf("nop\n");
            break;

        case 0x01:
            printf("aconst_null\n");
            break;

        case 0x02:
            printf("iconst_m1\n");
            break;

        case 0x03:
            printf("iconst_0\n");
            break;

        case 0x04:
            printf("iconst_1\n");
            break;

        case 0x05:
            printf("iconst_2\n");
            break;

        case 0x06:
            printf("iconst_3\n");
            break;

        case 0x07:
            printf("iconst_4\n");
            break;

        case 0x08:
            printf("iconst_5\n");
            break;

        case 0x09:
            printf("lconst_0\n");
            break;

        case 0x0a:
            printf("lconst_1\n");
            break;

        case 0x0b:
            printf("fconst_0\n");
            break;

        case 0x0c:
            printf("fconst_1\n");
            break;

        case 0x0d:
            printf("fconst_2\n");
            break;

        case 0x0e:
            printf("dconst_0\n");
            break;

        case 0x0f:
            printf("dconst_1\n");
            break;

        case 0x10:
            printf("bipush %d\n", code[i+1]);
            i=i+1;
            break;

        case 0x11:
            printf("sipush\n");
            break;

        case 0x12:
            printf("ldc #%u\n",code[i+1]);
            i++;
            break;

        case 0x13:
            printf("ldc_w #%u\n", code[i+1] + code[i+2]);
            break;

        case 0x14:
            printf("ldc2_w #%u\n", code[i+1] + code[i+2]);
            i=i+2;
            break;

        case 0x15:
            printf("iload %d\n", code[i+1]);
            i++;
            break;

        case 0x16:
            printf("lload %d\n", code[i+1]);
            break;

        case 0x17:
            printf("fload %d\n", code[i+1]);
            break;

        case 0x18:
            printf("dload %d\n", code[i+1]);
            break;

        case 0x19:
            printf("aload %d\n", code[i+1]);
            break;

        case 0x1a:
            printf("iload_0\n");
            break;

        case 0x1b:
            printf("iload_1\n");
            break;

        case 0x1c:
            printf("iload_2\n");
            break;

        case 0x1d:
            printf("iload_3\n");
            break;

        case 0x1e:
            printf("lload_0\n");
            break;

        case 0x1f:
            printf("lload_1\n");
            break;

        case 0x20:
            printf("lload_2\n");
            break;

        case 0x21:
            printf("lload_3\n");
            break;

        case 0x22:
            printf("fload_0\n");
            break;

        case 0x23:
            printf("fload_1\n");
            break;

        case 0x24:
            printf("fload_2\n");
            break;

        case 0x25:
            printf("fload_3\n");
            break;

        case 0x26:
            printf("dload_0\n");
            break;

        case 0x27:
            printf("dload_1\n");
            break;

        case 0x28:
            printf("dload_2\n");
            break;

        case 0x29:
            printf("dload_3\n");
            break;

        case 0x2a:
            printf("aload_0\n");
            break;

        case 0x2b:
            printf("aload_1\n");
            break;

        case 0x2c:
            printf("aload_2\n");
            break;
        case 0x2d:
            printf("aload_3\n");
            break;
        case 0x2e:
            printf("iaload\n");
            break;
        case 0x2f:
            printf("laload\n");
            break;
        case 0x30:
            printf("faload\n");
            break;
        case 0x31:
            printf("daload\n");
            break;
        case 0x32:
            printf("aaload\n");
            break;
        case 0x33:
            printf("baload\n");
            break;
        case 0x34:
            printf("caload\n");
            break;

        case 0x35:
            printf("saload\n");
            break;

        case 0x36:
            printf("istore %d\n",code[i+1]);
            i++;
            break;

        case 0x37:
            printf("lstore %d\n",code[i+1]);
            break;

        case 0x38:
            printf("fstore %d\n",code[i+1]);
            break;

        case 0x39:
            printf("dstore %d\n",code[i+1]);
            break;

        case 0x3a:
            printf("astore %d\n",code[i+1]);
            break;

        case 0x3b:
            printf("istore_0\n");
            break;

        case 0x3c:
            printf("istore_1\n");
            break;

        case 0x3d:
            printf("istore_2\n");
            break;

        case 0x3e:
            printf("istore_3\n");
            break;

        case 0x3f:
            printf("lstore_0\n");
            break;

        case 0x40:
            printf("lstore_1\n");
            break;

        case 0x41:
            printf("lstore_2\n");
            break;

        case 0x42:
            printf("lstore_3\n");
            break;

        case 0x43:
            printf("fstore_0\n");
            break;

        case 0x44:
            printf("fstore_1\n");
            break;

        case 0x45:
            printf("fstore_2\n");
            break;

        case 0x46:
            printf("fstore_3\n");
            break;

        case 0x47:
            printf("dstore_0\n");
            break;

        case 0x48:
            printf("dstore_1\n");
            break;

        case 0x49:
            printf("dstore_2\n");
            break;

        case 0x4a:
            printf("dstore_3\n");
            break;

        case 0x4b:
            printf("astore_0\n");
            break;

        case 0x4c:
            printf("astore_1\n");
            break;

        case 0x4d:
            printf("astore_2\n");
            break;

        case 0x4e:
            printf("astore_3\n");
            break;

        case 0x4f:
            printf("iastore\n");
            break;

        case 0x50:
            printf("lastore\n");
            break;

        case 0x51:
            printf("fastore\n");
            break;

        case 0x52:
            printf("dastore\n");
            break;

        case 0x53:
            printf("aastore\n");
            break;

        case 0x54:
            printf("bastore\n");
            break;

        case 0x55:
            printf("castore\n");
            break;

        case 0x56:
            printf("sastore\n");
            break;

        case 0x57:
            printf("pop\n");
            break;

        case 0x58:
            printf("pop2\n");
            break;

        case 0x59:
            printf("dup\n");
            break;

        case 0x5a:
            printf("dup_x1\n");
            break;

        case 0x5b:
            printf("dup_x2\n");
            break;

        case 0x5c:
            printf("dup2\n");
            break;

        case 0x5d:
            printf("dup2_x1\n");
            break;

        case 0x5e:
            printf("dup2_x2\n");
            break;

        case 0x5f:
            printf("swap\n");
            break;

        case 0x60:
            printf("iadd\n");
            break;

        case 0x61:
            printf("ladd\n");
            break;

        case 0x62:
            printf("fadd\n");
            break;

        case 0x63:
            printf("dadd\n");
            break;

        case 0x64:
            printf("isub\n");
            break;

        case 0x65:
            printf("lsub\n");
            break;

        case 0x66:
            printf("fsub\n");
            break;

        case 0x67:
            printf("dsub\n");
            break;

        case 0x68:
            printf("imul\n");
            break;

        case 0x69:
            printf("lmul\n");
            break;

        case 0x6a:
            printf("fmul\n");
            break;

        case 0x6b:
            printf("dmul\n");
            break;

        case 0x6c:
            printf("idiv\n");
            break;

        case 0x6d:
            printf("ldiv\n");
            break;

        case 0x6e:
            printf("fdiv\n");
            break;

        case 0x6f:
            printf("ddiv\n");
            break;

        case 0x70:
            printf("irem\n");
            break;

        case 0x71:
            printf("lrem\n");
            break;

        case 0x72:
            printf("frem\n");
            break;

        case 0x73:
            printf("drem\n");
            break;

        case 0x74:
            printf("ineg\n");
            break;

        case 0x75:
            printf("lneg\n");
            break;

        case 0x76:
            printf("fneg\n");
            break;

        case 0x77:
            printf("dneg\n");
            break;

        case 0x78:
            printf("ishl\n");
            break;

        case 0x79:
            printf("lshl\n");
            break;

        case 0x7a:
            printf("ishr\n");
            break;

        case 0x7b:
            printf("lshr\n");
            break;

        case 0x7c:
            printf("iushr\n");
            break;

        case 0x7d:
            printf("lushr\n");
            break;

        case 0x7e:
            printf("iand\n");
            break;

        case 0x7f:
            printf("land\n");
            break;

        case 0x80:
            printf("ior\n");
            break;

        case 0x81:
            printf("lor\n");
            break;

        case 0x82:
            printf("ixor\n");
            break;

        case 0x83:
            printf("lxor\n");
            break;

        case 0x84:
            printf("iinc %d by %d\n", code[i+1],code[i+2]);
            i=i+2;
            break;

        case 0x85:
            printf("i2l\n");
            break;

        case 0x86:
            printf("i2f\n");
            break;

        case 0x87:
            printf("i2d\n");
            break;

        case 0x88:
            printf("l2i\n");
            break;

        case 0x89:
            printf("l2f\n");
            break;

        case 0x8a:
            printf("l2d\n");
            break;

        case 0x8b:
            printf("f2i\n");
            break;

        case 0x8c:
            printf("f2l\n");
            break;

        case 0x8d:
            printf("f2d\n");
            break;

        case 0x8e:
            printf("d2i\n");
            break;

        case 0x8f:
            printf("d2l\n");
            break;

        case 0x90:
            printf("d2f\n");
            break;

        case 0x91:
            printf("i2b\n");
            break;

        case 0x92:
            printf("i2c\n");
            break;

        case 0x93:
            printf("i2s\n");
            break;

        case 0x94:
            printf("lcmp\n");
            break;

        case 0x95:
            printf("fcmpl\n");
            break;

        case 0x96:
            printf("fcmpg\n");
            break;

        case 0x97:
            printf("dcmpl\n");
            break;

        case 0x98:
            printf("dcmpg\n");
            break;

        case 0x99:
            printf("ifeq %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0x9a:
            printf("ifne %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0x9b:
            printf("iflt %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0x9c:
            printf("ifge %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0x9d:
            printf("ifgt %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0x9e:
            printf("ifle %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0x9f:
            printf("if_icmpeq %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0xa0:
            printf("if_icmpne %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0xa1:
            printf("if_icmplt %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0xa2:
            printf("if_icmpge %u %u\n", code[i+1] , code[i+2]);
            i=i+2;
            break;

        case 0xa3:
            printf("if_icmpgt %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0xa4:
            printf("if_icmple %u %u\n", code[i+1] , code[i+2]);
            break;

        case 0xa5:
            printf("if_acmpeq\n");
            break;

        case 0xa6:
            printf("if_acmpne\n");
            break;

        case 0xa7:
            printf("goto %u (+%u)\n", i+(code[i+1]<<8|code[i+2]), code[i+1]<<8|code[i+2]);
            i=i+2;
            break;

        case 0xa8:
            printf("jsr\n");
            break;

        case 0xa9:
            printf("ret %d\n", code[i+1]);
            break;

        case 0xaa:
            i++;
            inicial = i;

            while(i%4!=0)
            {
                i++;
            }

            byte1=code[i++];
            byte2=code[i++];
            byte3=code[i++];
            byte4=code[i++];
            defaultbyte = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

            byte1=code[i++];
            byte2=code[i++];
            byte3=code[i++];
            byte4=code[i++];
            low = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

            byte1=code[i++];
            byte2=code[i++];
            byte3=code[i++];
            byte4=code[i++];
            high = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

            printf("tableswitch (%u to %u)\n",low,high);

            for (j=low;j<=high;j++){

                byte1=code[i++];
                byte2=code[i++];
                byte3=code[i++];
                byte4=code[i++];
                jump = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

                printf("%4u: %4u (+%u)\n",j,inicial+jump-1,jump);

            }

            printf("   default: %4u (+%u)\n",inicial+defaultbyte-1,defaultbyte);
            i--;
            break;

        case 0xab:
            i++;
            inicial = i;

            while(i%4!=0)
            {
                i++;
            }

            byte1=code[i++];
            byte2=code[i++];
            byte3=code[i++];
            byte4=code[i++];
            defaultbyte = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

            byte1=code[i++];
            byte2=code[i++];
            byte3=code[i++];
            byte4=code[i++];
            npairs = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

            printf("lookupswitch (%u)\n",npairs);

            for (j=0;j<npairs;j++){

                byte1=code[i++];
                byte2=code[i++];
                byte3=code[i++];
                byte4=code[i++];
                key = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

                byte1=code[i++];
                byte2=code[i++];
                byte3=code[i++];
                byte4=code[i++];
                jump = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

                printf("%4u: %4u (+%u)\n",key,inicial+jump-1,jump);

            }

            printf("   default: %4u (+%u)\n",inicial+defaultbyte-1,defaultbyte);
            i--;
            break;

        case 0xac:
            printf("ireturn\n");
            break;

        case 0xad:
            printf("lreturn\n");
            break;

        case 0xae:
            printf("freturn\n");
            break;

        case 0xaf:
            printf("dreturn\n");
            break;

        case 0xb0:
            printf("areturn\n");
            break;

        case 0xb1:
            printf("return_\n");
            break;

        case 0xb2:
            printf("getstatic #%u\n", code[i+1] + code[i+2]);
            i=i+2;
            break;

        case 0xb3:
            printf("putstatic #%u\n", code[i+1] + code[i+2]);
            i=i+2;
            break;

        case 0xb4:
            printf("getfield #%u\n",code[i+1] + code[i+2]);
            i=i+2;
            break;

        case 0xb5:
            printf("putfield #%u\n",code[i+1] + code[i+2]);
            i=i+2;
            break;

        case 0xb6:
            printf("invokevirtual #%u\n",code[i+1]<<8|code[i+2]);
            i=i+2;
            break;

        case 0xb7:
            printf("invokespecial #%u\n",code[i+1] + code[i+2]);
            i=i+2;
            break;

        case 0xb8:
            printf("invokestatic #%u\n",code[i+1] + code[i+2]);
            i=i+2;
            break;

        case 0xb9:
            printf("invokeinterface\n");
            break;

        case 0xba:
            printf("NULL\n");
            break;

        case 0xbb:
            printf("new #%u\n",code[i+1] + code[i+2]);
            i=i+2;
            break;

        case 0xbc:
            switch (code[i+1])
            {
            case 4:
                printf("newarray (tipo: %u - %s)\n", code[i+1],"t_boolean"); break;
            case 5:
                printf("newarray (tipo: %u - %s)\n", code[i+1],"t_char"); break;
            case 6:
                printf("newarray (tipo: %u - %s)\n", code[i+1],"t_float"); break;
            case 7:
                printf("newarray (tipo: %u - %s)\n", code[i+1],"t_double"); break;
            case 8:
                printf("newarray (tipo: %u - %s)\n", code[i+1],"t_byte"); break;
            case 9:
                printf("newarray (tipo: %u - %s)\n", code[i+1],"t_short"); break;
            case 10:
                printf("newarray (tipo: %u - %s)\n", code[i+1],"t_int"); break;
            case 11:
                printf("newarray (tipo: %u - %s)\n", code[i+1],"t_long"); break;
            default:
                printf("newarray (tipo: %u)\n", code[i+1]); break;
            }
            i++;
            break;

        case 0xbd:
            printf("anewarray #%u\n",code[i+1]+code[i+2]);
            i=i+2;
            break;

        case 0xbe:
            printf("arraylength\n");
            break;

        case 0xbf:
            printf("athrow\n");
            break;

        case 0xc0:
            printf("checkcast\n");
            break;

        case 0xc1:
            printf("instanceof\n");
            break;

        case 0xc2:
            printf("monitorenter\n");
            break;

        case 0xc3:
            printf("monitorexit\n");
            break;

        case 0xc4:
            printf("wide\n");
            break;

        case 0xc5:
            printf("multinewarray\n");
            break;

        case 0xc6:
            printf("ifnull #%u\n", code[i+1] + code[i+2]);
            i=i+2;
            break;

        case 0xc7:
            printf("ifnonnull #%u\n", code[i+1] + code[i+2]);
            i=i+2;
            break;

        case 0xc8:
            printf("goto_w\n");
            break;

        case 0xc9:
            printf("jsr_w\n");
            break;

        } /* fim do switch */

    } /* fim do for */
    printf("\n");
    getchar();

}

