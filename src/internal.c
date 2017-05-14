/*
*   UFRGS - Universidade Federal do Rio Grande do Sul
*   Instituto de Informática
*   INF01142 - Sistemas Operacionais I (2017/1)
*
*   Trabalho Prático I - Biblioteca de Threads cthreads 17.1
*
*   Ana Paula Mello - 260723 <apcomello@gmail.com>
*   Arateus Meneses - 242260 <caio_f.r@hotmail.com>
*   Caio Rodrigues -261578  <arateus.meneses@gmail.com>
*
*   internal.c: funções auxiliares da implementação da interface
*
*   versão 1.0 - 07/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include "../internal.h"
#include "../support.h"
#include "../cdata.h"
#include "../cthread.h"

#define FILA_SIZE 4 
#define TRUE 1
#define FALSE 0
// Criação e inicialização da fila de threads
FILA2 fila_threads[FILA_SIZE];


void init(){
    
	//Garante que não haverão duas inicializações
    init = 1;

    //Inicializa a fila de threads
    for (int i = 0; i < FILA_SIZE; i++){
		fila_threads[FILA_SIZE] = CreateFila2;
	}	

	//Inicializa a thread principal
    main_thread.context = *new_thread_context;
    main_thread.state = EXEC;
    main_thread.tid = 0;
    main_thread.ticket = 0;

    //Inicializa a thread atual
    current_thread = main_thread;

    //Inicializa o contexto que sempre aponta para choose_thread
    getcontext(&choose_thread_context);
    choose_thread_context.ss_sp = malloc(MEM);
    choose_thread_context.ss_size = MEM;
    choose_thread_context.uc_link = NULL;
    makecontext(&choose_thread_context, choose_thread(), NO_ARGUMENT);

 
}


//Função control_thread(): Manuseia próxima thread a ser executada e checa a fila de bloqueios
int control_thread(){	
	//Decide a próxima thread a ser executada
	choose_thread();




	
}


// Função choose_thread(s_TCB* returning_thread): Escolhe a thread a ser executada a partir da fila de aptos e remove ela da fila;
void choose_thread(){

	TCB_t * next_thread = (TCB_t *) malloc(sizeof(TCB_t));
	for (int i = 0; i < FILA_SIZE;i++ )
		if(FirstFila2(&fila_threads[i])){  //Coloca o iterador para o primeiro da fila de thread
										   //caso não haja na primeira fila, tenta a próxima fila até o final das filas
			*next_thread = *(GetatIteratorFila2(&fila_threads[i]));
			DeleteatIteratorFila2(&fila_threads[i]);
			troca_contexto(int i, next_thread)
	}
	printf ("ALGO DEU MUITO ERRADO");
}


// Função insert_thread(): Insere thread para a fila com número passado por argumento. Troca o contexto para essa fila
ucontext_t change_context(int fila, TCB_t *next_thread){
	

	LastFila2(&fila_threads[fila]);
	AppendFila2(GetatIteratorFila2(&fila_threads[fila], &current_thread);
	current_thread = *next_thread;
	swapcontext((GetatIteratorFila2(&fila_threads[fila])).context, next_thread))


}



control_blocked();
