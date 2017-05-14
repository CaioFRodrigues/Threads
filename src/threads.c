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
#include "../internal.h"
#include "../support.h"
#include "../cdata.h"
#include "../cthread.h"
#define NO_ARGUMENT 0



TCB_t main_tcb;
ucontext_t choose_thread_context; //Context that always begins at choose_thread
int tidCounter = 1; // Thread Identifier Counter
int init = 0; // 0 - init will begin //  1 - init has already occurred


int ccreate(void *(*start)(void *), void *arg, int prio)
{
    TCB_t *new_thread = (TCB_t *) malloc(sizeof(TCB_t));
    ucontext_t *new_thread_context = (ucontext_t *) malloc(sizeof(ucontext_t));
    char funcStack[16384];

    if(getcontext(uc) == -1){
        return -1;
    }


    if (init == 0)
    {
        init = 1;
        main_tcb.context = *new_thread_context;
        main_tcb.state = EXEC;
        main_tcb.tid = 0;
        getcontext(&choose_thread_context);
        choose_thread_context.ss_sp = funcStack;
        choose_thread_context.ss_size = sizeof(funcStack);
        choose_thread_context.uc_link = NULL;
        makecontext(&choose_thread_context, choose_thread(), NO_ARGUMENT)

    }

    new_thread_context.uc_stack.ss_sp = funcStack;
    new_thread_context.uc_stack.ss_size = sizeof(funcStack);
    new_thread_context.uc_link = choose_thread_context;
    new_thread->state = choose_thread_context;
    new_thread->tid = ++tidCounter;
    makecontext(new_thread_context, (void (*) (void)) start, 1, arg);
    new_thread->context = new_thread_context;

    choose_thread();

    



//    return newThread;
    return newThread.tid;
//    return 0;
}