#include "threads.h"
#include <stdio.h>

/*
 * Name: Sami Mian, Peter Tueller
 * CSE 430
 * Project 2
 */
 
 int value, sem1, sem2, sem3;
 
 //Thread Functions
 void thread1(void) {
 	int local = 0;
 	while(1) {
 		while(sem1==0) {
 			yield();
 		}
 		sem1--;
 		printf("Local value = %d, Global Value = %d\n",local++,value++);
 		sem2++;
 	}
 }
 
 void thread2(void) {
 	int local = 0;
 	while(1) {
 		while(sem2==0) {
 			yield();
 		}
 		sem2--;
 		printf("Local value = %d, Global Value = %d\n",local++,value++);
 		sem3++;
 	}
 }
 
 void thread3(void) {
 	int local = 0;
 	while(1) {
 		while(sem3==0) {
 			yield();
 		}
 		sem3--;
 		printf("Local value = %d, Global Value = %d\n",local++,value++);
 		sem1++;
 	}
 }
 
 int main() {
 	RunQ = malloc(sizeof(queue)); //Init RunQ
 	value = 0;
 	sem1 = 1;
 	sem2 = 0;
 	sem3 = 0;
 	startThread(&thread1); //Start Threads
 	startThread(&thread2);
 	startThread(&thread3);
 	run(); //Run
 }