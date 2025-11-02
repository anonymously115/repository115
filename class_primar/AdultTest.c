#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "Adult.h"

char msg[] = "Error: expected: <18446744073709551615> but was: <18446744073709551616>";

int tests_run = 0;

static char* test_constructor() {
	Adult *adult = new_Adult();
	mu_assert("Error: expected: not <null> but was: <null>", adult);
	del_Customer((Customer**) &adult);
	return 0;
}

static char* test_amount(uint32_t value, uint32_t expected) {
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->set_amount(customer, value);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_food(uint32_t value, bool drunk, uint32_t expected) {
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	if (drunk) customer->take_alcohol(customer, 0);
	customer->take_food(customer, value);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_softdrink(uint32_t value, uint32_t expected) {
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->take_softdrink(customer, value);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_alcohol(uint32_t value, uint32_t expected) {
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->take_alcohol(customer, value);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_beer() {
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->take_beer(customer);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 500, actual);
	mu_assert(msg, actual == 500);
	return 0;
}

static char* test_amount_0() {
	return test_amount(0, 0);
}

static char* test_take_food_0() {
	return test_take_food(5000, false, 5000);
}

static char* test_take_softdrink_0() {
	return test_take_softdrink(300, 300);
}

static char* test_take_alcohol_0() {
	return test_take_alcohol(500, 500);
}

static char* test_take_food_1() {
	return test_take_food(300, true, 100);
}

static char* all_tests() {
	mu_run_test(test_constructor);
	mu_run_test(test_amount_0);
	mu_run_test(test_take_food_0);
	mu_run_test(test_take_softdrink_0);
	mu_run_test(test_take_alcohol_0);
	mu_run_test(test_take_food_1);
	mu_run_test(test_take_beer);
	return 0;
}

int main(void) {
	char *result = all_tests();
	if (result != 0) {
		fprintf(stderr, "%s\n", result);
		fprintf(stderr, "Tests run: %d\n", tests_run);
	} else {
		fprintf(stdout, "ALL TESTS PASSED\n");
		fprintf(stdout, "Tests run: %d\n", tests_run);
	}
	return result != 0;
}
