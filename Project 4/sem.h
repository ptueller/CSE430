#include "threads.h"

typedef struct sem_t {
	int value;
	struct queue *semQ;
} sem_t;

void InitSem(struct sem_t *sem, int value) {
	sem->value=value;
}

void P(struct sem_t *sem) {
	TCB_t *swap;
	sem->value--;
	if(sem->value<0) {
		swap = DelQueue(RunQ);
		AddQueue(sem->semQ,swap); //Take this TCB out of the RunQ and put it in the waiting semQ
		swapcontext(&(swap->context),&(RunQ->head->context)); //Execute the new head of the RunQ
	}
}

void V(struct sem_t *sem) {
	sem->value++;
	if(sem->value<=0) {
		AddQueue(RunQ,DelQueue(sem->semQ)); //Take this TCB out of the semQ and put it in the RunQ
	}
	yield();
}
