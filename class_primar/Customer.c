#include <stdlib.h>
#include "Customer.h"

static size_t num_of_left = 0;

static void Customer_take_food(Customer *self, unsigned price) {
	self->amount += price;
}

static void Customer_take_softdrink(Customer *self, unsigned price) {
	self->amount += price;
}

static void Customer_take_alcohol(Customer *self, unsigned price) {
	(void) self;
	(void) price;
}

static void Customer_take_beer(Customer *self) {
	self->take_alcohol(self, 500);
}

static void Customer_accounting(Customer *self) {
	(void) self;
	num_of_left++;
}

void customer_init(Customer *self) {
	self->amount = 0;
	self->take_food = Customer_take_food;
	self->take_softdrink = Customer_take_softdrink;
	self->take_alcohol = Customer_take_alcohol;
	self->take_beer = Customer_take_beer;
	self->accounting = Customer_accounting;
}

Customer* new_customer() {
	Customer *customer = (Customer*) malloc(sizeof(Customer));
	customer_init(customer);
	return customer;
}

size_t get_num_of_left() {
	return num_of_left;
}
