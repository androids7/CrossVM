


#ifndef CLASS_LOADER_H_
#define CLASS_LOADER_H_

#include <stdio.h>
#include "class.h"
#include "estruturas.h"

/* macro para leitura dos dados do arquivo */
#define readu1(fp) getc(fp);
#define readu2(fp) ((getc(fp)) << 8) | getc(fp);
#define readu4(fp) ((getc(fp)) << 24) | ((getc(fp))<<16) | ((getc(fp))<<8) | getc(fp);


/* funcoes de leitura do arquivo class */
void leitura_classfile(FILE *fp);
void leitura_dos_metodos(t_method_info * method , FILE *fp, class_file * classfile);
void leitura_dos_atributos(t_attribute_info * att , FILE *fp, class_file * classfile);
void leitura_dos_fields(t_field_info * field, FILE *fp, class_file * classfile);


/* no programa sera declarado um ponteiro para funcoes
 * para lidar com todos os tipos de cp_info
 * As funcoes recebem o ponteiro para a struct que ira armazenar
 * todas informacoes da cp_info, o arquivo a ser lido para obter
 * as informacoes e um inteiro indicando a posicao do vetor de struct que para qual
 * devera ser salva a cp_info
 */
int bclass(t_cp_info*, FILE*, int);
int bfieldref(t_cp_info*, FILE*, int);
int bmethodref(t_cp_info*, FILE*, int);
int binterfacemethodref(t_cp_info*, FILE*, int);
int bstring(t_cp_info*, FILE*, int);
int binteger(t_cp_info*, FILE*, int);
int bfloat(t_cp_info*, FILE*, int);
int blong(t_cp_info*, FILE*, int);
int bdouble(t_cp_info*, FILE*, int);
int bnamenadtype(t_cp_info*, FILE*, int);
int butf8(t_cp_info*, FILE*, int);


/* funcos para exibicao do .class lido */
void exibe_classfile(class_file * class_file);
void exibe_atributos(t_attribute_info * att, class_file * classfile);
void exibe_codigo(u4 code_length, u1 * code);

/* auxiliares da exibicao do codigo */
char * recupera_nome_flag(u4 access_flag);
char * recupera_nome_classe (t_cp_info * constantPool, u2 indice);
char * recupera_string (t_cp_info *constantPool, u2 indice);
char * recupera_name_type (t_cp_info *constantPool, u2 indice);



#endif /* CLASS_LOADER_H_ */
