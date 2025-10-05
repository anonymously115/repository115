#ifndef NDEBUG
#include <stdio.h>
#include "minunit.h"
#include "Adult.h"

int tests_run = 0;
char message[64];

static char* test_customer() {
	Customer* customer = new_customer();
	customer->take_softdrink(customer, 300);
	customer->take_food(customer, 400);
	customer->take_beer(customer);
	customer->take_softdrink(customer, 600);
	customer->take_food(customer, 700);
	customer->accounting(customer);
	int expected = 2000;
	int actual = customer->amount;
	sprintf(message, "Error: expected: <%d> but was: <%d>\n", expected, actual);
	mu_assert(message, actual == expected);
	return 0;
}

static char* test_adult() {
	Customer* adult = (Customer*)new_adult();
	adult->take_softdrink(adult, 300);
	adult->take_food(adult, 400);
	adult->take_beer(adult);
	adult->take_softdrink(adult, 600);
	adult->take_food(adult, 700);
	adult->accounting(adult);
	int expected = 2300;
	int actual = adult->amount;
	sprintf(message, "Error: expected: <%d> but was: <%d>\n", expected, actual);
	mu_assert(message, actual == expected);
	return 0;
}

static char* test_num_of_left() {
	int expected = 2;
	int actual = get_num_of_left();
	sprintf(message, "Error: expected: <%d> but was: <%d>\n", expected, actual);
	mu_assert(message, actual == expected);
	return 0;
}

static char* all_tests() {
	mu_run_test(test_customer);
	mu_run_test(test_adult);
	mu_run_test(test_num_of_left);
	return 0;
}

int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;
	char *result = all_tests();
	if (result) {
		printf("%s\n", result);
	} else {
		printf("ALL TESTS PASSED\n");
	}
	(void)get_num_of_left();
	printf("Tests run: %d\n", tests_run);
	return result != 0;
}
#endif
