#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "minunit.h"
#include "Pub.h"

int tests_run = 0;
char msg[] = "Error: expected: <18446744073709551615> but was: <18446744073709551616>";

static char* test_constructor() {
	Pub *pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub);
	size_t size = sizeof(*pub);
	del_Pub(&pub);
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", sizeof(Pub), size);
	mu_assert(msg, size == sizeof(Pub));
	return 0;
}

static char* test_add_customer() {
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 19);
	customer->take_beer(customer);
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	mu_assert("Error: expected: not <null> but was: <null>", customer);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", 0U, (unsigned) actual);
	mu_assert(msg, actual == 0U);
	return 0;
}

static char* test_add_adult() {
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 20);
	customer->take_beer(customer);
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	mu_assert("Error: expected: not <null> but was: <null>", customer);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", 500U, (unsigned) actual);
	mu_assert(msg, actual == 500U);
	return 0;
}

static char* test_customer_take_food() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price;
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 19);
	bool result = pub->order(pub, 0, "food", price);
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	mu_assert("Error: expected: <true> but was: <false>", result);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", (unsigned) expected, (unsigned) actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_adult_take_food() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price;
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 20);
	bool result = pub->order(pub, 0, "food", price);
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	mu_assert("Error: expected: <true> but was: <false>", result);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", (unsigned) expected, (unsigned) actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_customer_take_softdrink() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price;
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 19);
	bool result = pub->order(pub, 0, "softdrink", price);
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	mu_assert("Error: expected: <true> but was: <false>", result);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", (unsigned) expected, (unsigned) actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_adult_take_softdrink() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price;
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 20);
	bool result = pub->order(pub, 0, "softdrink", price);
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	mu_assert("Error: expected: <true> but was: <false>", result);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", (unsigned) expected, (unsigned) actual);
	mu_assert(msg, actual == expected);
	return 0;
}


static char* test_customer_take_alcohol() {
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 19);
	bool result = pub->order(pub, 0, "alcohol", (uint32_t) (300 + rand() % 4701));
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	mu_assert("Error: expected: <true> but was: <false>", result);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", 0U, (unsigned) actual);
	mu_assert(msg, actual == 0U);
	return 0;
}

static char* test_adult_take_alcohol() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price;
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 20);
	bool result = pub->order(pub, 0, "alcohol", price);
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	mu_assert("Error: expected: <true> but was: <false>", result);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", (unsigned) expected, (unsigned) actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_customer_take_beer() {
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 19);
	bool result = pub->order(pub, 0, "0", (uint32_t) (300 + rand() % 4701));
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	mu_assert("Error: expected: <true> but was: <false>", result);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", 0U, (unsigned) actual);
	mu_assert(msg, actual == 0U);
	return 0;
}

static char* test_adult_take_beer() {
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 20);
	bool result = pub->order(pub, 0, "0", (uint32_t) (300 + rand() % 4701));
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	mu_assert("Error: expected: <true> but was: <false>", result);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", 500U, (unsigned) actual);
	mu_assert(msg, actual == 500U);
	return 0;
}

static char* test_adult_take_alcohol_and_food() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price - 200;
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 20);
	pub->order(pub, 0, "alcohol", 0);
	pub->order(pub, 0, "food", price);
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", (unsigned) expected, (unsigned) actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_adult_take_beer_and_food() {
	uint32_t price = (uint32_t) (300 + rand() % 4701);
	uint32_t expected = price + 300;
	Pub *pub = new_Pub();
	Customer *customer = pub->add_customer(pub, 20);
	pub->order(pub, 0, "0", 0);
	pub->order(pub, 0, "food", price);
	uint32_t actual = customer->get_amount(customer);
	del_Pub(&pub);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", (unsigned) expected, (unsigned) actual);
	mu_assert(msg, actual == expected);
	return 0;
}

static char* test_customer_accounting() {
	size_t before = get_num_of_left();
	Pub *pub = new_Pub();
	pub->add_customer(pub, 19);
	bool result = pub->order(pub, 0, "A", (uint32_t) (300 + rand() % 4701));
	del_Pub(&pub);
	size_t after = get_num_of_left();
	mu_assert("Error: expected: <true> but was: <false>", result);
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", before + 1, after);
	mu_assert(msg, after == before + 1);
	return 0;
}

static char* test_adult_accounting() {
	size_t before = get_num_of_left();
	Pub *pub = new_Pub();
	pub->add_customer(pub, 20);
	bool result = pub->order(pub, 0, "A", (uint32_t) (300 + rand() % 4701));
	del_Pub(&pub);
	size_t after = get_num_of_left();
	mu_assert("Error: expected: <true> but was: <false>", result);
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", before + 1, after);
	mu_assert(msg, after == before + 1);
	return 0;
}

static char* test_customer_out_of_range() {
	Pub *pub = new_Pub();
	bool result = pub->order(pub, 0, "0", 0);
	del_Pub(&pub);
	mu_assert("Error: expected: <false> but was: <true>", !result);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", ERANGE, errno);
	mu_assert(msg, errno == ERANGE);
	return 0;
}

static char* test_customer_null() {
	Pub *pub = new_Pub();
	pub->add_customer(pub, 0);
	bool result = pub->order(pub, 0, NULL, 0);
	del_Pub(&pub);
	mu_assert("Error: expected: <false> but was: <true>", !result);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);
	return 0;
}

static char* test_customer_empty() {
	Pub *pub = new_Pub();
	pub->add_customer(pub, 0);
	bool result = pub->order(pub, 0, "", 0);
	del_Pub(&pub);
	mu_assert("Error: expected: <false> but was: <true>", !result);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);
	return 0;
}

static char* test_customer_invalid() {
	Pub *pub = new_Pub();
	pub->add_customer(pub, 0);
	pub->order(pub, 0, "a", 0);
	del_Pub(&pub);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);
	return 0;
}

static char* all_tests() {
	mu_run_test(test_constructor);
	mu_run_test(test_add_customer);
	mu_run_test(test_add_adult);
	mu_run_test(test_customer_take_food);
	mu_run_test(test_adult_take_food);
	mu_run_test(test_customer_take_softdrink);
	mu_run_test(test_adult_take_softdrink);
	mu_run_test(test_customer_take_alcohol);
	mu_run_test(test_adult_take_alcohol);
	mu_run_test(test_customer_take_beer);
	mu_run_test(test_adult_take_beer);
	mu_run_test(test_adult_take_alcohol_and_food);
	mu_run_test(test_adult_take_beer_and_food);
	mu_run_test(test_customer_accounting);
	mu_run_test(test_adult_accounting);
	mu_run_test(test_customer_out_of_range);
	mu_run_test(test_customer_null);
	mu_run_test(test_customer_empty);
	mu_run_test(test_customer_invalid);
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
