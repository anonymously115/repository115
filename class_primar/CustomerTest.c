#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minunit.h"
#include "Customer.h"

int tests_run = 0;
char msg[] = "Error: expected: <18446744073709551615> but was: <18446744073709551616>";

static char* message_u(uint32_t expected, uint32_t actual) {
	sprintf(msg, "Error: expected: <%u> but was: <%u>", expected, actual);
	return msg;
}

static char* message_zu(size_t expected, size_t actual) {
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", expected, actual);
	return msg;
}

static char* test_num_of_left_init() {
	size_t actual = get_num_of_left();
	mu_assert(message_zu(0ULL, actual), actual == 0ULL);
	return 0;
}

static char* test_constructor() {
	Customer *customer = new_Customer();
	mu_assert("Error: expected: not <null> but was: <null>", customer);
	size_t size = sizeof(*customer);
	uint32_t amount = customer->get_amount(customer);
	del_Customer(&customer);
	mu_assert("Error: expected: <null> but was: not <null>", !customer);
	mu_assert(message_zu(sizeof(Customer), size), size == sizeof(Customer));
	mu_assert(message_u(amount, 0U), amount == 0U);
	return 0;
}

static char* test_amount() {
	uint32_t amount = (uint32_t) rand();
	uint32_t expected = amount;
	Customer *customer = new_Customer();
	customer->set_amount(customer, amount);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	mu_assert(message_u(expected, actual), actual == expected);
	return 0;
}

static char* test_take_food_init() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price;
	Customer *customer = new_Customer();
	customer->take_food(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	mu_assert(message_u(expected, actual), actual == expected);
	return 0;
}

static char* test_take_food() {
	uint32_t amount = (uint32_t) rand();
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = amount + price;
	Customer *customer = new_Customer();
	customer->set_amount(customer, amount);
	customer->take_food(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	mu_assert(message_u(expected, actual), actual == expected);
	return 0;
}

static char* test_take_softdrink_init() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price;
	Customer *customer = new_Customer();
	customer->take_softdrink(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	mu_assert(message_u(expected, actual), actual == expected);
	return 0;
}

static char* test_take_softdrink() {
	uint32_t amount = (uint32_t) rand();
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = amount + price;
	Customer *customer = new_Customer();
	customer->set_amount(customer, amount);
	customer->take_softdrink(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	mu_assert(message_u(expected, actual), actual == expected);
	return 0;
}

static char* test_take_alcohol_init() {
	Customer *customer = new_Customer();
	customer->take_alcohol(customer, (uint32_t) (300 + rand() % 4701));
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	mu_assert(message_u(0U, actual), actual == 0U);
	return 0;
}

static char* test_take_alcohol() {
	uint32_t amount = (uint32_t) rand();
	uint32_t expected = amount;
	Customer *customer = new_Customer();
	customer->set_amount(customer, amount);
	customer->take_alcohol(customer, (uint32_t) (300 + rand() % 4701));
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	mu_assert(message_u(expected, actual), actual == expected);
	return 0;
}

static char* test_take_beer_init() {
	Customer *customer = new_Customer();
	customer->take_beer(customer);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	mu_assert(message_u(0U, actual), actual == 0U);
	return 0;
}

static char* test_take_beer() {
	uint32_t amount = (uint32_t) rand();
	uint32_t expected = amount;
	Customer *customer = new_Customer();
	customer->set_amount(customer, amount);
	customer->take_beer(customer);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	mu_assert(message_u(expected, actual), actual == expected);
	return 0;
}

static char* test_accounting() {
	size_t before = get_num_of_left();
	Customer *customer = new_Customer();
	customer->accounting(customer);
	del_Customer(&customer);
	size_t after = get_num_of_left();
	mu_assert(message_zu(before + 1, after), after == before + 1);
	return 0;
}

static char* test_num_of_left() {
	size_t actual = get_num_of_left();
	mu_assert(message_zu(1ULL, actual), actual == 1ULL);
	return 0;
}

static char* all_tests() {
	mu_run_test(test_num_of_left_init);
	mu_run_test(test_constructor);
	mu_run_test(test_amount);
	mu_run_test(test_take_food_init);
	mu_run_test(test_take_food);
	mu_run_test(test_take_softdrink_init);
	mu_run_test(test_take_softdrink);
	mu_run_test(test_take_alcohol_init);
	mu_run_test(test_take_alcohol);
	mu_run_test(test_take_beer_init);
	mu_run_test(test_take_beer);
	mu_run_test(test_accounting);
	mu_run_test(test_num_of_left);
	return 0;
}

int main() {
	srand((unsigned) time(NULL));
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
