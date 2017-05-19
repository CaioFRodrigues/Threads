/*
*   UFRGS - Universidade Federal do Rio Grande do Sul
*   Instituto de Informática
*   INF01142 - Sistemas Operacionais I (2017/1)
*
*   Trabalho Prático I - Biblioteca de Threads cthreads 17.1
*
*   Ana Paula Mello - 260723 <apcomello@gmail.com>
*   Arateus Meneses - 242260 <arateus.meneses@gmail.com>
*   Caio Rodrigues - 261578  <caio_f.r@hotmail.com>
*
*   I_am_the_future_test.c: primeiro arquivo de teste
*
*   versão 1.0 - 07/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/internal.h"
#include "../include/support.h"
#include "../include/cdata.h"
#include "../include/cthread.h"
#include <ucontext.h>

void* func1(void* arg){
	printf("Func 1 / print 1 before yield\n");
	cyield();
	printf("Func 1 / print 2 after yield\n");
	return 0;
}

void* func2(void* arg){

	printf("Func 2 / print 1 before yield\n");
	cyield();
	printf("Func 2 / print 2 after yield\n");
	return 0;
}

void* func3(void* arg){

	printf("Func 3 / print 1 before yield\n");
	cyield();
	printf("Func 3 / print 2 after yield\n");
	return 0;
}

int main(){
	int* arg = malloc(sizeof(int));
	int tid[3];
	tid[0] = ccreate(func1, arg, 0);
	tid[1] = ccreate(func2, arg, 0);
	tid[2] = ccreate(func3, arg, 0);
	printf("func1 tid: %d\n", tid[0]);
	printf("func2 tid: %d\n", tid[1]);
	printf("func3 tid: %d\n", tid[2]);
	printf("\nTHIS SHOULD BE THE MIDDLE OF THE TEST\n\n");
	cyield();
	cyield();
	cyield();
	cyield();
	cyield();
	cyield();

	return 0;
}