#include "q.h"
#include <stdio.h>

int main() {
	queue *testQ1 = malloc(sizeof(queue));
	testQ1->head = NewItem();
	testQ1->head->payload = 1;
	InitQueue(testQ1);
	qnode *tempNode = NewItem();
	tempNode->payload = 2;
	AddQueue(testQ1,tempNode);
	printf("Payload 1 = %d. Payload 2 = %d\n",testQ1->head->payload,testQ1->head->next->payload);
	RotateQueue(testQ1);
	printf("Payload 1 = %d. Payload 2 = %d\n",testQ1->head->payload,testQ1->head->next->payload);
	DelQueue(testQ1);
	printf("Payload 1 = %d. Payload 2 = %d\n",testQ1->head->payload,testQ1->head->next->payload);
	qnode *tempNode2 = NewItem();
	tempNode2->payload = 3;
	AddQueue(testQ1,tempNode2);
	AddQueue(testQ1,tempNode);
	printf("Payload 1 = %d. Payload 2 = %d\n",testQ1->head->payload,testQ1->head->next->payload);
	RotateQueue(testQ1);
	printf("Payload 1 = %d. Payload 2 = %d\n",testQ1->head->payload,testQ1->head->next->payload);
	RotateQueue(testQ1);
	printf("Payload 1 = %d. Payload 2 = %d\n",testQ1->head->payload,testQ1->head->next->payload);
	free(testQ1);
}