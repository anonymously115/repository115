#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minunit.h"
#include "Adult.h"

int tests_run = 0;
char msg[] = "Error: expected: <18446744073709551615> but was: <18446744073709551616>";

static char* test_constructor() {
	Adult *adult = new_Adult();
	mu_assert("Error: expected: not <null> but was: <null>", adult);
	Customer *customer = (Customer*) adult;
	uint32_t amount = customer->get_amount(customer);
	del_Customer((Customer**) &adult);
	mu_assert("Error: expected: <null> but was: not <null>", !adult);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", 0U, (unsigned) amount);
	mu_assert(msg, amount == 0U);
	return 0;
}

static char* test_amount() {
	uint32_t amount = (uint32_t) rand();
	uint32_t expected = amount;
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->set_amount(customer, amount);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_food_init() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price;
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->take_food(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_food() {
	uint32_t amount = (uint32_t) rand();
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = amount + price;
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->set_amount(customer, amount);
	customer->take_food(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_softdrink_init() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price;
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->take_softdrink(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_softdrink() {
	uint32_t amount = (uint32_t) rand();
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = amount + price;
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->set_amount(customer, amount);
	customer->take_softdrink(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_alcohol_init() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price;
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->take_alcohol(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_alcohol() {
	uint32_t amount = (uint32_t) rand();
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = amount + price;
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->set_amount(customer, amount);
	customer->take_alcohol(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_beer_init() {
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->take_beer(customer);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 500, actual);
	mu_assert(msg, actual == 500);
	return 0;
}

static char* test_take_beer() {
	uint32_t amount = (uint32_t) rand();
	uint32_t expected = amount + 500;
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->set_amount(customer, amount);
	customer->take_beer(customer);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_food_after_alcohol() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price - 200;
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->take_alcohol(customer, 0);
	customer->take_food(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_take_food_after_beer() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price + 300;
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->take_beer(customer);
	customer->take_food(customer, price);
	uint32_t actual = customer->get_amount(customer);
	del_Customer(&customer);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_accounting() {
	size_t before = get_num_of_left();
	Adult *adult = new_Adult();
	Customer *customer = (Customer*) adult;
	customer->accounting(customer);
	del_Customer(&customer);
	size_t after = get_num_of_left();
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", before + 1, after);
	mu_assert(msg, after == before + 1);
	return 0;
}

static char* all_tests() {
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
	mu_run_test(test_take_food_after_alcohol);
	mu_run_test(test_take_food_after_beer);
	mu_run_test(test_accounting);
	return 0;
}

int main(void) {
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
