//SLL DFS

#include<stdio.h>
#include<stdlib.h>

#define num 5

struct node {
	int v;
	struct node *next;
};

/*--------------vertex 방문여부 표시 배열---------------*/
//방문 했다면 1, 방문하지 않았다면 0
int visited[num] = { 0 };
struct node *graph[num];
/*----------------stack--------------*/
int stack[num];
int top = -1;

void push(int v)
{
	if (top == num - 1)
	{
		printf("------stack is full------\n");
	}
	top++;
	stack[top] = v;
}

//return 1은 stack이 비어있는것

int isStackEmpty()
{
	if (top == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int pop()
{
	int temp = 0;
	if (top == -1)
	{
		printf("stack is empty\n");
		return -1;
	}
	temp = stack[top];
	top--;
	return temp;
}


void addEdge(int v1, int v2,int doReverse)
{
	//undirect로
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = v2;
	new_one->next = 0;

	struct node *cur = graph[v1];
	
	if (cur == 0)
	{
		graph[v1] = new_one;
		return;
	}
	else
	{
		while (cur->next != 0)
		{
			cur = cur->next;
		}
		cur->next = new_one;
	}
	if (doReverse == 1)
	{
		addEdge(v2, v1, 0);
	}
	return;
}

void showAdjacentVertex(int v)
{
	struct node *cur = graph[v];

	while (cur != 0)
	{
		printf("%d is the adjacent vertex\n", cur->v);
		cur = cur->next;
	}
}

//v와 연결된 vertex 중, 아직까지 방문하지 않은 vertex를 반환
//만약, 조건만족 vertex가 없으면, -1을 반환
int findNextVertex(int v)
{
	struct node *cur = graph[v];

	while (cur != 0)
	{
		if (visited[cur->v] == 0)//방문하지 않았다.
		{
			return cur->v;
		}
		cur = cur->next;
	}
	return -1; //v에 연결된 vertex 중에 방문하지 않은 것이 없다.
}
void doDFS(int v)
{
	printf("visited %d\n", v);
	visited[v] = 1;
	push(v);

	while (isStackEmpty() == 0)
	{
		int next_vertex = -1;
		next_vertex = findNextVertex(stack[top]); //아직까지 방문하지 않음.

		if (next_vertex == -1)
		{
			pop();
		}
		else
		{
			printf("visited %d\n", next_vertex);
			visited[next_vertex] = 1;
			push(next_vertex);
		}
	}
}


int main(void)
{
	addEdge(0, 1,1);
	addEdge(0, 2,1);
	addEdge(0, 4,1);
	addEdge(1,2,1);
	addEdge(2,3,1);
	addEdge(2, 4,1);
	addEdge(3, 4,1);

	doDFS(0);
}