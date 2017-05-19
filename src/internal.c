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
*   internal.c: funções auxiliares da implementação da interface
*
*   versão 1.0 - 07/05/2017
*/


#include "../include/internal.h"


//Cria uma thread nova com um contexto alocado para a função desejada
TCB_t * create_thread(void *(*start)(void *), void *arg, int prio){

	TCB_t *new_thread = malloc(sizeof(TCB_t)); //Ponteiro para nova thread que será posto na fila
    ucontext_t *new_thread_context = malloc(sizeof(ucontext_t)); //Ponteiro do contexto da nova thread 

    if(getcontext(new_thread_context) == -1) //Pega o contexto atual
        return NULL;
   	
    new_thread_context->uc_stack.ss_sp = malloc(MEM);
    new_thread_context->uc_stack.ss_size = MEM;
    new_thread_context->uc_link = &end_thread_context;
    new_thread->ticket = prio;
    new_thread->state = PROCST_APTO;
    new_thread->tid = tid_counter++;
    makecontext(new_thread_context, (void (*) (void)) start, 1, arg);
    new_thread->context = *new_thread_context;

    return new_thread;
}




//Função update_current_thread(): Cria uma cópia da thread atual e a coloca no final da fila de threads
//Atualiza a thread atual por uma passada por parâmetro
//Retorna o valor da fila da thread anterior, para seu contexto ser salvo posteriormente
int update_current_thread(TCB_t * next_thread){

	TCB_t * current_thread_copy = malloc(sizeof(TCB_t)); // Cópia da thread atual que será jogada na fila de threads
	*current_thread_copy = current_thread; //Agora current_thread pode ser alterada, e o último elemento da fila é a thread atual
	insert_thread_in_fila(current_thread_copy); //Insere a cópia na fila
 	current_thread = *next_thread; //Atualiza a thread atual
 	return current_thread_copy->ticket;
}

// Função swap_context(fila): Troca o contexto da thread para o current_thread, e salva o contexto atual na fila passada como parâmetro
void swap_context(int fila){
	LastFila2(&fila_threads[fila]);
	swapcontext(&(((TCB_t *)(GetAtIteratorFila2(&fila_threads[fila])))->context), &(current_thread.context));

}


//Função insert_thread(thread): Insere thread para a fila dela
void insert_thread_in_fila(TCB_t *new_thread){

	AppendFila2(&fila_threads[new_thread->ticket], new_thread);

}

// Função get_next_thread(): Pega a primeira thread da fila, e retorna ela;
// Retorno: próxima thread a ser executada
TCB_t * get_next_thread(){
	int i;

	for (i = 0; i < FILA_SIZE;i++ )
		if(!FirstFila2(&fila_threads[i])){  //Coloca o iterador para o primeiro da fila de thread
							   //caso não haja na primeira fila, tenta a próxima fila até o final das filas
			TCB_t * next_thread = (TCB_t *) malloc(sizeof(TCB_t));

			*next_thread = (*(TCB_t *) (GetAtIteratorFila2(&fila_threads[i])));

			DeleteAtIteratorFila2(&fila_threads[i]);

			return next_thread;
	}
	return NULL;
}


//Função control_blocked(): Controla as threads bloqueadas, checando se alguma pode ser liberada com o encerramento da thread atual
int control_blocked();
