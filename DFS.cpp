#include<stdio.h>
#include<stdlib.h>
//vertex의 개수가 4일 때
//vertex는 0부터 3라고 하자
#define NUM 5

int *graph=0; //1차원 배열로

int *stack = 0; 
int top = -1;
int *visit = 0;

struct node {
	int n;
	struct node *next;
};

struct node *head = 0;

int compareStack(int ad)
{
	//stack안에 있는지 비교
	for (int i = 0; i < NUM; i++)
	{
		if (stack[i] == ad) //stack에 존재한다!
		{
			return 1;
		}
	}
	return 0;
}

//stack 
void push(int n)
{
	//n은 vertex
	if (top == NUM-1)
	{
		return;
	}
	top = top + 1;
	stack[top] = n;
	return;
}


int pop()
{
	if (top == -1)
	{
		//아무것도 없다.
		return -999;
	}
	top = top - 1;
	return stack[top + 1];
}

void addToEdge(int vertex_1, int vertex_2)
{
	//배열이므로 1을 넣어주면됨!
	graph[vertex_1*NUM + vertex_2]=1;
	graph[vertex_2*NUM + vertex_1]=1;
}

void addToSLL(int v)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->n = v;
	new_one->next = 0;
	struct node *cur = head;

	if (head == 0)
	{
		head = new_one;
		return;
	}
	while (cur!=0)
	{
		if (cur->n == new_one->n)
		{
			return;
		}
		cur = cur->next;
	}
	struct node *temp = head;
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_one;
	return;
}

void doDFS(int v)
{
	int vertex = 0;

	push(v); //첫번째 시작 vertex를 stack에 넣기
	while (1)
	{
		vertex = pop();
		if (vertex == -999)
		{
			return;
		}
		visit[vertex] = 1;
		addToSLL(vertex);
		//인접 vertex 찾기
		for (int i = vertex * NUM; i < vertex*NUM+NUM; i++)
		{
			if (graph[i] == 1)
			{
				//edge로 연결된 인접vertex다!
				int adjacency = i - (vertex*NUM); //인접한 vertex 번호
				int stack_ = compareStack(adjacency);
				
				if (visit[adjacency] == 0 && stack_ == 0)
				{
					push(adjacency);
				}
			}
		}

	}
}

void show()
{
	struct node *cur = head;
	while (cur != 0)
	{
		printf("%d -> ", cur->n);
		cur = cur->next;
	}
	printf("\n");
	return;
}

//초기화를 습관화 하기!
int main(void)
{
	//그래프 구성
	graph = (int *)malloc(sizeof(int)*NUM*NUM);
	//배열 초기화
	for (int i = 0; i < NUM*NUM; i++)
	{
		graph[i] = 0;
	}
	//stack 초기화
	stack = (int *)malloc(sizeof(int)*NUM);
	for (int i = 0; i < NUM; i++)
	{
		stack[i] = 0;
	}
	visit = (int *)malloc(sizeof(int)*NUM);
	for (int i = 0; i < NUM; i++)
	{
		visit[i] = 0;
	}

	//우선 vertex끼리 edge 연결
	addToEdge(0, 1);
	addToEdge(0, 3);
	addToEdge(1, 4);
	addToEdge(1, 2);
	addToEdge(2, 3);
	addToEdge(2, 4);

	doDFS(0);
	show();
	return 0;
}