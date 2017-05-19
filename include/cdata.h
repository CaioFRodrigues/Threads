/*
 * cdata.h: arquivo de inclus�o de uso apenas na gera��o da libpithread
 *
 * Esse arquivo pode ser modificado. ENTRETANTO, deve ser utilizada a TCB fornecida
 *
 * Vers�o de 25/04/2017
 *
 */
#ifndef __cdata__
#define __cdata__

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
#define TRUE 1
#define FALSE 0

#include <ucontext.h>


/* N�O ALTERAR ESSA struct */
typedef struct s_TCB { 
	int		tid; 		// identificador da thread
	int		state;		// estado em que a thread se encontra
					// 0: Cria��o; 1: Apto; 2: Execu��o; 3: Bloqueado e 4: T�rmino
	int 		ticket;		// "bilhete" de loteria da thread, para uso do escalonador
	ucontext_t 	context;	// contexto de execu��o da thread (SP, PC, GPRs e recursos) 
} TCB_t; 

typedef struct s_blocked_TCB{
	int expected_tid;
	TCB_t thread;
} blocked_TCB;


#endif
