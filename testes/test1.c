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

// testar caso grande com ccreate e cyield
// varias funcoes com varias prioridades :D

void* func1(void* arg){
	printf ("1: OI, EU SOU CAIO, EU VOO EM UMA NUVEM VOADORA\n");
	cyield ();
	printf("1: OI CAIO, EU NAO SABIA QUE VOCE ERA UM PIRATA, MAS SIM UM SAYAJIN\n");
	return 0;
}

void* func2(void* arg){
	printf("2: TENS RAZAO, VOU VIRAR ATE SUPER SAYAJIN %d\n", *((int *)saiyan));
	cyield();
	printf("2: IMPOSSIVEL, SEU PODER DE LUTA EH MAIS DE 8000\n");
	return 0;	
}

void* func3(void* saiyan){
	printf("3: NOSSA QUE LEGAL! EU GOSTO DE COMER PANQUECAS\n");
	cyield();
	printf ("3: YAR\n");
	return 0;	
}

void* func4(void* arg){
	printf("4: QUE MASSA, SEMPRE GOSTEI DE USAR CALCAS JEANS\n");
	cyield();
	return 0;
}

void* func5(void* arg){
	printf("4: FON\n");
	cyield();
	return 0;
}

int main(){
	int* arg = malloc(sizeof(int));
	int best_saiyan = 4;
	// ccreate(func1, arg, 0);
	ccreate(func2, arg, 0);
	ccreate(func4, arg, 1);
	ccreate(func3, (void*)&best_saiyan, 0);
	ccreate(func5, arg, 2);
	printf("Todos sabemos que Dragon Ball GT eh o melhor Dragon Ball\n");
	cyield();
	printf("S2 Caio S2\n");
	cyield();
	cyield();
	cyield();
	cyield();
	cyield();
	cyield();



	return 0;
}