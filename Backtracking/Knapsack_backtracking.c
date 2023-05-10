#include <stdio.h>
#include <stdbool.h>

int max_profit = 0; //최대 이익
int max_pf_weight = 0;

bool promising(int n, int i, int profit, int weight, int max_weight, int w[], int v[]) {
	int j, k;
	int totweight; // weight + [ i+1 ~ k-1 ]까지 weight의 합
	float bound;   // profit + [ i+1 ~ k-1 ]까지 value의 합 + (max_weight - totweight) * vk/ wk

	if (weight >= max_weight) // Case1) 아이템을 포함한 무게가 최대 무게를 넘을 때
		return false;
	else {                    
		j = i + 1;			  // (level i) + 1
		bound = (float)profit;
		totweight = weight;
		while (j <= n && totweight + w[j] <= max_weight) { // totweight와 bound에 [ i+1 ~ k-1 ] 까지의 각 값을 더하는 과정
			totweight = totweight + w[j];
			bound = bound + v[j];
			j++;
		}
		k = j;
		if (k <= n) // bound + k번째 아이템의 여유 무게 + 아이템의 이익 (vk / wk)
			bound = bound + (max_weight - totweight) * v[k] / w[k];
		// Case2) 남은 아이템을 모두 포함해도 max_profit (best profit)을 넘지 못할 때
		return bound > max_profit; //bound가 max_profit보다 큰지 아닌지 반환
	}
}

void knapsack(int n, int i, int profit, int weight, int max_weight, int w[], int v[]) {
	if (weight <= max_weight && profit > max_profit) {
		max_profit = profit;
		max_pf_weight = weight;
	}

	printf("profit : %d, weight : %d\n", profit, weight); //현재 노드의 profit, weight 출력
	if (promising(n, i, profit, weight, max_weight, w, v)) { //bound가 max_profit보다 크면 아래 노드도 확인
		knapsack(n, i + 1, profit + v[i + 1], weight + w[i + 1], max_weight, w, v); //i+1 번째 포함 (왼쪽 노드)
		knapsack(n, i + 1, profit, weight, max_weight, w, v); //i+1 번째 미포함 (오른쪽 노드)
	}
}

int main() {
	int w[] = { 0, 2, 5, 10, 5 }; //weight 배열
	int v[] = { 0, 40, 30, 50, 10 }; //value 배열
	int max_weight = 16; //최대 무게
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

	knapsack(n, 0, 0, 0, max_weight, w, v);
	printf("max_profit = %d, weight = %d", max_profit, max_pf_weight);
}