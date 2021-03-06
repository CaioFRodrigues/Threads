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
	printf ("OIOIOI\n");
	cyield ();
	printf ("YAR\n");
	return 0;
}

int main(){
	int* arg = malloc(sizeof(int));
	ccreate(func1, arg, 0);
	printf ("Encerrando main\n");
	cyield();
	printf ("IT WORKS!!!Maybe...\n");

  return 0;
}
