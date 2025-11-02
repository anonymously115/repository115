#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Pub.h"
#include "Adult.h"

struct __Pub {
	size_t size;
	Customer **customers;
};

static bool Pub_add_customer(Pub *self, uint8_t age) {
	errno = 0;
	size_t n = self->_pub->size;
	self->_pub->customers = (Customer**) realloc(self->_pub->customers, sizeof(Customer*) * (n + 1));
	self->_pub->customers[n] = (age < 20) ? new_Customer() : (Customer*) new_Adult();
	if (self->_pub->customers[n] == NULL) return false;
	self->_pub->size += 1;
	return true;
}

static bool Pub_order(Pub *self, size_t n, const char* s, uint32_t m) {
	errno = 0;
	if (n >= self->_pub->size) {
		errno = ERANGE;
		return false;
	} else if (!s) {
		errno = EINVAL;
		return false;
	}
	Customer *customer = self->_pub->customers[n];
	if (!strcmp(s, "food")) {
		customer->take_food(customer, m);
	} else if (!strcmp(s, "softdrink")) {
		customer->take_softdrink(customer, m);
	} else if (!strcmp(s, "alcohol")) {
		customer->take_alcohol(customer, m);
	} else if (!strcmp(s, "0")) {
		customer->take_beer(customer);
	} else if (!strcmp(s, "A")) {
		customer->accounting(customer);
	} else {
		errno = EINVAL;
		return false;
	}
	return true;
}

bool Pub_init(Pub *pub) {
	if (!(pub->_pub = (_Pub*) malloc(sizeof(_Pub)))) {
		return false;
	}
	pub->_pub->size = 0;
	if (!(pub->_pub->customers = (Customer**) malloc(sizeof(Customer*)))) {
		free(pub->_pub);
		return false;
	}
	pub->add_customer = Pub_add_customer;
	pub->order = Pub_order;
	return true;
}

Pub* new_Pub() {
	Pub *pub = NULL;
	if (!(pub = (Pub*) malloc(sizeof(Pub)))) return NULL;
	if (!Pub_init(pub)) {
		del_Pub(&pub);
		return NULL;
	}
	return pub;
}

void del_Pub(Pub **pub) {
	if (*pub == NULL) return;
	size_t *n = &((*pub)->_pub->size);
	while (*n) {
		*n -= 1;
		del_Customer(&((*pub)->_pub->customers[*n]));
	}
	free((*pub)->_pub->customers);
	free((*pub)->_pub);
	free(*pub);
	*pub = NULL;
}
