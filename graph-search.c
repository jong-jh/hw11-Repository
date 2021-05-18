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
void DFS(Graph* h, int);
void BFS(Graph* h, int);
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
		printf(" Insert Vertex          = v      Insert Edge                = e \n");
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
            scanf("%d",&v1);
            printf("Your Key (v2) = ");
            scanf("%d",&v2);
			InsertEdge(head,v1,v2);
			break;

        case 'd': case 'D':
			printf("Your Key = ");
            scanf("%d",&v1);
			DFS(head, v1);
			break;

        case 'b': case 'B':
			printf("Your Key = ");
            scanf("%d",&v1);
			BFS(head, v1);
			break;

        case 'p': case 'P':
			PrintGraph(head);
			break;
		
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;
}

int initializeGraph(Graph** h){
    if(*h!=NULL)
        freeGraph(*h);

    *h=(Graph*)malloc(sizeof(Graph)*10);
    for(int i=0;i<10;i++){
        (*h+i)->link=NULL;
        (*h+i)->vertex=-1;	//각 헤더노드의 vertex를 -1으로 초기화
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
   (h+v1)->vertex = v1;

   return 1;
}

int InsertEdge(Graph* h,int v1, int v2){
	if((h+v1)->vertex==-1||(h+v2)->vertex==-1){
		printf("\n key is not in graph \n");
		return 0;
	}


	Graph* temp1 =(Graph*)malloc(sizeof(Graph));		//새로운 값이 들어갈 공간 생성
	Graph* temp2 =(Graph*)malloc(sizeof(Graph));		//새로운 값이 들어갈 공간 생성
	Graph* p=(h+v1);	//헤드노드의 해당되는 인덱스와 연결.

	temp1->vertex=v1;
	temp1->link=NULL;
	temp2->vertex=v2;
	temp2->link=NULL;

	while(1){
		if(p->vertex==v2){// 이미 연결되어있다면
			printf("\n Edge already exist \n");
			return 0;
		}

		if(!p->link){	//가리키는 노드가 없다면 연결
			p->link=temp2;	//v1 이 v2 를 가리킴
			break;
		}

		if(p->link->vertex > v2){	//인접리스트를 vertex 크기 순으로 정렬
			temp2->link=p->link;
			p->link=temp2;
			break;
		}

		else p=p->link;		// 다음 노드가 존재한다면 이동
	}
	
	p=(h+v2);
	while(1){
		if(!p->link){ 
			p->link=temp1;	//v2 가 v1을 가리킴
			break;
		}
		if(p->link->vertex > v1){ //인접리스트를 vertex 크기 순으로 정렬
			temp1->link=p->link;
			p->link=temp1;
			break;
		}
		else p=p->link;
	}

	return 0;
}

/*Depth First Search (iteratvie)*/

void DFS(Graph* h,int v){
	if((h+v)->vertex==-1){
		printf("\n key is not in graph \n");
		return ;
	}
	Graph* p = h+v;	//그래프를 가리키는 포인터
	Graph* ptr = NULL;	//stack 의 pop을 받을 ptr

	int visited[10]; for(int i=0;i<10;i++){visited[i]=0;}	//visit flag  0으로 초기화
	top = -1;	//stack top 초기화

	//visited[v]=1;	//방문 노드 1 표시
	//push(h+v);

	while(1){
		
		v=p->vertex;	//헤더노드의 vertex를 받는다.

		if(!visited[v]){	//해당 vertex에 방문하지 않았다면
			printf("  [%d]  ",v);	//값을 출력
			visited[v]=1;			//방문 flag
			push(h+v);				//stack 에 push
			p=h+v;					//해당 값을 가진 헤더노드로 이동
		}
		else {			//해당 vertex에 방문을 했다면
			if(p->link==NULL){	//다음 노드가 존재하지 않는다면
				ptr=pop();		//stack 을 pop 해준다.
				//printf(" [%d] ", ptr->vertex);
				p=h+(p->vertex);	//헤더노드 이동
			}
			p=p->link;	//노드 이동
		}

		if(top==-1)	break;	//stack이 비워지면 반복문 탈출
	}

}

void BFS(Graph* h, int v){
	Graph* p=h+v;		//그래프를 가리킬 포인터
	
	if((h+v)->vertex==-1){
		printf("\n key is not in graph \n");
		return ;
	}

	int visited[10]; for(int i=0;i<10;i++){visited[i]=0;}	//visit flag  0으로 초기화
	rear=front=-1;

	printf("  [%d]  ",v);
	visited[v]=1;
	enQueue(p);

	while(1){
		p=deQueue();
		for(p;p;p=p->link){
			v=p->vertex;
			if(!visited[v]){
				printf("  [%d]  ",p->vertex);
				enQueue(h+v);
				visited[v]=1;
			}
		}
		if(rear==front) break;
	}
}

void PrintGraph(Graph* h){
	Graph* p=h;

	for(int i=0;i<10;i++){
		p=h+i;
		for(int j=0;j<10;j++){
			if(p->vertex!=-1){
				printf(" [%d] ",(p->vertex));
			}
			if(p->link){
				p=p->link;
			}
			else
				break;
		}
		printf("\n");
	}
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