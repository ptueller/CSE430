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

void InitQueue(qnode* head) {
	head->next = head;
	head->prev = head;
}

void AddQueue(qnode* head, qnode* item) {
	item->next = head;
	item->prev = head->prev->prev;
	head->prev = item;
}

qnode* DelQueue(qnode* head) {
	qnode* returnValue = head;
	head->next->prev = head->prev;
	head->prev->next = head->next;
	if(head != head->next) {
		head = head->next;
	}
	else {
		head = NULL;
	}
	return returnValue;
}

void RotateQueue(qnode* head) {
	head = head->next;
}