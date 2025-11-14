#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "Pub.h"
#include "Adult.h"

const uint8_t ADULT_AGE = 20;

struct __Pub {
	size_t size;
	Customer **customers;
};

static Customer* Pub_add_customer(Pub *self, uint8_t age) {
	errno = 0;
	size_t n = self->_pub->size;
	Customer** tmp = (Customer**) realloc(self->_pub->customers, sizeof(Customer*) * (n + 1));
	if (!tmp) {
		while (n--) {
			free(self->_pub->customers[n]);
			self->_pub->customers[n] = NULL;
		}
		self->_pub->size = 0;
		free(self->_pub->customers);
		self->_pub->customers = NULL;
		return NULL;
	}
	self->_pub->customers = tmp;
	self->_pub->customers[n] = (age < ADULT_AGE) ? new_Customer() : (Customer*) new_Adult();
	if (self->_pub->customers[n] == NULL) return NULL;
	self->_pub->size += 1;
	return self->_pub->customers[n];
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

Pub* new_Pub(void) {
	Pub *pub = NULL;
	if (!(pub = (Pub*) malloc(sizeof(Pub)))) return NULL;
	if (!(pub->_pub = (_Pub*) malloc(sizeof(_Pub)))) {
		del_Pub(&pub);
		return NULL;
	}
	pub->_pub->size = 0;
	if (!(pub->_pub->customers = (Customer**) malloc(sizeof(Customer*)))) {
		del_Pub(&pub);
		return NULL;
	}
	pub->add_customer = Pub_add_customer;
	pub->order = Pub_order;
	return pub;
}

void del_Pub(Pub **pub) {
	if (*pub) {
		if ((*pub)->_pub) {
			size_t *n = &((*pub)->_pub->size);
			if ((*pub)->_pub->customers) {
				while (*n) {
					*n -= 1;
					del_Customer(&((*pub)->_pub->customers[*n]));
				}
				free((*pub)->_pub->customers);
				(*pub)->_pub->customers = NULL;
			} else {
				*n = 0;
			}
			free((*pub)->_pub);
			(*pub)->_pub = NULL;
		}
		free(*pub);
		*pub = NULL;
	}
}
