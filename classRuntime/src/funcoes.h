#ifndef FUNCOES_H_
#define FUNCOES_H_

int nop             (frame_execucao * frame); /*0x00*/
int aconst_null     (frame_execucao * frame); /*0x01*/
int iconst_m1       (frame_execucao * frame); /*0x02*/
int iconst_0        (frame_execucao * frame); /*0x03*/
int iconst_1        (frame_execucao * frame); /*0x04*/
int iconst_2        (frame_execucao * frame); /*0x05*/
int iconst_3        (frame_execucao * frame); /*0x06*/
int iconst_4        (frame_execucao * frame); /*0x07*/
int iconst_5        (frame_execucao * frame); /*0x08*/
int lconst_0        (frame_execucao * frame); /*0x09*/
int lconst_1        (frame_execucao * frame); /*0x0a*/
int fconst_0        (frame_execucao * frame); /*0x0b*/
int fconst_1        (frame_execucao * frame); /*0x0c*/
int fconst_2        (frame_execucao * frame); /*0x0d*/
int dconst_0        (frame_execucao * frame); /*0x0e*/
int dconst_1        (frame_execucao * frame); /*0x0f*/
int bipush          (frame_execucao * frame); /*0x10*/
int sipush          (frame_execucao * frame); /*0x11*/
int ldc             (frame_execucao * frame); /*0x12*/
int ldc_w           (frame_execucao * frame); /*0x13*/
int ldc2_w          (frame_execucao * frame); /*0x14*/
int iload           (frame_execucao * frame); /*0x15*/
int lload           (frame_execucao * frame); /*0x16*/
int fload           (frame_execucao * frame); /*0x17*/
int dload           (frame_execucao * frame); /*0x18*/
int aload           (frame_execucao * frame); /*0x19*/
int iload_0         (frame_execucao * frame); /*0x1a*/
int iload_1         (frame_execucao * frame); /*0x1b*/
int iload_2         (frame_execucao * frame); /*0x1c*/
int iload_3         (frame_execucao * frame); /*0x1d*/
int lload_0         (frame_execucao * frame); /*0x1e*/
int lload_1         (frame_execucao * frame); /*0x1f*/
int lload_2         (frame_execucao * frame); /*0x20*/
int lload_3         (frame_execucao * frame); /*0x21*/
int fload_0         (frame_execucao * frame); /*0x22*/
int fload_1         (frame_execucao * frame); /*0x23*/
int fload_2         (frame_execucao * frame); /*0x24*/
int fload_3         (frame_execucao * frame); /*0x25*/
int dload_0         (frame_execucao * frame); /*0x26*/
int dload_1         (frame_execucao * frame); /*0x27*/
int dload_2         (frame_execucao * frame); /*0x28*/
int dload_3         (frame_execucao * frame); /*0x29*/
int aload_0         (frame_execucao * frame); /*0x2a*/
int aload_1         (frame_execucao * frame); /*0x2b*/
int aload_2         (frame_execucao * frame); /*0x2c*/
int aload_3         (frame_execucao * frame); /*0x2d*/
int iaload          (frame_execucao * frame); /*0x2e*/
int laload          (frame_execucao * frame); /*0x2f*/
int faload          (frame_execucao * frame); /*0x30*/
int daload          (frame_execucao * frame); /*0x31*/
int aaload          (frame_execucao * frame); /*0x32*/
int baload          (frame_execucao * frame); /*0x33*/
int caload          (frame_execucao * frame); /*0x34*/
int saload          (frame_execucao * frame); /*0x35*/
int istore          (frame_execucao * frame); /*0x36*/
int lstore          (frame_execucao * frame); /*0x37*/
int fstore          (frame_execucao * frame); /*0x38*/
int dstore          (frame_execucao * frame); /*0x39*/
int astore          (frame_execucao * frame); /*0x3a*/
int istore_0        (frame_execucao * frame); /*0x3b*/
int istore_1        (frame_execucao * frame); /*0x3c*/
int istore_2        (frame_execucao * frame); /*0x3d*/
int istore_3        (frame_execucao * frame); /*0x3e*/
int lstore_0        (frame_execucao * frame); /*0x3f*/
int lstore_1        (frame_execucao * frame); /*0x40*/
int lstore_2        (frame_execucao * frame); /*0x41*/
int lstore_3        (frame_execucao * frame); /*0x42*/
int fstore_0        (frame_execucao * frame); /*0x43*/
int fstore_1        (frame_execucao * frame); /*0x44*/
int fstore_2        (frame_execucao * frame); /*0x45*/
int fstore_3        (frame_execucao * frame); /*0x46*/
int dstore_0        (frame_execucao * frame); /*0x47*/
int dstore_1        (frame_execucao * frame); /*0x48*/
int dstore_2        (frame_execucao * frame); /*0x49*/
int dstore_3        (frame_execucao * frame); /*0x4a*/
int astore_0        (frame_execucao * frame); /*0x4b*/
int astore_1        (frame_execucao * frame); /*0x4c*/
int astore_2        (frame_execucao * frame); /*0x4d*/
int astore_3        (frame_execucao * frame); /*0x4e*/
int iastore         (frame_execucao * frame); /*0x4f*/
int lastore         (frame_execucao * frame); /*0x50*/
int fastore         (frame_execucao * frame); /*0x51*/
int dastore         (frame_execucao * frame); /*0x52*/
int aastore         (frame_execucao * frame); /*0x53*/
int bastore         (frame_execucao * frame); /*0x54*/
int castore         (frame_execucao * frame); /*0x55*/
int sastore         (frame_execucao * frame); /*0x56*/
int pop             (frame_execucao * frame); /*0x57*/
int dup             (frame_execucao * frame); /*0x59*/
int dup_x1          (frame_execucao * frame); /*0x5a*/
int dup_x2          (frame_execucao * frame); /*0x5b*/
int dup2            (frame_execucao * frame); /*0x5c*/
int dup2_x1         (frame_execucao * frame); /*0x5c*/
int dup2_x2         (frame_execucao * frame); /*0x5c*/
int swap            (frame_execucao * frame); /*0x5f*/
int iadd            (frame_execucao * frame); /*0x60*/
int ladd            (frame_execucao * frame); /*0x61*/
int fadd            (frame_execucao * frame); /*0x62*/
int dadd            (frame_execucao * frame); /*0x63*/
int isub            (frame_execucao * frame); /*0x64*/
int lsub            (frame_execucao * frame); /*0x65*/
int fsub            (frame_execucao * frame); /*0x66*/
int dsub            (frame_execucao * frame); /*0x67*/
int imul            (frame_execucao * frame); /*0x68*/
int lmul            (frame_execucao * frame); /*0x69*/
int fmul            (frame_execucao * frame); /*0x6a*/
int dmul            (frame_execucao * frame); /*0x6b*/
int idiv            (frame_execucao * frame); /*0x6c*/
int ldiv_           (frame_execucao * frame); /*0x6d*/
int fdiv            (frame_execucao * frame); /*0x6e*/
int ddiv            (frame_execucao * frame); /*0x6f*/
int irem            (frame_execucao * frame); /*0x70*/
int lrem            (frame_execucao * frame); /*0x71*/
int frem            (frame_execucao * frame); /*0x72*/
int drem_           (frame_execucao * frame); /*0x73*/
int ineg            (frame_execucao * frame); /*0x74*/
int lneg            (frame_execucao * frame); /*0x75*/
int fneg            (frame_execucao * frame); /*0x76*/
int dneg            (frame_execucao * frame); /*0x77*/
int ishl            (frame_execucao * frame); /*0x78*/
int lshl            (frame_execucao * frame); /*0x79*/
int ishr            (frame_execucao * frame); /*0x7a*/
int lshr            (frame_execucao * frame); /*0x7b*/
int iushr           (frame_execucao * frame); /*0x7c*/
int iand            (frame_execucao * frame); /*0x7e*/
int land            (frame_execucao * frame); /*0x7f*/
int ior             (frame_execucao * frame); /*0x80*/
int lor             (frame_execucao * frame); /*0x81*/
int ixor            (frame_execucao * frame); /*0x82*/
int lxor            (frame_execucao * frame); /*0x83*/
int iinc            (frame_execucao * frame); /*0x84*/
int i2l             (frame_execucao * frame); /*0x85*/
int i2f             (frame_execucao * frame); /*0x86*/
int i2d             (frame_execucao * frame); /*0x87*/
int l2i             (frame_execucao * frame); /*0x88*/
int l2f             (frame_execucao * frame); /*0x89*/
int l2d             (frame_execucao * frame); /*0x8a*/
int f2i             (frame_execucao * frame); /*0x8b*/
int f2l             (frame_execucao * frame); /*0x8c*/
int f2d             (frame_execucao * frame); /*0x8d*/
int d2i             (frame_execucao * frame); /*0x8e*/
int d2l             (frame_execucao * frame); /*0x8f*/
int d2f             (frame_execucao * frame); /*0x90*/
int i2b             (frame_execucao * frame); /*0x91*/
int i2c             (frame_execucao * frame); /*0x92*/
int i2s             (frame_execucao * frame); /*0x93*/
int lcmp            (frame_execucao * frame); /*0x94*/
int fcmpl           (frame_execucao * frame); /*0x95*/
int fcmpg           (frame_execucao * frame); /*0x96*/
int dcmpl           (frame_execucao * frame); /*0x97*/
int dcmpg           (frame_execucao * frame); /*0x98*/
int ifeq            (frame_execucao * frame); /*0x99*/
int ifne            (frame_execucao * frame); /*0x9a*/
int iflt            (frame_execucao * frame); /*0x9b*/
int ifge            (frame_execucao * frame); /*0x9c*/
int ifgt            (frame_execucao * frame); /*0x9d*/
int ifle            (frame_execucao * frame); /*0x9e*/
int if_icmpeq       (frame_execucao * frame); /*0x9f*/
int if_icmpne       (frame_execucao * frame); /*0xa0*/
int if_icmplt       (frame_execucao * frame); /*0xa1*/
int if_icmpge       (frame_execucao * frame); /*0xa2*/
int if_icmpgt       (frame_execucao * frame); /*0xa3*/
int if_icmple       (frame_execucao * frame); /*0xa4*/
int goto_           (frame_execucao * frame); /*0xa7*/
int ret             (frame_execucao * frame); /*0xa9*/
int tableswitch     (frame_execucao * frame); /*0xaa*/
int lookupswitch    (frame_execucao * frame); /*0xab*/
int ireturn         (frame_execucao * frame); /*0xac*/
int lreturn         (frame_execucao * frame); /*0xad*/
int freturn         (frame_execucao * frame); /*0xae*/
int dreturn         (frame_execucao * frame); /*0xaf*/
int areturn         (frame_execucao * frame); /*0xb0*/
int return_         (frame_execucao * frame); /*0xb1*/
int getstatic       (frame_execucao * frame); /*0xb2*/
int putstatic       (frame_execucao * frame); /*0xb3*/
int getfield        (frame_execucao * frame); /*0xb4*/
int putfield        (frame_execucao * frame); /*0xb5*/
int invokevirtual   (frame_execucao * frame); /*0xb6*/
int invokespecial   (frame_execucao * frame); /*0xb7*/
int invokestatic    (frame_execucao * frame); /*0xb8*/
int new_            (frame_execucao * frame); /*0xbb*/
int newarray        (frame_execucao * frame); /*0xbc*/
int anewarray       (frame_execucao * frame); /*0xbd*/
int arraylength     (frame_execucao * frame); /*0xbe*/
int ifnull          (frame_execucao * frame); /*0xc6*/
int ifnonnull       (frame_execucao * frame); /*0xc7*/
int jsr_w           (frame_execucao * frame); /*0xc9*/


/* instrucoes da pilha de operandos */
pilha_u4 * inserir_na_pilha (pilha_u4 * pilha, u4 valor);
pilha_u4 * retirar_da_pilha (pilha_u4 * pilha, u4 * valor);

float converte_para_float (u4 valor);
double converte_para_double (long long valor);


/* para transformar um float em inteiro */
typedef union
{
    float f;
    unsigned int i;
} tipo_float;

typedef union
{
    unsigned int u;
    short i;
} llts;

/* para transformar um double em long long int */
typedef union
{
    double d;
    unsigned long long l;
} tipo_double;




#endif
