#include <stdio.h>
#include <stdbool.h>

int max_profit = 0; //�ִ� ����
int max_pf_weight = 0;

bool promising(int n, int i, int profit, int weight, int max_weight, int w[], int v[]) {
	int j, k;
	int totweight; // weight + [ i+1 ~ k-1 ]���� weight�� ��
	float bound;   // profit + [ i+1 ~ k-1 ]���� value�� �� + (max_weight - totweight) * vk/ wk

	if (weight >= max_weight) // Case1) �������� ������ ���԰� �ִ� ���Ը� ���� ��
		return false;
	else {                    
		j = i + 1;			  // (level i) + 1
		bound = (float)profit;
		totweight = weight;
		while (j <= n && totweight + w[j] <= max_weight) { // totweight�� bound�� [ i+1 ~ k-1 ] ������ �� ���� ���ϴ� ����
			totweight = totweight + w[j];
			bound = bound + v[j];
			j++;
		}
		k = j;
		if (k <= n) // bound + k��° �������� ���� ���� + �������� ���� (vk / wk)
			bound = bound + (max_weight - totweight) * v[k] / w[k];
		// Case2) ���� �������� ��� �����ص� max_profit (best profit)�� ���� ���� ��
		return bound > max_profit; //bound�� max_profit���� ū�� �ƴ��� ��ȯ
	}
}

void knapsack(int n, int i, int profit, int weight, int max_weight, int w[], int v[]) {
	if (weight <= max_weight && profit > max_profit) {
		max_profit = profit;
		max_pf_weight = weight;
	}

	printf("profit : %d, weight : %d\n", profit, weight); //���� ����� profit, weight ���
	if (promising(n, i, profit, weight, max_weight, w, v)) { //bound�� max_profit���� ũ�� �Ʒ� ��嵵 Ȯ��
		knapsack(n, i + 1, profit + v[i + 1], weight + w[i + 1], max_weight, w, v); //i+1 ��° ���� (���� ���)
		knapsack(n, i + 1, profit, weight, max_weight, w, v); //i+1 ��° ������ (������ ���)
	}
}

int main() {
	int w[] = { 0, 2, 5, 10, 5 }; //weight �迭
	int v[] = { 0, 40, 30, 50, 10 }; //value �迭
	int max_weight = 16; //�ִ� ����
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

	knapsack(n, 0, 0, 0, max_weight, w, v);
	printf("max_profit = %d, weight = %d", max_profit, max_pf_weight);
}