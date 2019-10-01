#include<stdio.h>
#include<stdlib.h>

int num;
int *queue = 0;
int *graph = 0;
int *visited = 0;
int rear = 0;
int front = 0;
int cnt = 0;

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

void addToEdge(int v1, int v2)
{
	graph[v1*num + v2] = 1;
	graph[v2*num + v1] = 1;
	return;
}

int isQueue(int v)
{
	for (int i = 0; i < num; i++)
	{
		if (queue[i] == v)
		{
			return 1;
		}
	}
	return 0;
}

void doBFS(int v,int r)
{
	int vertex = 0;
	enqueue(v);
	while (1)
	{
		vertex = dequeue();
		if (vertex == -999)
		{
			return;
		} 

		visited[vertex] = 1;
		cnt++;
		//printf("cnt Áõ°¡");
		if (cnt == num )
		{
			if (vertex == r)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
		for (int i = num * vertex; i < num*vertex + num; i++)
		{
			if (graph[i] == 1)
			{
				int ad = i - (num*vertex);
				if (visited[ad] == 0&& isQueue(ad) == 0)
				{
					enqueue(ad);
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d", &num);
	graph = (int *)malloc(sizeof(int)*num*num);
	for (int i = 0; i < num*num; i++)
	{
		graph[i] = 0;
	}
	visited = (int *)malloc(sizeof(int)*num);
	for (int i = 0; i < num; i++)
	{
		visited[i] = 0;
	}
	queue= (int *)malloc(sizeof(int)*num);
	for (int i = 0; i < num; i++)
	{
		queue[i] = 0;
	}

	int v1, v2 = 0;
	while (1)
	{
		scanf("%d %d", &v1, &v2);
		if (v1 == -1 && v2 == -1)
		{
			break;
		}
		else
		{
			addToEdge(v1, v2);
		}
	}
	int s, r = 0;
	scanf("%d %d", &s, &r);
	doBFS(s,r);

	return 0;
}