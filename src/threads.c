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
#include "../internal.h"
#include "../support.h"
#include "../cdata.h"
#include "../cthread.h"

int cidentify(char *name, int size){
	char devs[] = {"Ana Paula Mello 260723\nArateus Meneses 242260\nCaio Rodrigues 261578\0"};
    name[size] = '\0';
    if(strncpy(name, devs, size))
        return 0;
    else
        return -1;
}

int csetprio(int tid, int prio){

	int i=0, current_prio=0;
	TCB_t * tested_thread = (TCB_t *) malloc(sizeof(TCB_t));

	for (i=0; i<FILA_SIZE; i++){
		while (TRUE){	// Enquanto houver threads na fila

			*(tested_thread) = *(GetAtIteratorFila2(&fila_threads[i]));	//Guardando o conteudo, nao o ponteiro

			if (tested_thread.tid == tid){
				current_prio = tested_thread.ticket; // Necessario? Nao lembro por que fiz isso
				tested_thread.ticket = prio;
				//Muda a thread para a fila apropriada
				DeleteAtIteratorFila2(&fila_threads[i]));
				AppendFila2(fila_threads[tested_thread], &fila_threads[i]));
				return 0;
			}

			if (NextFila2(fila_threads[i]) != 0) // Fila acabou ou esta vazia
				break;
		}
	}

	return -1;

}
