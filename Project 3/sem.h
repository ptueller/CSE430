#include "threads.h"

typedef struct sem_t {
	int value;
	struct queue semQ;
};

void InitSem(struct sem_t *sem, int value) {
	sem->value=value;
}

void P(struct sem_t *sem) {
	sem->value--;
	if(sem->value<0) {
		AddQueue(sem->semQ,DelQueue(RunQ));
		swapcontext(&parent,&(RunQ->head->context)); //Execute the new head of the RunQ
	}
}

void V(struct sem_t *sem) {
	sem->value++;
	if(sem->value<=0) {
		AddQueue(RunQ,DelQueue(sem->semQ));
		yield();
	}
}
