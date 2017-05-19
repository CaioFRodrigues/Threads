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
*   manager.c: funções auxiliares de manuseamento interno da thread
*
*   versão 1.0 - 07/05/2017
*/


#include "../include/manager.h"


//Função control_thread(): Manuseia próxima thread a ser executada e checa a fila de bloqueios
void end_thread(){	
	//Controla fila de bloqueios
	blocked_TCB * blocked_thread = search_block_fila(current_thread.tid);

	if (blocked_thread != NULL){

		TCB_t *copy_blocked_thread = malloc(sizeof(TCB_t)); //Cria cópia para não perder o ponteiro ao deletá-lo da fila
		*copy_blocked_thread = blocked_thread->thread;
		DeleteAtIteratorFila2(&fila_blocked);
		insert_thread_in_fila(copy_blocked_thread);


	}
	//Decide a próxima thread a ser executada
	TCB_t * next_thread = get_next_thread();
	current_thread = *next_thread;
	setcontext(&(current_thread.context));

	
}

//Função free_thread(): Coloca a thread atual na fila de threads, e coloca a primeira thread da fila em execução 
int free_thread(){
	TCB_t * next_thread = get_next_thread();

	if (next_thread == NULL)
		return -1;
	int current_thread_ticket;

	current_thread_ticket = update_current_thread(next_thread);

	swap_context(current_thread_ticket);

	return 0;
}
