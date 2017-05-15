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

extern int tidCounter; // Thread Identifier Counter
extern int init_flag; // 0 - Biblioteca ainda não foi iniciada; 1 - Biblioteca já foi iniciada



int ccreate(void *(*start)(void *), void *arg, int prio)
{
    TCB_t *new_thread = (TCB_t *) malloc(sizeof(TCB_t));
    ucontext_t *new_thread_context = (ucontext_t *) malloc(sizeof(ucontext_t));

    if(getcontext(new_thread_context) == -1){
        return -1;
    }


    if (init_flag == 0)  //Primeira execução do programa
    {
        init();
    }


    new_thread_context->uc_stack.ss_sp = malloc(MEM);
    new_thread_context->uc_stack.ss_size = MEM;
    new_thread_context->uc_link = &choose_thread_context;
    new_thread->state = PROCST_APTO;
    new_thread->tid = ++tidCounter;
    makecontext(new_thread_context, (void (*) (void)) start, 1, arg);
    new_thread->context = *new_thread_context;

    choose_thread();

    
    return 0;
}
