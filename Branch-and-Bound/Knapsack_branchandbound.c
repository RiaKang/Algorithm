#include <stdio.h>
#include <stdlib.h>
#define Q_SIZE 10

typedef struct { //node 구조체 ( level, profit, weight )
	int level;
	int profit;
	int weight;
} node;

typedef struct { //node 구조체를 사용한 queue
	node queue[Q_SIZE];
	int front, rear;
} QueueType;

QueueType* createQueue(); //queue를 사용하는 함수 선호출
int isQueueEmpty(QueueType* Q);
int isQueueFull(QueueType* Q);
void enQueue(QueueType* Q, node item);
node deQueue(QueueType* Q);

float bound(int n, node u, int max_weight, int v[], int w[]) { //backtracking에서 사용했던 bound에서 result 반환, node를 사용으로 교체
	int j, k;
	int totweight; // weight + [ i+1 ~ k-1 ]까지 weight의 합
	float result;   // profit + [ i+1 ~ k-1 ]까지 value의 합 + (max_weight - totweight) * vk/ wk

	if (u.weight >= max_weight) // Case1) 아이템을 포함한 무게가 최대 무게를 넘을 때
		return 0;
	else {                    // Case2) 남은 모든 아이템을 포함해도 best profit을 넘지 못할 때
		j = u.level + 1;			  // (level i) + 1
		result = u.profit;
		totweight = u.weight;
		while (j <= n && totweight + w[j] <= max_weight) { // totweight와 bound에 [ i+1 ~ k-1 ] 까지의 각 값을 더하는 과정
			totweight = totweight + w[j];
			result = result + v[j];
			j++;
		}
		k = j;
		if (k <= n) // k번째 아이템의 여무 무게 + 아이템의 이익 (vk / wk)
			result = result + (max_weight - totweight) * v[k] / w[k];
		return result;
	}
}

void knapsack_breadth(int n, int max_weight, const int v[], const int w[]) {
	QueueType* Q = createQueue();
	node u, u_child;

	u.level = 0; u.profit = 0; u.weight = 0; // 초기화 과정
	int max_profit = 0;
	int max_pf_weight = 0;

	printf("profit : %d , weight : %d\n", u.profit, u.weight);
	enQueue(Q, u); // 초기화된 u를 root로
	while (!isQueueEmpty(Q)) {
		u = deQueue(Q);

		u_child.level = u.level + 1; //u_child는 u의 자식(아래) 노드

		//u_child를 u의 왼쪽 자식 노드로 (다음 item을 포함하는 노드)
		u_child.weight = u.weight + w[u_child.level];
		u_child.profit = u.profit + v[u_child.level];

		if (u_child.weight <= max_weight && u_child.profit > max_profit) {
			max_profit = u_child.profit;
			max_pf_weight = u_child.weight;
		}
		if (bound(n, u_child, max_weight, v, w) > max_profit) { // 왼쪽 자식 노드의 bound가 max_profit보다 크면
			enQueue(Q, u_child); // queue에 삽입
		}
		printf("profit : %d , weight : %d\n", u_child.profit, u_child.weight);

		// u_child를 u의 오른쪽 자식 노드로 (다음 item을 포함하지 않는 노드)
		u_child.weight = u.weight;
		u_child.profit = u.profit;
		if (bound(n, u_child, max_weight, v, w) > max_profit) { // 오른쪽 자식 노드의 bound가 max_profit보다 크면
			enQueue(Q, u_child); // queue에 삽입
		}
		printf("profit : %d , weight : %d\n", u_child.profit, u_child.weight);
	}
	printf("max_profit = %d, max_pf_weight = %d\n", max_profit, max_pf_weight);
}

int main() {
	int w[] = { 0, 1, 3, 2, 2 }; //weight 배열
	int v[] = { 0, 1, 2, 3, 4 }; //value 배열
	int max_weight = 5; //최대 무게
	int n = 4; //item 갯수

	printf("weight [ "); //가시성을 위한 출력
	for (int i = 0; i <= n; i++) {
		printf("%d ", w[i]);
	}
	printf("]\n");

	printf("value  [ "); //가시성을 위한 출력
	for (int i = 0; i <= n; i++) {
		printf("%d ", v[i]);
	}
	printf("]\n\n");

	knapsack_breadth(n, max_weight, v, w);
}

QueueType* createQueue() {
	QueueType* Q;
	Q = (QueueType*)malloc(sizeof(QueueType));
	Q->front = -1;    // front 초깃값 설정
	Q->rear = -1;    // rear 초깃값 설정
	return Q;
}

// 순차 큐가 공백 상태인지 검사하는 연산
int isQueueEmpty(QueueType* Q) {
	if (Q->front == Q->rear) {
		return 1;
	}
	else return 0;
}

// 순차 큐가 포화 상태인지 검사하는 연산
int isQueueFull(QueueType* Q) {
	if (Q->rear == Q_SIZE - 1) {
		return 1;
	}
	else return 0;
}

// 순차 큐의 rear에 원소를 삽입하는 연산
void enQueue(QueueType* Q, node item) {
	if (isQueueFull(Q)) return;  // 포화 상태이면, 삽입 연산 중단
	else {
		Q->rear++;
		Q->queue[Q->rear] = item;
	}
}

// 순차 큐의 front에서 원소를 삭제하는 연산
node deQueue(QueueType* Q) {
	if (isQueueEmpty(Q)) return;  // 공백 상태이면, 삭제 연산 중단
	else {
		Q->front++;
		return Q->queue[Q->front];
	}
}