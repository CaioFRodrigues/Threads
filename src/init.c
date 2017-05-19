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
*   init.c: funções auxiliares da inicialização de variáveis globais
*
*   versão 1.0 - 07/05/2017
*/



#include "../include/init.h"

// Void init: Inicializa um contexto para o control_thread
void init(){
	//Garante que não haverão duas inicializações
    init_flag = 1;


    //Inicializa a fila de threads
    init_fila();

    //Inicializa a thread principal
    init_main_thread();

    //Inicializa o contexto da thread que sempre apontará para end_thread()
    init_end_thread_context();

    //Inicializa a thread atual
    current_thread = main_thread;
}



//init_fila(): Inicializa as filas globais de threads
void init_fila(){
	int i;
	//Inicializa cada fila de threads
	for (i = 0; i < FILA_SIZE; i++) 
		CreateFila2( &(fila_threads[FILA_SIZE])); 
    CreateFila2(&fila_blocked);
}


//Inicializa o contexto da main_thread
void init_main_thread(){

	//Cria um template para a thread
	ucontext_t *new_thread_context = malloc(sizeof(ucontext_t));
    getcontext(new_thread_context);

	//Inicializa a thread principal
    main_thread.context = *new_thread_context;
    main_thread.state = PROCST_EXEC;
    main_thread.tid = 0;
    main_thread.ticket = 0;

}

//init_end_thread_context(): Inicializa o contexto global que sempre aponta para control_thread
void init_end_thread_context(){

    getcontext(&end_thread_context); //inicializa o contexto global que sempre aponta para control_thread

    //Manipula as informações internas
    end_thread_context.uc_stack.ss_sp = malloc(MEM);
    end_thread_context.uc_stack.ss_size = MEM;
    end_thread_context.uc_link = NULL;

    //Finaliza a criação de contexto global
    makecontext(&end_thread_context, end_thread, NO_ARGUMENT);

}