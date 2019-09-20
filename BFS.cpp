#include<stdio.h>
#include<stdlib.h>
//vertex�� ������ 4�� ��
//vertex�� 0���� 3��� ����
#define NUM 4

int *graph = 0; //1���� �迭��
/*0~4���� vertex 0
5~9���� vertex 1....
*/
int *queue= 0;
int front = 0;
int rear = 0;
int *visit = 0;

struct node {
	int n;
	struct node *next;
};

struct node *head = 0;

//!!!!!queue�� �ִ��� �񱳷� �ٲپ���Ѵ�.
int compareStack(int ad)
{
	//stack�ȿ� �ִ��� ��
	for (int i = 0; i < NUM-1; i++)
	{
		if (queue[i] == ad) //stack�� �����Ѵ�!
		{
			return 1;
		}
	}
	return 0;
}

void enqueue(int v)
{
	if ((rear + 1) % NUM == front)
	{
		return;
	}
	queue[rear] = v;
	rear = (rear + 1) % NUM;
	return;
}

int dequeue()
{
	int res;
	if (front == rear)
	{
		return -999;
	}
	res = queue[front];
	front=(front + 1) % NUM;
	return res;
}

void addToEdge(int vertex_1, int vertex_2)
{
	//�迭�̹Ƿ� 1�� �־��ָ��!
	graph[vertex_1*NUM + vertex_2] = 1;
	graph[vertex_2*NUM + vertex_1] = 1;
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
	while (cur != 0)
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

void doBFS(int v)
{
	int vertex = 0;

	enqueue(v); //ù��° ���� vertex�� stack�� �ֱ�
	while (1)
	{
		vertex = dequeue();
		if (vertex == -999)
		{
			return;
		}
		visit[vertex] = 1;
		addToSLL(vertex);
		//���� vertex ã��
		for (int i = vertex * NUM; i < vertex*NUM + NUM; i++)
		{
			if (graph[i] == 1)
			{
				//edge�� ����� ����vertex��!
				int adjacency = i - (vertex*NUM); //������ vertex ��ȣ
				int stack_ = compareStack(adjacency);

				if (visit[adjacency] == 0 && stack_ == 0)
				{
					enqueue(adjacency);
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

//�ʱ�ȭ�� ����ȭ �ϱ�!
int main(void)
{
	//�׷��� ����
	graph = (int *)malloc(sizeof(int)*NUM*NUM);
	//�迭 �ʱ�ȭ
	for (int i = 0; i < NUM*NUM; i++)
	{
		graph[i] = 0;
	}
	//stack �ʱ�ȭ
	queue = (int *)malloc(sizeof(int)*NUM);
	for (int i = 0; i < NUM; i++)
	{
		queue[i] = 0;
	}
	
	visit = (int *)malloc(sizeof(int)*NUM);
	for (int i = 0; i < NUM; i++)
	{
		visit[i] = 0;
	}

	//�켱 vertex���� edge ����
	addToEdge(0, 1);
	addToEdge(0, 2);
	addToEdge(0, 3);
	addToEdge(1, 2);
	addToEdge(2, 3);

	doBFS(0);
	show();
	return 0;
}