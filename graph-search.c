/*
 * graph-search.c
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>


/* for graph */
typedef struct graph {
	int vertex;
	struct graph *link;
} Graph;

/* for stack */
#define MAX_STACK_SIZE		20
Graph* stack[MAX_STACK_SIZE];
int top = -1;

Graph* pop();
void push(Graph* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Graph* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Graph* deQueue();
void enQueue(Graph* aNode);

/* functions that you have to implement */
int initializeGraph(Graph** h);
int freeGraph(Graph* h);
int InsertVertex(Graph* h,int);
int InsertEdge(Graph* h,int, int);
void DFS(Graph* h);
void BFS(Graph* h);
void PrintGraph(Graph* h);
void freeVertex(Graph *ptr);


int main()
{
	char command;
	int v1,v2;
    Graph* head=NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph search                           \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                     \n");
		printf(" Insert Vertex          = v      Insert Edge               = e \n");
		printf(" Depth First Search     = d      Breath First Search        = b \n");
		printf(" Print Graph            = p      Quit                       = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeGraph(&head);
			break;

        case 'q': case 'Q':
			freeGraph(head);
			break;
        
        case 'v': case 'V':
            printf("Your Key = ");
            scanf("%d",&v1);
			InsertVertex(head,v1);
			break;

        case 'e': case 'E':
            printf("Your Key (v1) = ");
            scanf("%d",&v2);
            printf("Your Key (v1) = ");
            scanf("%d",&v2);
			InsertEdge(head,v1,v2);
			break;

        case 'd': case 'D':
			DFS(head);
			break;

        case 'b': case 'B':
			BFS(head);
			break;

        case 'p': case 'P':
			PrintGraph(head);
			break;
		
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeGraph(Graph** h){
    if(*h!=NULL)
        freeGraph(*h);

    *h=(Graph*)malloc(sizeof(Graph)*10);
    for(int i=0;i<10;i++){
        (*h+i)->link=NULL;
        (*h+i)->vertex=i;
    }

    top=-1;

    front = rear = -1;

    return 1;
}

void freeVertex(Graph *ptr){
    if(ptr){
        freeVertex(ptr->link);
        free(ptr);
    }
}

int freeGraph(Graph* h){
    for(int i=0;i<10;i++){

        if((h+i)->link){
           freeVertex((h+i)->link);
        }
    }

    free(h);
    return 0;
}

int InsertVertex(Graph* h,int v1){

}

int InsertEdge(Graph* h,int v1, int v2){

}

void DFS(Graph* h){

}

void BFS(Graph* h){

}

void PrintGraph(Graph* h){

}

Graph* pop()	//stack pop
{
	if(top==-1)	return NULL;	
	else return stack[top--];
}

void push(Graph* aNode)	//stack push 
{	if(top==MAX_STACK_SIZE-1) printf("stack is full\n");	
	else stack[++top]=aNode;	
}



Graph* deQueue()	//deQueue
{
	if(front==rear)	return 0;	
	else return queue[++front];	
}

void enQueue(Graph* aNode)	//enQueue
{
	if(rear==MAX_QUEUE_SIZE-1)	printf("queue is full\n");	
	else queue[++rear]=aNode;
}