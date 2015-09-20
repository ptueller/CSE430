#include <stdlib.h>

typedef struct qnode qnode;
typedef struct queue queue;

struct qnode {
	qnode *prev;
	qnode *next;
	int payload;
};

struct queue {
	qnode *head;
};

qnode* NewItem() {
	return malloc(sizeof(qnode));
}

void FreeItem(qnode* head) {
	free(head);
}

void InitQueue(queue* q) {
	q->head->next = q->head;
	q->head->prev = q->head;
}

void AddQueue(queue* q, qnode* item) {
	q->head->prev->next = item;
	item->prev = q->head->prev;
	q->head->prev = item;
	item->next = q->head;
}

qnode* DelQueue(queue* q) {
	qnode* returnValue = q->head;
	q->head->next->prev = q->head->prev;
	q->head->prev->next = q->head->next;
	if(q->head != q->head->next) {
		q->head = q->head->next;
	}
	else {
		q->head = NULL;
	}
	return returnValue;
}

void RotateQueue(queue* q) {
	q->head = q->head->next;
}