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


// Criação e inicialização da fila de threads

extern int tidCounter; // Thread Identifier Counter
extern int init_flag; // 0 - Biblioteca ainda não foi iniciada; 1 - Biblioteca já foi
tidCounter = 1;
init_flag = 0;
void init(){
    
	//Garante que não haverão duas inicializações
    init_flag = 1;


    //Inicializa a fila de threads
    for (int i = 0; i < FILA_SIZE; i++){
		CreateFila2( &(fila_threads[FILA_SIZE]));
	}	


	//Cria um template para a thread
	ucontext_t *new_thread_context = (ucontext_t *) malloc(sizeof(ucontext_t));
    getcontext(new_thread_context);
	//Inicializa a thread principal
    main_thread.context = *new_thread_context;
    main_thread.state = PROCST_EXEC;
    main_thread.tid = 0;
    main_thread.ticket = 0;

    //Inicializa a thread atual
    current_thread = main_thread;
 	
    //Inicializa o contexto que sempre aponta para choose_thread
    getcontext(&choose_thread_context);
    choose_thread_context.uc_stack.ss_sp = malloc(MEM);
    choose_thread_context.uc_stack.ss_size = MEM;
    choose_thread_context.uc_link = NULL;
    makecontext(&choose_thread_context, choose_thread, NO_ARGUMENT);

 
}


//Função control_thread(): Manuseia próxima thread a ser executada e checa a fila de bloqueios
int control_thread(){	
	//Decide a próxima thread a ser executada
	choose_thread();
	return 0;




}


// Função choose_thread(s_TCB* returning_thread): Escolhe a thread a ser executada a partir da fila de aptos e remove ela da fila;
void choose_thread(){

	TCB_t * next_thread = (TCB_t *) malloc(sizeof(TCB_t));
	for (int i = 0; i < FILA_SIZE;i++ )
		if(FirstFila2(&fila_threads[i])){  //Coloca o iterador para o primeiro da fila de thread
										   //caso não haja na primeira fila, tenta a próxima fila até o final das filas
			*next_thread = (*(TCB_t *) (GetAtIteratorFila2(&fila_threads[i])));
			DeleteAtIteratorFila2(&fila_threads[i]);
			change_context(i, next_thread);
	}
	printf ("ALGO DEU MUITO ERRADO");
}


// Função insert_thread(): Insere thread para a fila com número passado por argumento. Troca o contexto para essa fila
void change_context(int fila, TCB_t *next_thread){
	

	LastFila2(&fila_threads[fila]);
	AppendFila2(GetAtIteratorFila2(&fila_threads[fila]), &current_thread);
	current_thread = *next_thread;
	swapcontext(&(((TCB_t *)(GetAtIteratorFila2(&fila_threads[fila])))->context), &(next_thread->context));


}



int control_blocked();
