#include "sem.h"
#include <stdio.h>

/*
 * Name: Sami Mian, Peter Tueller
 * CSE 430
 * Project 4
 * Description: Running the 3 readers, 2 writers problem
 */

#define BUFFER_SIZE 100

struct mesg {
	int id;
	int value;
};

struct sem_t *mutex, *rsem, *wsem, *rtry;
struct mesg buffer[BUFFER_SIZE];
int bufferCount=0;
int wc =0;
int rc =0;
 
//Thread Functions
void reader1(void) {
	while(1) {
		P(rtry);
		P(rsem);
		rc++;
		if(rc==1) P(mutex);
		V(rsem);
		V(rtry);
		
		while(bufferCount==0) {
			yield();
		}
		printf("Reader 1 got value %d from Writer %d\n",buffer[bufferCount].value,buffer[bufferCount].id);
		bufferCount--;

		P(rsem);
		rc--;
		if(rc==0) V(mutex);
		V(rsem);
		yield();
	}	
 }
 void reader2(void) {
 	while(1) {
		P(rtry);
		P(rsem);
		rc++;
		if(rc==1) P(mutex);
		V(rsem);
		V(rtry);
		
		while(bufferCount==0) {
			yield();
		}
		printf("Reader 2 got value %d from Writer %d\n",buffer[bufferCount].value,buffer[bufferCount].id);
		bufferCount--;

		P(rsem);
		rc--;
		if(rc==0) V(mutex);
		V(rsem);
		yield();
 	}
 }

 void reader3(void) {
 	while(1) {
		P(rtry);
		P(rsem);
		rc++;
		if(rc==1) P(mutex);
		V(rsem);
		V(rtry);
		
		while(bufferCount==0) {
			yield();
		}
		printf("Reader 3 got value %d from Writer %d\n",buffer[bufferCount].value,buffer[bufferCount].id);
		bufferCount--;

		P(rsem);
		rc--;
		if(rc==0) V(mutex);
		V(rsem);
		yield();
 	}
 }
 
 void writer1(void) {
 	static int local = 0;
	struct mesg *message = malloc(sizeof(struct mesg));
	message->id = 1;
 	while(1) {
 		P(wsem);
		wc++;
		if(wc==1) P(rtry);
		V(wsem);

		P(mutex);

		while(bufferCount>=BUFFER_SIZE) {
			yield();
		}
		message->value = local++;
		buffer[bufferCount++] = *message;

		V(mutex);
		
		P(wsem);
		wc--;
		if(wc==0) V(rtry);
		V(wsem);
		yield();
 	}
 }

 void writer2(void) {
 	static int local = 0;
	struct mesg *message = malloc(sizeof(struct mesg));
	message->id = 2;
 	while(1) {
 		P(wsem);
		wc++;
		if(wc==1) P(rtry);
		V(wsem);

		P(mutex);

		while(bufferCount>=BUFFER_SIZE) {
			yield();
		}
		message->value = local++;
		buffer[bufferCount++] = *message;

		V(mutex);

		P(wsem);
		wc--;
		if(wc==0) V(rtry);
		V(wsem);
		yield();
 	}
 }
 
 int main() {
	mutex = malloc(sizeof(sem_t));
	rsem = malloc(sizeof(sem_t));
	wsem = malloc(sizeof(sem_t));	
	rtry = malloc(sizeof(sem_t));
 	RunQ = malloc(sizeof(queue)); //Init RunQ
	mutex->semQ = malloc(sizeof(queue));
	rsem->semQ = malloc(sizeof(queue));
	wsem->semQ = malloc(sizeof(queue));
	rtry->semQ = malloc(sizeof(queue));
	InitQueue(RunQ);
	InitQueue(mutex->semQ);
	InitQueue(rsem->semQ);
	InitQueue(wsem->semQ);
	InitQueue(rtry->semQ);
 	InitSem(mutex,1);
 	InitSem(rsem,1);
	InitSem(wsem,1);
	InitSem(rtry,1);
 	start_thread(&reader1); //Start Threads
	start_thread(&reader2);
	start_thread(&reader3);
	start_thread(&writer1);
	start_thread(&writer2);
 	run(); //Run
 }
