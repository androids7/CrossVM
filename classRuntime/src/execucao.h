#ifndef EXECUCAO_H_
#define EXECUCAO_H_

instance * inserir_nova_instancia(char * nomeClasse);

t_method_info * localizar_metodo_pelo_nome (class_file * classfile , char * nome_metodo);

class_list * localizar_classe_pelo_nome (char * nomeClasse);

frame_execucao * iniciar_frame (class_file * classfile , t_method_info * metodo);

void executar_metodo (frame_execucao * frame);


#endif
