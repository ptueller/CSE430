#include "sem.h"
#include <stdio.h>

/*
 * Name: Peter Tueller
 * CSE 430
 * Project 4
 * Description: Running the 3 readers, 2 writers problem
 */

struct sem_t *mutex, *rsem, *wsem;
int value = 0;
int wc =0;
int rc =0;
int rwc = 0;
int wwc = 0;


//Thread Functions
void reader1(void) {
	while(1) {
		P(mutex);
		if (wwc > 0 || wc > 0)
		{
			rwc++;
			V(mutex);
			P(rsem);
			rwc--;
		}
		rc++;
		if (rwc > 0) V(rsem);
		else V(mutex);

		printf("Reader 1 got value %d from Writer\n",value);

		P(mutex);
		rc--;
		if (rc == 0 && wwc > 0) V(wsem);
		else V(mutex);
	}	
 }
 void reader2(void) {
 	while(1) {
		P(mutex);
		if (wwc > 0 || wc > 0)
		{
			rwc++;
			V(mutex);
			P(rsem);
			rwc--;
		}
		rc++;
		if (rwc > 0) V(rsem);
		else V(mutex);

		printf("Reader 2 got value %d from Writer\n",value);

		P(mutex);
		rc--;
		if (rc == 0 && wwc > 0) V(wsem);
		else V(mutex);
 	}
 }

 void reader3(void) {
 	while(1) {
		P(mutex);
		if (wwc > 0 || wc > 0)
		{
			rwc++;
			V(mutex);
			P(rsem);
			rwc--;
		}
		rc++;
		if (rwc > 0) V(rsem);
		else V(mutex);

		printf("Reader 3 got value %d from Writer\n",value);

		P(mutex);
		rc--;
		if (rc == 0 && wwc > 0) V(wsem);
		else V(mutex);
 	}
 }
 
 void writer1(void) {
 	static int local = 0;
 	while(1) {
		P(mutex);
		if (rc > 0 || wc > 0)
		{
			wwc++;
			V(mutex);
			P(wsem);
			wwc--;
		}
		wc++;
		V(mutex);

		value = ++local;
		printf("Writer 1 wrote %d\n",local);

		P(mutex);
		wc--;
		if (rwc > 0) V(rsem);
		else if (wwc > 0) V(wsem);
 	}
 }

 void writer2(void) {
 	static int local = 0;
 	while(1) {
		P(mutex);
		if (rc > 0 || wc > 0)
		{
			wwc++;
			V(mutex);
			P(wsem);
			wwc--;
		}
		wc++;
		V(mutex);

		value = ++local;
		printf("Writer 2 wrote %d\n",local);

		P(mutex);
		wc--;
		if (rwc > 0) V(rsem);
		else if (wwc > 0) V(wsem);
 	}
 }
 
 int main() {
	mutex = malloc(sizeof(sem_t));
	rsem = malloc(sizeof(sem_t));
	wsem = malloc(sizeof(sem_t));
 	RunQ = malloc(sizeof(queue)); //Init RunQ
	mutex->semQ = malloc(sizeof(queue));
	rsem->semQ = malloc(sizeof(queue));
	wsem->semQ = malloc(sizeof(queue));
	InitQueue(RunQ);
	InitQueue(mutex->semQ);
	InitQueue(rsem->semQ);
	InitQueue(wsem->semQ);
 	InitSem(mutex,1);
 	InitSem(rsem,0);
	InitSem(wsem,0);
	start_thread(&writer1);
	start_thread(&writer2);
 	start_thread(&reader1); //Start Threads
	start_thread(&reader2);
	start_thread(&reader3);
 	run(); //Run
 }
