#include <stdio.h>
#include <stdlib.h>
#define Q_SIZE 10

typedef struct { //node ����ü ( level, profit, weight )
	int level;
	int profit;
	int weight;
} node;

typedef struct { //node ����ü�� ����� queue
	node queue[Q_SIZE];
	int front, rear;
} QueueType;

QueueType* createQueue(); //queue�� ����ϴ� �Լ� ��ȣ��
int isQueueEmpty(QueueType* Q);
int isQueueFull(QueueType* Q);
void enQueue(QueueType* Q, node item);
node deQueue(QueueType* Q);

float bound(int n, node u, int max_weight, int v[], int w[]) { //backtracking���� ����ߴ� bound���� result ��ȯ, node�� ������� ��ü
	int j, k;
	int totweight; // weight + [ i+1 ~ k-1 ]���� weight�� ��
	float result;   // profit + [ i+1 ~ k-1 ]���� value�� �� + (max_weight - totweight) * vk/ wk

	if (u.weight >= max_weight) // Case1) �������� ������ ���԰� �ִ� ���Ը� ���� ��
		return 0;
	else {                    // Case2) ���� ��� �������� �����ص� best profit�� ���� ���� ��
		j = u.level + 1;			  // (level i) + 1
		result = u.profit;
		totweight = u.weight;
		while (j <= n && totweight + w[j] <= max_weight) { // totweight�� bound�� [ i+1 ~ k-1 ] ������ �� ���� ���ϴ� ����
			totweight = totweight + w[j];
			result = result + v[j];
			j++;
		}
		k = j;
		if (k <= n) // k��° �������� ���� ���� + �������� ���� (vk / wk)
			result = result + (max_weight - totweight) * v[k] / w[k];
		return result;
	}
}

void knapsack_breadth(int n, int max_weight, const int v[], const int w[]) {
	QueueType* Q = createQueue();
	node u, u_child;

	u.level = 0; u.profit = 0; u.weight = 0; // �ʱ�ȭ ����
	int max_profit = 0;
	int max_pf_weight = 0;

	printf("profit : %d , weight : %d\n", u.profit, u.weight);
	enQueue(Q, u); // �ʱ�ȭ�� u�� root��
	while (!isQueueEmpty(Q)) {
		u = deQueue(Q);

		u_child.level = u.level + 1; //u_child�� u�� �ڽ�(�Ʒ�) ���

		//u_child�� u�� ���� �ڽ� ���� (���� item�� �����ϴ� ���)
		u_child.weight = u.weight + w[u_child.level];
		u_child.profit = u.profit + v[u_child.level];

		if (u_child.weight <= max_weight && u_child.profit > max_profit) {
			max_profit = u_child.profit;
			max_pf_weight = u_child.weight;
		}
		if (bound(n, u_child, max_weight, v, w) > max_profit) { // ���� �ڽ� ����� bound�� max_profit���� ũ��
			enQueue(Q, u_child); // queue�� ����
		}
		printf("profit : %d , weight : %d\n", u_child.profit, u_child.weight);

		// u_child�� u�� ������ �ڽ� ���� (���� item�� �������� �ʴ� ���)
		u_child.weight = u.weight;
		u_child.profit = u.profit;
		if (bound(n, u_child, max_weight, v, w) > max_profit) { // ������ �ڽ� ����� bound�� max_profit���� ũ��
			enQueue(Q, u_child); // queue�� ����
		}
		printf("profit : %d , weight : %d\n", u_child.profit, u_child.weight);
	}
	printf("max_profit = %d, max_pf_weight = %d\n", max_profit, max_pf_weight);
}

int main() {
	int w[] = { 0, 1, 3, 2, 2 }; //weight �迭
	int v[] = { 0, 1, 2, 3, 4 }; //value �迭
	int max_weight = 5; //�ִ� ����
	int n = 4; //item ����

	printf("weight [ "); //���ü��� ���� ���
	for (int i = 0; i <= n; i++) {
		printf("%d ", w[i]);
	}
	printf("]\n");

	printf("value  [ "); //���ü��� ���� ���
	for (int i = 0; i <= n; i++) {
		printf("%d ", v[i]);
	}
	printf("]\n\n");

	knapsack_breadth(n, max_weight, v, w);
}

QueueType* createQueue() {
	QueueType* Q;
	Q = (QueueType*)malloc(sizeof(QueueType));
	Q->front = -1;    // front �ʱ갪 ����
	Q->rear = -1;    // rear �ʱ갪 ����
	return Q;
}

// ���� ť�� ���� �������� �˻��ϴ� ����
int isQueueEmpty(QueueType* Q) {
	if (Q->front == Q->rear) {
		return 1;
	}
	else return 0;
}

// ���� ť�� ��ȭ �������� �˻��ϴ� ����
int isQueueFull(QueueType* Q) {
	if (Q->rear == Q_SIZE - 1) {
		return 1;
	}
	else return 0;
}

// ���� ť�� rear�� ���Ҹ� �����ϴ� ����
void enQueue(QueueType* Q, node item) {
	if (isQueueFull(Q)) return;  // ��ȭ �����̸�, ���� ���� �ߴ�
	else {
		Q->rear++;
		Q->queue[Q->rear] = item;
	}
}

// ���� ť�� front���� ���Ҹ� �����ϴ� ����
node deQueue(QueueType* Q) {
	if (isQueueEmpty(Q)) return;  // ���� �����̸�, ���� ���� �ߴ�
	else {
		Q->front++;
		return Q->queue[Q->front];
	}
}