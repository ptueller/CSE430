#include "q.h"
#include <stdlib.h>

int main() {
	queue *testQ1 = malloc(sizeof queue);
	testQ1->head = NewItem();
	testQ1->head->payload = 1;
	InitQueue(testQ1->head);
	qnode *tempNode = NewItem();
	tempNode->payload = 2;
	AddQueue(testQ1->head,tempNode);
	printf("Payload 1 = %d. Payload 2 = %d\n",testQ1->head->payload,testQ1->head->next->payload);
	DelQueue(testQ1->head);
	printf("Payload 1 = %d. Payload 2 = %d\n",testQ1->head->payload,testQ1->head->next->payload);
	DelQueue(testQ1->head);
	if(testQ1->head != NULL) {
		printf("Payload 1 = %d. Payload 2 = %d\n",testQ1->head->payload,testQ1->head->next->payload);
	}
}