#include <stdio.h>
#include <stdlib.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct {
	char *name;
	int remaining_time;
} Process, *Item;
/*
 *
 */
typedef struct Node {
	Item data;
	struct Node* next;
} Node;
/*
 *
 */
typedef struct {
	Node* head;
	Node* tail;
} Queue;
/*
 *
 */
void init(Queue *q) {
	q->head = NULL;
	q->tail = NULL;
}
/*
 *
 */
int isEmpty(Queue *q) {
	if (q->head == NULL) {return 1;}
	return 0;
}
/*
 *
 */
Item dequeue(Queue *q) {
	if (q->head == NULL) {return NULL;}
	Item temp=q->head->data;
	Node* node =q->head;
	if (q->head->next == NULL) { q->head = NULL;q->tail = NULL; }
	else { q->head = q->head->next; }
	free(node);
	return temp;
}
/*
 *
 */
void enqueue(Queue* q, Item val) {
	Node* node;
	node = malloc(sizeof(Node));
	node->data = val;
	if (q->tail == NULL) {q->tail = node; q->head = node;}
	else { q->tail->next = node; q->tail = node;}
	node->next = NULL;
}
/*
 *
 */
void destroy(Queue *q) {
	while (q->head != NULL) {
		dequeue(q);
	}
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
	Process* process;
	Item impProcesses[50];
	int startTime[50];
	char* processName;
	int processesCount=0;

	Queue* CPU;
	CPU = malloc(sizeof(Queue));
	init(CPU);

FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("file not found");
		return;
	}

	for(int i=0 ;!feof(fp) ;i++ ) {
		process = malloc(sizeof(Process));
		processName = malloc(sizeof(char)*3);

		fscanf(fp, "%s ", processName);
		*(processName+2) = '\0';
		process->name = processName;
		fscanf(fp, "%d ", &startTime[i]);
		fscanf(fp, "%d\n", &(process->remaining_time));

		impProcesses[i] = process;
		processesCount++;
	}
	fclose(fp);

	int timeFlow=0;
	int haltCount=0;

	for(int j=0;j<processesCount;j++){
						if(startTime[j]==timeFlow) {
						enqueue(CPU,impProcesses[j]);
							}
						}

		for(haltCount=0;haltCount<processesCount;){

		if(isEmpty(CPU)) {printf("idle  (%d-->%d)\n",timeFlow ,timeFlow+1);}
			else{
					process = malloc(sizeof(Process));
					process = dequeue(CPU);
					process->remaining_time--;
					printf("%s  (%d-->%d)\n",process->name,timeFlow ,timeFlow+1);
					if(process->remaining_time==0){
					printf("%s halts\n",process->name);
					haltCount++;
					}
					else{
						for(int j=0;j<processesCount;j++){
							if(startTime[j]==timeFlow+1) {
								enqueue(CPU,impProcesses[j]);
								}
							}
						enqueue(CPU,process);
						timeFlow++;
						continue;
						}
					}
					for(int j=0;j<processesCount;j++){
						if(startTime[j]==timeFlow+1) {
							enqueue(CPU,impProcesses[j]);
						}
					}
					timeFlow++;
	}
		//correct dequeue for current process
		//remaining time--
		//check if there's any remaining time in the current process to enqueue
		//and check if there's a new process that should enter at the same second
		//enque the new process
	printf("EOF\n");
}
/*
 *
 */
int main(int argc, char**argv) {
	if(argc!=2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
	RoundRobin(argv[1]);
	return 0;
}

