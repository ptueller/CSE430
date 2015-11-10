#include "sem.h"
#include <stdio.h>

/*
 * Name: Sami Mian, Peter Tueller
 * CSE 430
 * Project 3
 * Description: Three threads will spawn and will take turns updating a global variable and printing it.
 * Each thread has its own local variable that is also updates and prints. The turn taking is done using busy waiting semaphores.
 */
 
 int value;
struct sem_t *sem1, *sem2;
 
 //Thread Functions
 void thread1(void) {
 	static int local = 0;
 	while(1) {
 		P(sem1);
 		printf("Thread1: Local value = %d, Global Value = %d\n",local++,value++);
 		V(sem2);
 	}
 }
 
 void thread2(void) {
 	static int local = 0;
 	while(1) {
 		P(sem2);
 		printf("Thread2: Local value = %d, Global Value = %d\n",local++,value++);
 		V(sem1);
 	}
 }
 
 int main() {
	sem1 = malloc(sizeof(sem_t));
	sem2 = malloc(sizeof(sem_t));	
 	RunQ = malloc(sizeof(queue)); //Init RunQ
	sem1->semQ = malloc(sizeof(queue));
	sem2->semQ = malloc(sizeof(queue));
	InitQueue(RunQ);
	InitQueue(sem1->semQ);
	InitQueue(sem2->semQ);
 	value = 0;
 	InitSem(sem1,1);
 	InitSem(sem2,0);
 	start_thread(&thread1); //Start Threads
 	start_thread(&thread2);
 	run(); //Run
 }
