//��Ÿ�ӿ�������;;;;

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int VERTEX_NUM;

int* graph = 0;
int* queue = 0;
int front = 0;
int rear = 0;
int* visited = 0;

/*
 Queue full �̸� �ܼ��� return
*/
void enqueue(int v)
{
	if ((rear + 1) % VERTEX_NUM == front)
	{
		return;
	}
	queue[rear] = v;
	rear = (rear + 1) % VERTEX_NUM;
	return;
}

/*
 Empty queue�̸� -999�� return
*/
int dequeue()
{
	/* �� ���� ä�� �����ÿ� */
	if (rear == front)
	{
		return -999;
	}
	int res = queue[front];
	front = (front + 1) % VERTEX_NUM;
	return res;
}

void addEdge(int v1, int v2)
{
	graph[v1 * VERTEX_NUM + v2] = 1;
	graph[v2 * VERTEX_NUM + v1] = 1;
}

/*
 queue�� vertex v�� ������, 1
 ������ 0�� ��ȯ
*/

int isInQueue(int v)
{
	for (int i = 0; i < VERTEX_NUM; i++)
	{
		if (queue[i] == v)
		{
			return 1;
		}
	}
	return 0;
}


/*
  v���� �����ؼ�,,, DFS
*/
int doBFS(int v,int x, int y)
{
	int cur_vertex;
	int f;
	// 1. v�� stack�� �ִ´�.
	enqueue(v);

	// queue�� ������� �ʴ� ��...
	while (1)
	{
		cur_vertex = dequeue();

		if (cur_vertex == -999)
		{
			return -1;
		}

		// 1. queue���� ������ visited
		visited[cur_vertex] = 1;
		//���⼭ y�� �湮�ߴ����� ��
		if (cur_vertex == x)
		{
			if (visited[y] == 0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		//addToSLL(cur_vertex);

		//------------------------------
		// ������ʹ� �����ص� �˴ϴ�.


		// 2. ģ������ ã�Ƽ� queue�� enqueue
		//
		for (int i = cur_vertex * VERTEX_NUM; i < cur_vertex*VERTEX_NUM + VERTEX_NUM; i++)
		{
			if (graph[i] == 1)
			{
				//�����ߴ�.
				int ad = i - (cur_vertex*VERTEX_NUM);
				if (visited[ad] == 0 && isInQueue(ad) == 0)
				{
					enqueue(ad);
				}
			}
		}
		// �� ������ �����Ͻÿ�.
		//
	}
}




int main(void)
{
	int v1, v2;
	int i;
	scanf("%d", &VERTEX_NUM);

	// �׷��� ����
	graph = (int*)malloc(sizeof(int) * VERTEX_NUM * VERTEX_NUM);
	// �ʱ�ȭ
	for (i = 0; i < VERTEX_NUM * VERTEX_NUM; i++)
	{
		graph[i] = 0;
	}

	while (1)
	{
		scanf("%d %d", &v1, &v2);
		if ((v1 == -1) && (v2 == -1))
		{
			break;
		}
		addEdge(v1, v2);
	}
	int x, y = 0;
	scanf("%d %d", &x, &y);

	// Queue ����
	queue = (int*)malloc(sizeof(int) * VERTEX_NUM);
	for (i = 0; i < VERTEX_NUM; i++)
	{
		queue[i] = 0;
	}
	visited = (int*)malloc(sizeof(int) * VERTEX_NUM);
	for (i = 0; i < VERTEX_NUM; i++)
	{
		visited[i] = 0;
	}

	// BFS ����

	printf("%d\n", doBFS(0, x, y));
	return 0;
}
