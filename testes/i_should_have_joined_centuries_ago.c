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
	cyield();
	printf ("Func 1 / print 3 after yield 2\n");
	cyield();
	printf ("Func 1 / print 4 after yield 3\n");
	return 0;
}

void* func2(void* arg){

	printf("Func 2 / print 1 before yield\n");
	cyield();
	printf("Func 2 / print 2 after yield\n");
	cyield();
	printf ("Func 2 / print 3 after yield 2\n");
	cjoin(*((int *)arg));
	printf ("Func 2 / print final after join -> func3 has ended\n");
	return 0;
}

void* func3(void* arg){

	printf("Func 3 / print 1 before yield\n");
	cyield();
	printf("Func 3 / print 2 after yield\n");
	return 0;
}

int main(){
	void * arg = NULL;
	int tid,tid2,tid3;

	tid = ccreate(func1, arg, 1);
	tid3 = ccreate(func3,arg,3);
	tid2 = ccreate(func2,&tid2,0);
	
	cjoin(tid3);
	printf ("Func2 has ended for sure\n");
	cjoin(tid);
	printf ("Func 1 has ended for sure\n");
	printf ("Func 1 and func 2 have ended\n");
	return 0;
}