
typedef struct qnode {
	qnode *prev;
	qnode *next;
	int payload;
} qnode;

typedef struct queue {
	qnode *head;
} queue;

qnode* NewItem() {
	return malloc(sizeof(qnode));
}

void FreeItem(qnode* head) {
	free(head);
}

void InitQueue(qnode* head) {
	head->next = head;
	head->prev = head;
	queue->head = head;
}

void AddQueue(qnode* head, qnode* item) {
	qnode *iterator = head;
	while(iterator->next != head) {
		iterator = iterator->next;
	}
	item->next = head;
	item->prev = iterator;
	iterator->next = item;
	head->prev = item;
}

qnode* DelQueue(qnode* head) {
	head->next->prev = head->prev;
	head->prev->next = head->next;
	if(head != head->next) {
		queue->head = head->next;
	}
	else {
		queue->head = NULL;
	}
	return head;
}

void RotateQueue(qnode* head) {
	
}