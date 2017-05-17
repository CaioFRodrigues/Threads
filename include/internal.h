/*
*   Ana Paula Mello - 260723
*   Arateus Meneses - 242260
*   Caio Rodrigues -261578
*
*   internal.h: funções auxiliares da implementação da interface
*
*   versão 1.0 - 07/05/2017
*/
#ifndef	__INTERNAL_H__
#define	__INTERNAL_H__

#include <ucontext.h>
#include "cdata.h"
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#include "support.h"
#include "cdata.h"
#include "cthread.h"

#define FILA_SIZE 4 
#define TRUE 1
#define FALSE 0
#define NO_ARGUMENT 0
#define MEM 64000
#define	PROCST_CRIACAO	0
#define	PROCST_APTO	1
#define	PROCST_EXEC	2
#define	PROCST_BLOQ	3
#define	PROCST_TERMINO	4
#define FILA_SIZE 4 


TCB_t main_thread;
TCB_t current_thread;
ucontext_t choose_thread_context; //Contexto sempre começa no choose_thread, então no final de cada thread é necessário ir para lá
FILA2 fila_threads[FILA_SIZE];                        // escolher a próxima

extern int tidCounter; // Thread Identifier Counter
extern int init_flag; // 0 - Biblioteca ainda não foi iniciada; 1 - Biblioteca já foi iniciada



void init();

int control_thread();

int choose_thread();

int control_blocked();

void change_context(int fila, TCB_t *next_thread);

void insert_thread(int fila, TCB_t *new_thread);
#endif
