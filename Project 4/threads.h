#include "q.h"

void start_thread(void (*function)(void))
{
     void *stack = malloc(8192); //allocate a stack (via malloc) of a certain size (choose 8192)
     TCB_t *tcb = NewItem(); //allocate a TCB (via malloc)
     init_TCB(tcb,function,stack,8192); //call init_TCB with appropriate arguments
     AddQueue(RunQ,tcb); //call addQ to add this TCB into the “RunQ” which is a global header pointer
}

void run()
{
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(RunQ->head->context));  // start the first thread
}

void yield() // similar to run
{
	ucontext_t parent;
	getcontext(&parent);
	RunQ->head->context = parent;
	RotateQueue(RunQ); //rotate the run Q;
	swapcontext(&parent,&(RunQ->head->context)); //swap the context, from previous thread to the thread pointed to by RunQ
}
