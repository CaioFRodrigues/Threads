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

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "../include/internal.h"
#include "../include/support.h"
#include "../include/cdata.h"
#include "../include/cthread.h"

extern TCB_t main_thread;
extern TCB_t current_thread;
extern ucontext_t choose_thread_context; //Contexto sempre começa no choose_thread, então no final de cada thread é necessário ir para lá
extern FILA2 fila_threads[FILA_SIZE];                        // escolher a próxima

int tidCounter = 1; // Thread Identifier Counter
int init_flag = 0; // 0 - Biblioteca ainda não foi iniciada; 1 - Biblioteca já foi iniciada


//função ccreate (func, arg, prio)
//Cria uma nova thread de prioridade prio com a função func passando arg como argumento
//Inicializa diversas coisas internas da biblioteca
//Abdica do controle da thread ao final da função,chamando a próxima no escalonador
//Retorna -1 se não conseguir criar uma nova thread, e 0 caso consiga
int ccreate(void *(*start)(void *), void *arg, int prio)
{
    
    TCB_t *new_thread = (TCB_t *) malloc(sizeof(TCB_t)); //Ponteiro para nova thread que será posto na fila
    ucontext_t *new_thread_context = (ucontext_t *) malloc(sizeof(ucontext_t)); //Ponteiro do contexto da nova thread 

    if(getcontext(new_thread_context) == -1){ //Pega o contexto atual
        return -1;
    }
    


    if (init_flag == 0)  //Primeira execução do programa
        init();
    


    new_thread_context->uc_stack.ss_sp = malloc(MEM);
    new_thread_context->uc_stack.ss_size = MEM;
    new_thread_context->uc_link = &choose_thread_context;
    new_thread->state = PROCST_APTO;
    new_thread->tid = ++tidCounter;
    makecontext(new_thread_context, (void (*) (void)) start, 1, arg);
    new_thread->context = *new_thread_context;

    insert_thread(prio, new_thread);

    choose_thread();

    return tidCounter;
}

// Abdica do controle do processador e vai para a próxima thread
// retorna 0 se deu erro e -1 se ocorreu falha (não havia thread para trocar).
int cyield(){
    if (choose_thread() == 0)
        return 1;
    else return -1;
}


int csetprio(int tid, int prio){

    int i=0;
    TCB_t * tested_thread = (TCB_t *) malloc(sizeof(TCB_t));

    for (i=0; i<FILA_SIZE; i++){
        while (NextFila2(&fila_threads[i]) != 0){   // Enquanto houver threads na fila

            tested_thread = (TCB_t *) (GetAtIteratorFila2(&fila_threads[i]));   //Guardando o conteudo, nao o ponteiro

            if (tested_thread->tid == tid){
                if (tested_thread->ticket == prio)
                    return 0;

                tested_thread->ticket = prio;
                DeleteAtIteratorFila2(&fila_threads[i]);
                //Muda a thread para a fila apropriada
                insert_thread(prio, tested_thread);
                
                return 0;
            }

        }
    }

    return -1;

}

