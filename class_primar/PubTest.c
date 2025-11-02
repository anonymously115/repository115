#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "minunit.h"
#include "Pub.h"

Pub *pub = NULL;

char msg[] = "Error: expected: <18446744073709551615> but was: <18446744073709551616>";

int tests_run = 0;

static char* test_constructor() {
	mu_assert("Error: expected: not <null> but was: <null>", pub = new_Pub());
	size_t size = sizeof(*pub);
	del_Pub(&pub);
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", sizeof(Pub), size);
	mu_assert(msg, size == sizeof(Pub));
	return 0;
}

static char* test_add_customer() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 19));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "0", 0));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_add_adult() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 20));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "0", 0));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_customer_accounting() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 19));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_customer_take_food() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 19));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "food", 5000));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_customer_take_softdrink() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 19));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "softdrink", 300));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_customer_take_alcohol() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 19));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "alcohol", UINT32_MAX));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_customer_take_beer() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 19));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "0", 0));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_adult_accounting() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 20));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_adult_take_food() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 20));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "food", 5000));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_adult_take_softdrink() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 20));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "softdrink", 300));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_adult_take_alcohol() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 20));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "alcohol", 1000));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_adult_take_beer() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 20));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "0", 0));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_adult_take_alcohol_and_food() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 20));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "alcohol", 0));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "food", 5000));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_adult_take_beer_and_food() {
	pub = new_Pub();
	mu_assert("Error: expected: not <null> but was: <null>", pub->add_customer(pub, 20));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "0", 0));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "food", 5000));
	mu_assert("Error: expected: <true> but was: <false>", pub->order(pub, 0, "A", 0));
	del_Pub(&pub);
	return 0;
}

static char* test_customer_take_invalid() {
	pub = new_Pub();

	mu_assert("Error: expected: <false> but was: <true>", !pub->order(pub, 0, "0", 0));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", ERANGE, errno);
	mu_assert(msg, errno == ERANGE);

	pub->add_customer(pub, 0);
	mu_assert("Error: expected: <false> but was: <true>", !pub->order(pub, 0, NULL, 0));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);

	mu_assert("Error: expected: <false> but was: <true>", !pub->order(pub, 0, "", 0));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);

	del_Pub(&pub);
	return 0;
}

static char* all_tests() {
	mu_run_test(test_constructor);
	del_Pub(&pub);
	mu_run_test(test_add_customer);
	del_Pub(&pub);
	mu_run_test(test_add_adult);
	del_Pub(&pub);
	mu_run_test(test_customer_accounting);
	del_Pub(&pub);
	mu_run_test(test_customer_take_food);
	del_Pub(&pub);
	mu_run_test(test_customer_take_softdrink);
	del_Pub(&pub);
	mu_run_test(test_customer_take_alcohol);
	del_Pub(&pub);
	mu_run_test(test_customer_take_beer);
	del_Pub(&pub);
	mu_run_test(test_adult_accounting);
	del_Pub(&pub);
	mu_run_test(test_adult_take_food);
	del_Pub(&pub);
	mu_run_test(test_adult_take_softdrink);
	del_Pub(&pub);
	mu_run_test(test_adult_take_alcohol);
	del_Pub(&pub);
	mu_run_test(test_adult_take_beer);
	del_Pub(&pub);
	mu_run_test(test_adult_take_alcohol_and_food);
	del_Pub(&pub);
	mu_run_test(test_adult_take_beer_and_food);
	del_Pub(&pub);
	mu_run_test(test_customer_take_invalid);
	del_Pub(&pub);
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
	free(pub);
	return result != 0;
}
