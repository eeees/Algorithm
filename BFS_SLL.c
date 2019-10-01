#include<stdio.h>
#include<stdlib.h>

#define num 5

struct node {
	int v;
	struct node *next;
};

int visited[num] = { 0 };
struct node *graph[num];

int rear = 0;
int front = 0;
int queue[num];

void enqueue(int v)
{
	if ((rear + 1) % num == front)
	{
		return;
	}
	queue[rear] = v;
	rear = (rear + 1) % num;
	return;
}

int dequeue()
{
	if (rear == front)
	{
		return -999;
	}
	int temp = queue[front];
	front = (front + 1) % num;
	return temp;
}

int isQueueEmpty()
{
	if (rear == front)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void addToEdge(int v1, int v2, int reverse)
{
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
	if (reverse == 0)
	{
		addToEdge(v2, v1, 1);
	}
	return;
}

int findNext(int v)
{
	struct node *cur = graph[v];
	while (cur != 0)
	{
		if (visited[cur->v] == 0)
		{
			return cur->v;
		}
		else
		{
			cur = cur->next;
		}
	}
	return -1;
}

void doBFS(int v)
{
	printf("visited is %d\n", v);
	visited[v] = 1;
	enqueue(v);

	while (isQueueEmpty() == 0)
	{
		int next_v = 0;
		next_v = findNext(queue[front]);

		if (next_v == -1)
		{
			dequeue();
		}
		else
		{
			printf("visited is %d\n", next_v);
			visited[next_v] = 1;
			enqueue(next_v);
		}
	}
	return;
}

int main(void)
{
	addToEdge(0, 1, 1);
	addToEdge(0, 2, 1);
	addToEdge(0, 4, 1);
	addToEdge(1, 2, 1);
	addToEdge(2, 3, 1);
	addToEdge(2, 4, 1);
	addToEdge(3, 4, 1);

	doBFS(0);
}