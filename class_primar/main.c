#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Adult.h"

int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;
#ifdef NDEBUG
	size_t N, k;
	scanf("%zu %zu", &N, &k);
	Customer *customers[N];
	for (size_t i = 0; i < N; i++) {
		unsigned a;
		scanf("%u", &a);
		if (a < 20) customers[i] = new_customer();
		else customers[i] = (Customer*) new_adult();
	}
	while (k--) {
		size_t n;
		char s[10];
		scanf("%zu %s", &n, s);
		n -= 1;
		if (!strcmp(s, "0")) {
			customers[n]->take_beer(customers[n]);
		} else if (!strcmp(s, "A")) {
			customers[n]->accounting(customers[n]);
			printf("%u\n", customers[n]->amount);
		} else {
			int m;
			scanf("%d", &m);
			if (!strcmp(s, "food")) customers[n]->take_food(customers[n], m);
			else if (!strcmp(s, "softdrink")) customers[n]->take_softdrink(customers[n], m);
			else if (!strcmp(s, "alcohol")) customers[n]->take_alcohol(customers[n], m);
		}
	}
	printf("%zu\n", get_num_of_left());
#else
	size_t N = 2;
	Customer *customers[N];
	customers[0] = new_customer();
	customers[1] = (Customer*) new_adult();
	customers[0]->take_softdrink(customers[0], 300);
	customers[0]->take_food(customers[0], 400);
	customers[0]->take_beer(customers[0]);
	customers[0]->take_softdrink(customers[0], 600);
	customers[0]->take_food(customers[0], 700);
	customers[0]->accounting(customers[0]);
	customers[1]->take_softdrink(customers[1], 300);
	customers[1]->take_food(customers[1], 400);
	customers[1]->take_beer(customers[1]);
	customers[1]->take_softdrink(customers[1], 600);
	customers[1]->take_food(customers[1], 700);
	customers[1]->accounting(customers[1]);
	assert(customers[0]->amount == 2000);
	assert(customers[1]->amount == 2300);
	assert(get_num_of_left() == 2);
#endif
	while (N) {
		free(customers[--N]);
		customers[N] = NULL;
	}
	return 0;
}
