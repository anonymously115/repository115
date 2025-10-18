#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "Pub.h"

struct __Pub{
	size_t n;
	Customer **customers;
};

static void Pub_order(Pub *pub, size_t n, const char *s, unsigned m) {
	Customer *customer = pub->_pub->customers[n];
	if (!strcmp(s, "0")) {
		customer->take_beer(customer);
	} else if (!strcmp(s, "A")) {
		customer->accounting(customer);
	} else if (!strcmp(s, "food")) {
		customer->take_food(customer, m);
	} else if (!strcmp(s, "softdrink")) {
		customer->take_softdrink(customer, m);
	} else if (!strcmp(s, "alcohol")) {
		customer->take_alcohol(customer, m);
	}
}

void Pub_query(Pub *pub, const char *str) {
	char tmp[-~strlen(str)];
	strcpy(tmp, str);
	size_t n;
	sscanf(strtok(tmp, " "), "%zu", &n);
	char s[] = "softdrink";
	strcpy(s, strtok(NULL, " "));
	unsigned m = 0;
	char *t = strtok(NULL, " ");
	if (t) {
		sscanf(t, "%u", &m);
	}
	Pub_order(pub, n - 1, s, m);
}

void pub_init(Pub *pub, size_t n, const uint8_t *A) {
	pub->_pub = (_Pub) malloc(sizeof(struct __Pub));
	pub->_pub->n = n;
	pub->_pub->customers = (Customer**) calloc(n, sizeof(Customer*));
	for (size_t i = 0; i < n; i++) {
		if (A[i] < 20) pub->_pub->customers[i] = new_customer();
		else pub->_pub->customers[i] = (Customer*) new_adult();
	}
	pub->query = Pub_query;
}

Pub* new_pub(size_t n, const uint8_t *A) {
	Pub *pub = (Pub*) malloc(sizeof(Pub));
	pub_init(pub, n, A);
	return pub;
}

void del_pub(Pub** pub) {
	size_t *n = &((*pub)->_pub->n);
	while (*n) {
		del_customer(&((*pub)->_pub->customers[--(*n)]));
	}
	free((*pub)->_pub->customers);
	free(*pub);
	*pub = NULL;
}
