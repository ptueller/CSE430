#include "sem.h"
#include <stdio.h>

/*
 * Name: Sami Mian, Peter Tueller
 * CSE 430
 * Project 3
 * Description: Running the 2 producers, 2 consumers problem using semaphores in
 * sem.h.
 */

#define BUFFER_SIZE 32

struct mesg {
	int id;
	int value;
};

struct sem_t *mutex, *fillCount, *emptyCount;
struct mesg buffer[BUFFER_SIZE];
int bufferCount = 0;
 
 //Thread Functions
 void producer1(void) {
 	static int local = 0;
	struct mesg *message = malloc(sizeof(struct mesg));
	message->id = 1;
 	while(1) {
 		P(emptyCount);
		P(mutex);
		message->value = local++;
 		buffer[bufferCount++]=*message;
 		V(mutex);
		V(fillCount);
 	}
 }
 void producer2(void) {
 	static int local = 0;
	struct mesg *message = malloc(sizeof(struct mesg));
	message->id = 2;
 	while(1) {
 		P(emptyCount);
		P(mutex);
		message->value = local++;
 		buffer[bufferCount++]=*message;
 		V(mutex);
		V(fillCount);
 	}
 }
 
 void consumer1(void) {
 	while(1) {
 		P(fillCount);
		P(mutex);
		bufferCount--;
 		printf("Consumer 1 got value %d from Producer %d\n",buffer[bufferCount].value,buffer[bufferCount].id);
 		V(mutex);
		V(emptyCount);
 	}
 }

 void consumer2(void) {
 	while(1) {
 		P(fillCount);
		P(mutex);
		bufferCount--;
 		printf("Consumer 2 got value %d from Producer %d\n",buffer[bufferCount].value,buffer[bufferCount].id);
 		V(mutex);
		V(emptyCount);
 	}
 }
 
 int main() {
	mutex = malloc(sizeof(sem_t));
	fillCount = malloc(sizeof(sem_t));
	emptyCount = malloc(sizeof(sem_t));	
 	RunQ = malloc(sizeof(queue)); //Init RunQ
	mutex->semQ = malloc(sizeof(queue));
	fillCount->semQ = malloc(sizeof(queue));
	emptyCount->semQ = malloc(sizeof(queue));
	InitQueue(RunQ);
	InitQueue(mutex->semQ);
	InitQueue(fillCount->semQ);
	InitQueue(emptyCount->semQ);
 	InitSem(mutex,1);
 	InitSem(fillCount,0);
	InitSem(emptyCount,BUFFER_SIZE);
 	start_thread(&producer1); //Start Threads
 	start_thread(&producer2);
	start_thread(&consumer2);
	start_thread(&consumer1);
 	run(); //Run
 }
