/*
*   UFRGS - Universidade Federal do Rio Grande do Sul
*   Instituto de Informática
*   INF01142 - Sistemas Operacionais I (2017/1)
*
*   Trabalho Prático I - Biblioteca de Threads cthreads 17.1
*
*   Ana Paula Mello - 260723 <apcomello@gmail.com>
*   Arateus Meneses - 242260 <arateus.meneses@gmail.com>
*   Caio Rodrigues -261578  <caio_f.r@hotmail.com>
*
*   bloc_fila.c: funções auxiliares da uso da fila de bloqueados
*
*   versão 1.0 - 07/05/2017
*/



#include "../include/bloc_fila.h"


//Função insert_blocfila(thread, codigo)
void insert_block_fila(TCB_t * thread, int expected_tid){
	blocked_TCB* blocked_thread = malloc(sizeof(blocked_TCB));
	blocked_thread->expected_tid = expected_tid;
	blocked_thread->thread = *thread;

	AppendFila2(&fila_blocked, blocked_thread);

}


TCB_t * control_block_fila(){
	TCB_t * thread = malloc(sizeof(TCB_t));

}
