#include <stdio.h>
#include <stdlib.h>
#include "Customer.h"

static size_t num_of_left = 0;

struct __Customer {
	unsigned amount;
};

static unsigned Customer_get_amount(Customer *self) {
	return self->_customer->amount;
}

static void Customer_set_amount(Customer *self, unsigned amount) {
	self->_customer->amount = amount;
}

static void Customer_take_food(Customer *self, unsigned price) {
	self->_customer->amount += price;
}

static void Customer_take_softdrink(Customer *self, unsigned price) {
	self->_customer->amount += price;
}

static void Customer_take_alcohol(Customer *self, unsigned price) {
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

static void Customer_destructor(Customer* self) {
	free(self->_customer);
	self->_customer = NULL;
}

void customer_init(Customer *self) {
	self->_customer = (_Customer)malloc(sizeof(struct __Customer));
	self->_customer->amount = 0;
	self->get_amount = Customer_get_amount;
	self->set_amount = Customer_set_amount;
	self->take_food = Customer_take_food;
	self->take_softdrink = Customer_take_softdrink;
	self->take_alcohol = Customer_take_alcohol;
	self->take_beer = Customer_take_beer;
	self->accounting = Customer_accounting;
	self->destructor = Customer_destructor;
}

Customer* new_customer() {
	Customer *customer = (Customer*) malloc(sizeof(Customer));
	customer_init(customer);
	return customer;
}

void del_customer(Customer** customer) {
	free((*customer)->_customer);
	free(*customer);
	*customer = NULL;
}

size_t get_num_of_left() {
	return num_of_left;
}
