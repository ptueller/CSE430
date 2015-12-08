#include <stdlib.h>
#include "tcb.h"

typedef struct queue queue;

struct queue {
	TCB_t *head;
};

queue* RunQ;

TCB_t* NewItem() {
	return malloc(sizeof(TCB_t));
}

void FreeItem(TCB_t* head) {
	free(head);
}

void InitQueue(queue* q) {
	if(q->head != NULL) {
		q->head->next = q->head;
		q->head->prev = q->head;
	}
}

void AddQueue(queue* q, TCB_t* item) {
    	if(q->head != NULL) {
		if(q->head->next != NULL) {
    		        item->prev = q->head->prev;
    		        item->next = q->head;
     		       	q->head->prev->next = item;
     		       	q->head->prev = item;
		} 
		else {
            		q->head->next = item;
            		q->head->prev = item;
            		item->next = q->head;
            		item->prev = q->head;
		}
    } 

    else {
        q->head = item;
        item->prev = NULL;
        item->next = NULL;
    }
}

TCB_t* DelQueue(queue* q) {
	TCB_t* returnValue = q->head;

    	if(q->head != NULL) {
        	if(q->head->next != NULL) {
            		q->head->prev->next = q->head->next;
            		q->head->next->prev = q->head->prev;
            		q->head = q->head->next;
        	}
        	else {
            		q->head = NULL;
        	}
    	}
	
	return returnValue;
}

void RotateQueue(queue* q) {
	AddQueue(q, DelQueue(q));
}
