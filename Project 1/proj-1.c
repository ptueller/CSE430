#include "q.h"
#include <stdio.h>

int main() {
	queue *testQ1 = malloc(sizeof(queue));
	queue *testQ2 = malloc(sizeof(queue));
	testQ1->head = NewItem();
	testQ1->head->payload = 1;
	testQ2->head = NewItem();
	testQ2->head->payload = 10;
	InitQueue(testQ1); //Make sure to allocate memory for both the queue and the head before this point!
	InitQueue(testQ2);
	qnode *tempNode = NewItem();
	tempNode->payload = 2;
	AddQueue(testQ1,tempNode);
	printf("Queue 1 head = %d\n",testQ1->head->payload);
	printf("Queue 2 head = %d\n",testQ2->head->payload);
	RotateQueue(testQ1);
	printf("Queue 1 head = %d\n",testQ1->head->payload);
	printf("Queue 2 head = %d\n",testQ2->head->payload);
	DelQueue(testQ1);
	printf("Queue 1 head = %d\n",testQ1->head->payload);
	printf("Queue 2 head = %d\n",testQ2->head->payload);
	qnode *tempNode2 = NewItem();
	tempNode2->payload = 3;
	AddQueue(testQ1,tempNode2);
	AddQueue(testQ2,tempNode);
	RotateQueue(testQ1);
	RotateQueue(testQ2);
	printf("Queue 1 head = %d\n",testQ1->head->payload);
	printf("Queue 2 head = %d\n",testQ2->head->payload);
	RotateQueue(testQ1);
	RotateQueue(testQ2);
	printf("Queue 1 head = %d\n",testQ1->head->payload);
	printf("Queue 2 head = %d\n",testQ2->head->payload);
	free(testQ1);
	free(testQ2);
}