
typedef struct qnode {
	qnode *prev;
	qnode *next;
	int payload;
} qnode;

qnode* NewItem() {
	return malloc(sizeof(qnode));
}

void FreeItem(qnode* head) {
	free(head);
}

void InitQueue(qnode* head) {
	
}

void AddQueue(qnode* head, qnode* item) {
	
}

qnode* DelQueue(qnode* head) {
	
}

void RotateQueue(qnode* head) {
	
}