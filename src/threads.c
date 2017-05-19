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
*   threads.c: funções relacionadas à estrutura de threads
*
*   versão 1.0 - 07/05/2017
*/


#include "../include/internal.h"
#include "../include/support.h"
#include "../include/cdata.h"
#include "../include/cthread.h"



int init_flag = 0; // 0 - Biblioteca ainda não foi iniciada; 1 - Biblioteca já foi iniciada
int tid_counter = 1;

//função ccreate (func, arg, prio)
//Cria uma nova thread de prioridade prio com a função func passando arg como argumento
//Inicializa diversas coisas internas da biblioteca
//Abdica do controle da thread ao final da função,chamando a próxima no escalonador
//Retorna -1 se não conseguir criar uma nova thread, e 0 caso consiga
int ccreate(void *(*start)(void *), void *arg, int prio)
{
    if (init_flag == 0)  //Primeira execução do programa
        init();
    
    TCB_t * new_thread = create_thread(start, arg, prio);
    
    if (new_thread == NULL)
        return -1;

    insert_thread_in_fila(new_thread);

    free_thread();

    return new_thread->tid;
}

// Abdica do controle do processador e vai para a próxima thread
// retorna 0 se deu erro e -1 se ocorreu falha (não havia thread para trocar).
int cyield(){
    if (free_thread() != 0)
        return -1;
    else return 0;
}


int csetprio(int tid, int prio){

    TCB_t * searched_thread = search_fila_thread(tid);
    if (searched_thread == 0)
        return -1;
    TCB_t * copy_thread = malloc(sizeof(TCB_t));
    *copy_thread = *searched_thread;
    DeleteAtIteratorFila2(&fila_threads[searched_thread->ticket]);
    
    copy_thread->ticket = prio;
    //Muda a thread para a fila apropriada
    insert_thread_in_fila(copy_thread);
                
    return 0;
            
            

        

}

int cjoin(int tid){
    TCB_t * thread = search_tid(tid);
    if (thread == NULL)
        return -1;

    TCB_t * current_thread_copy = malloc(sizeof(TCB_t)); // Cópia da thread atual que será jogada na fila de threads
    *current_thread_copy = current_thread; //Agora current_thread pode ser alterada, e o último elemento da fila é a thread atual
    insert_block_fila(current_thread_copy, tid);




    TCB_t * next_thread = get_next_thread();
    current_thread = *next_thread;
    LastFila2(&fila_blocked);

    swapcontext(&(((blocked_TCB *) GetAtIteratorFila2(&fila_blocked))->thread.context) ,&(current_thread.context));
    return 0;
}