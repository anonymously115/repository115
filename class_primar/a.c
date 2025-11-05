#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
	int N, k;
	scanf("%d %d", &N, &k);
	int A[N];
	int sum[N];
	bool B[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		sum[i] = 0;
		B[i] = 0;
	}
	int C = 0;
	while (k--) {
		int n;
		char s[] = "softdrink";
		scanf("%d %s", &n, s);
		n -= 1;
		if (!strcmp(s, "A")) {
			printf("%d\n", sum[n]);
			C++;
		} else if (!strcmp(s, "0")) {
			if (A[n] >= 20) {
				sum[n] += 500;
				B[n] = true;
			}
		} else {
			int m;
			scanf("%d", &m);
			if (!strcmp(s, "food")) {
				if (B[n]) {
					sum[n] += (m - 200);
				} else {
					sum[n] += m;
				}
			} else if (!strcmp(s, "softdrink")) {
				sum[n] += m;
			} else if (!strcmp(s, "alcohol")) {
				if (A[n] >= 20) {
					sum[n] += m;
					B[n] = true;
				}
			}
		}
	}
	printf("%d\n", C);
	return 0;
}
