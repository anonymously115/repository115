#include <stdio.h>
#include "minunit.h"
#include "Customer.h"

char msg[] = "Error: expected: <18446744073709551615> but was: <18446744073709551616>";

int tests_run = 0;

static char* test_constructor() {
	Customer *customer = new_Customer();
	mu_assert("Error: expected: not <null> but was: <null>", customer);
	size_t size = sizeof(*customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", sizeof(Customer), size);
	mu_assert(msg, size == sizeof(Customer));
	return 0;
}

static char* test_amount(uint32_t value, uint32_t expected) {
	Customer *customer = new_Customer();
	customer->set_amount(customer, value);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_food(uint32_t value, uint32_t expected) {
	Customer *customer = new_Customer();
	customer->take_food(customer, value);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_softdrink(uint32_t value, uint32_t expected) {
	Customer *customer = new_Customer();
	customer->take_softdrink(customer, value);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_alcohol(uint32_t value, uint32_t expected) {
	Customer *customer = new_Customer();
	customer->take_alcohol(customer, value);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_beer() {
	Customer *customer = new_Customer();
	customer->take_beer(customer);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 0, actual);
	mu_assert(msg, actual == 0);
	return 0;
}

static char* test_amount_0() {
	return test_amount(0, 0);
}

static char* test_take_food_0() {
	return test_take_food(5000, 5000);
}

static char* test_take_softdrink_0() {
	return test_take_softdrink(300, 300);
}

static char* test_take_alcohol_0() {
	return test_take_alcohol(500, 0);
}

static char* all_tests() {
	mu_run_test(test_constructor);
	mu_run_test(test_amount_0);
	mu_run_test(test_take_food_0);
	mu_run_test(test_take_softdrink_0);
	mu_run_test(test_take_alcohol_0);
	mu_run_test(test_take_beer);
	return 0;
}

int main() {
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
