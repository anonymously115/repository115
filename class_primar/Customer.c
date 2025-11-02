#include <stdio.h>
#include <stdlib.h>
#include "Customer.h"

static size_t num_of_left = 0;

struct __Customer {
	uint32_t amount;
};

static void Customer_set_amount(Customer *self, uint32_t value) {
	self->_customer->amount = value;
}

static uint32_t Customer_get_amount(Customer *self) {
	return self->_customer->amount;
}

static void Customer_take_food(Customer *self, uint32_t price) {
	self->set_amount(self, self->get_amount(self) + price);
}

static void Customer_take_softdrink(Customer *self, uint32_t price) {
	self->set_amount(self, self->get_amount(self) + price);
}

static void Customer_take_alcohol(Customer *self, uint32_t price) {
	(void) self;
	(void) price;
}

static void Customer_take_beer(Customer *self) {
	self->take_alcohol(self, 500);
}

static void Customer_accounting(Customer *self) {
	printf("%d\n", self->get_amount(self));
	num_of_left++;
}

bool Customer_init(Customer *customer) {
	if (!(customer->_customer = (_Customer*) malloc(sizeof(_Customer)))) return false;
	customer->_customer->amount = 0;
	customer->set_amount = Customer_set_amount;
	customer->get_amount = Customer_get_amount;
	customer->take_food = Customer_take_food;
	customer->take_softdrink = Customer_take_softdrink;
	customer->take_alcohol = Customer_take_alcohol;
	customer->take_beer = Customer_take_beer;
	customer->accounting = Customer_accounting;
	return true;
}

Customer* new_Customer() {
	Customer *customer = NULL;
	if (!(customer = (Customer*) malloc(sizeof(Customer)))) return NULL;
	if (!Customer_init(customer)) {
		del_Customer(&customer);
		return NULL;
	}
	return customer;
}

size_t get_num_of_left() {
	return num_of_left;
}

void del_Customer(Customer **customer) {
	if (*customer == NULL) return;
	free((*customer)->_customer);
	free(*customer);
	*customer = NULL;
}
