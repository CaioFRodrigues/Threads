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
*   internal.c: funções auxiliares da implementação da interface
*
*   versão 1.0 - 07/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include "../internal.h"
#include "../support.h"
#include "../cdata.h"
#include "../cthread.h"

#define FILA_SIZE 4 
// Criação e inicialização da fila de threads
FILA2 fila_threads[FILA_SIZE];
for (int i = 0; i < FILA_SIZE; i++){
	fila_threads[FILA_SIZE] = CreateFila2;
} 


//Função control_thread(): Manuseia próxima thread a ser executada e checa a fila de bloqueios, garantindo 
control_thread(){
	//Checa a lista de bloqueios, para ver se alguma informação deve ser atualizada

	
	//Decide a próxima thread a ser executada
	int return_flag = 0;
	s_TCB* next_thread;
	if (choose_thread (next_thread))
		return_flag++;
	
}


// Função choose_thread(s_TCB* returning_thread): Escolhe a thread a ser executada a partir da fila de aptos e remove ela da fila;
// Se a função for executada com sucesso, ela retorna 1, senão, 0
// returning_thread: Ponteiro que estará apontando para a thread no final da função
int choose_thread(s_TCB* retuning_thread){

	for (int i = 0; i < FILA_SIZE;i++ )
		if(FirstFila2(&fila_threads[i])){  //Coloca o iterador para o primeiro da fila de thread
										   //caso não haja na primeira fila, tenta a próxima fila até o final das filas
			s_TCB * retuning_struct = GetatIteratorFila2(&fila_threads[i]);
			return 1;
	}
	return 0;
}

control_blocked();
