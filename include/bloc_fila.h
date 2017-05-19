/*
*   Ana Paula Mello - 260723
*   Arateus Meneses - 242260
*   Caio Rodrigues -261578
*
*   bloc_fila.c: funções auxiliares da uso da fila de bloqueados
*
*   versão 1.0 - 07/05/2017
*/



#ifndef __BLOQFILA__H
#define __BLOQFILA__H

#include "internal.h"

void insert_block_fila(TCB_t * thread, int waited_tid);
int free_thread();


#endif