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
*   bloc_fila.c: funções auxiliares da uso da fila de bloqueados
*
*   versão 1.0 - 07/05/2017
*/



#include "../include/bloc_fila.h"


//Função insert_blocfila(thread, codigo)
void insert_block_fila(TCB_t * thread, int expected_tid){
	blocked_TCB* blocked_thread = malloc(sizeof(blocked_TCB));
	blocked_thread->expected_tid = expected_tid;
	blocked_thread->thread = *thread;

	AppendFila2(&fila_blocked, blocked_thread);
}

//Função search_block_fila(tid): Procura uma thread na lista de bloqueados pelo tid e retorna um ponteiro para a estrutura contendo ela
//O iterador da fila estará sobre ela também, bastando usar DeleteAtIteratorFila2() para eliminar ela
//Retorna NULL se a thread não estiver na fila de bloqueados
//Para acessar a thread em si, usar search_block_fila(tid)->thread
//NOTA: A THREAD DENTRO DA ESTRUTURA NÃO É UM PONTEIRO
blocked_TCB * search_block_fila(int tid){
	blocked_TCB * current_thread;
	int cur = FirstFila2(&fila_blocked); //Inicializa o loop
	while (cur == 0){  

		current_thread = (blocked_TCB *) GetAtIteratorFila2(&fila_blocked); //Pega a thread do iterador atual

		if (current_thread->expected_tid == tid)  // Se a busca foi encontrada
			return current_thread;
		
		cur = NextFila2(&fila_blocked); //Checa se existe algo na próxima posição da fila
	}
	return NULL;
}
