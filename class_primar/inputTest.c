#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "minunit.h"
#include "input.h"

char msg[] = "Error: expected: <18446744073709551615> but was: <18446744073709551616>";
size_t n;
uint16_t k;
uint8_t a;
char s[] = "softdrink";
uint32_t m;

int tests_run = 0;

static char* test_read_num(const char *str, size_t exn, uint16_t exk) {
	mu_assert("Error: expected: <true> but was: <false>", read_numbers(str, &n, &k));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 0, errno);
	mu_assert(msg, errno == 0);
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", exn, n);
	mu_assert(msg, n == exn);
	sprintf(msg, "Error: expected: <%hu> but was: <%hu>", exk, k);
	mu_assert(msg, k == exk);
	return 0;
}

static char* test_read_num_null() {
	mu_assert("Error: expected: <false> but was: <true>", !read_numbers(NULL, &n, &k));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);
	return 0;
}

static char* test_read_num_invalid(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_numbers(str, &n, &k));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);
	return 0;
}

static char* test_read_num_out_of_range(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_numbers(str, &n, &k));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", ERANGE, errno);
	mu_assert(msg, errno == ERANGE);
	return 0;
}

static char* test_read_num_0() {return test_read_num_null();}
static char* test_read_num_1() {return test_read_num_invalid("");}
static char* test_read_num_2() {return test_read_num_invalid("a 1");}
static char* test_read_num_3() {return test_read_num_invalid("1");}
static char* test_read_num_4() {return test_read_num_invalid("1 a");}
static char* test_read_num_5() {return test_read_num_invalid("1 1 1");}
static char* test_read_num_6() {return test_read_num("1 1", 1, 1);}
static char* test_read_num_7() {return test_read_num("1000 1000", 1000, 1000);}
static char* test_read_num_8() {return test_read_num_out_of_range("0 1");}
static char* test_read_num_9() {return test_read_num_out_of_range("1001 1");}
static char* test_read_num_10() {return test_read_num_out_of_range("1 0");}
static char* test_read_num_11() {return test_read_num_out_of_range("1 1001");}

static char* test_read_age(const char *str, uint8_t exa) {
	mu_assert("Error: expected: <true> but was: <false>", read_age(str, &a));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 0, errno);
	mu_assert(msg, errno == 0);
	sprintf(msg, "Error: expected: <%d> but was: <%d>", exa, a);
	mu_assert(msg, a == exa);
	return 0;
}

static char* test_read_age_null() {
	mu_assert("Error: expected: <false> but was: <true>", !read_age(NULL, &a));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);
	return 0;
}

static char* test_read_age_invalid(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_age(str, &a));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);
	return 0;
}

static char* test_read_age_out_of_range(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_age(str, &a));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", ERANGE, errno);
	mu_assert(msg, errno == ERANGE);
	return 0;
}

static char* test_read_age_0() {return test_read_age_null();}
static char* test_read_age_1() {return test_read_age_invalid("");}
static char* test_read_age_2() {return test_read_age_invalid("a");}
static char* test_read_age_3() {return test_read_age_invalid("1 1");}
static char* test_read_age_4() {return test_read_age("1", 1);}
static char* test_read_age_5() {return test_read_age("100", 100);}
static char* test_read_age_6() {return test_read_age_out_of_range("0");}
static char* test_read_age_7() {return test_read_age_out_of_range("101");}

static char* test_read_query_3_args(const char *str, size_t exn, const char* exs, uint32_t exm) {
	mu_assert("Error: expected: <true> but was: <false>", read_query(str, &n, s, &m));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 0, errno);
	mu_assert(msg, errno == 0);
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", exn, n);
	mu_assert(msg, n == exn);
	sprintf(msg, "Error: expected: <%s> but was: <%s>", exs, s);
	mu_assert(msg, !strcmp(s, exs));
	sprintf(msg, "Error: expected: <%u> but was: <%u>", exm, m);
	mu_assert(msg, m == exm);
	return 0;
}

static char* test_read_query_2_args(const char *str, size_t exn, const char* exs) {
	mu_assert("Error: expected: <true> but was: <false>", read_query(str, &n, s, &m));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 0, errno);
	mu_assert(msg, errno == 0);
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", exn, n);
	mu_assert(msg, n == exn);
	sprintf(msg, "Error: expected: <%s> but was: <%s>", exs, s);
	mu_assert(msg, !strcmp(s, exs));
	return 0;
}

static char* test_read_query_null() {
	mu_assert("Error: expected: <false> but was: <true>", !read_query(NULL, &n, s, &m));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);
	return 0;
}

static char* test_read_query_invalid(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_query(str, &n, s, &m));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", EINVAL, errno);
	mu_assert(msg, errno == EINVAL);
	return 0;
}

static char* test_read_query_out_of_range(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_query(str, &n, s, &m));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", ERANGE, errno);
	mu_assert(msg, errno == ERANGE);
	return 0;
}

static char* test_read_query() {
	size_t n = (size_t) (1 + rand() % 1000);
	uint32_t m = (uint32_t) (300 + rand() % 4701);
	char line[] = "1000 softdrink 5000";
	sprintf(line, "%zu food %u", n, (unsigned) m);
	return test_read_query_3_args(line, n, "food", m);
}

static char* test_read_query_0() {return test_read_query_null();}
static char* test_read_query_1() {return test_read_query_invalid("");}
static char* test_read_query_2() {return test_read_query_invalid("a food 300");}
static char* test_read_query_3() {return test_read_query_invalid("1");}
static char* test_read_query_4() {return test_read_query_invalid("1 a 300");}
static char* test_read_query_5() {return test_read_query_invalid("1 food");}
static char* test_read_query_6() {return test_read_query_invalid("1 softdrink");}
static char* test_read_query_7() {return test_read_query_invalid("1 alcohol");}
static char* test_read_query_8() {return test_read_query_invalid("1 food a");}
static char* test_read_query_9() {return test_read_query_invalid("1 softdrink a");}
static char* test_read_query_10() {return test_read_query_invalid("1 beer a");}
static char* test_read_query_11() {return test_read_query_invalid("1 0 500");}
static char* test_read_query_12() {return test_read_query_invalid("1 A 500");}
static char* test_read_query_13() {return test_read_query_invalid("1 food 300 0");}
static char* test_read_query_14() {return test_read_query_3_args("1 food 300", 1, "food", 300);}
static char* test_read_query_15() {return test_read_query_3_args("1 softdrink 300", 1, "softdrink", 300);}
static char* test_read_query_16() {return test_read_query_3_args("1000 alcohol 5000", 1000, "alcohol", 5000);}
static char* test_read_query_17() {return test_read_query_2_args("1 0", 1, "0");}
static char* test_read_query_18() {return test_read_query_2_args("1000 A", 1000, "A");}
static char* test_read_query_19() {return test_read_query_out_of_range("0 0");}
static char* test_read_query_20() {return test_read_query_out_of_range("1001 A");}
static char* test_read_query_21() {return test_read_query_out_of_range("1 food 299");}
static char* test_read_query_22() {return test_read_query_out_of_range("1 softdrink 299");}
static char* test_read_query_23() {return test_read_query_out_of_range("1000 alcohol 5001");}

static char* all_tests() {
	mu_run_test(test_read_num_0);
	mu_run_test(test_read_num_1);
	mu_run_test(test_read_num_2);
	mu_run_test(test_read_num_3);
	mu_run_test(test_read_num_4);
	mu_run_test(test_read_num_5);
	mu_run_test(test_read_num_6);
	mu_run_test(test_read_num_7);
	mu_run_test(test_read_num_8);
	mu_run_test(test_read_num_9);
	mu_run_test(test_read_num_10);
	mu_run_test(test_read_num_11);
	mu_run_test(test_read_age_0);
	mu_run_test(test_read_age_1);
	mu_run_test(test_read_age_2);
	mu_run_test(test_read_age_3);
	mu_run_test(test_read_age_4);
	mu_run_test(test_read_age_5);
	mu_run_test(test_read_age_6);
	mu_run_test(test_read_age_7);
	mu_run_test(test_read_query);
	mu_run_test(test_read_query_0);
	mu_run_test(test_read_query_1);
	mu_run_test(test_read_query_2);
	mu_run_test(test_read_query_3);
	mu_run_test(test_read_query_4);
	mu_run_test(test_read_query_5);
	mu_run_test(test_read_query_6);
	mu_run_test(test_read_query_7);
	mu_run_test(test_read_query_8);
	mu_run_test(test_read_query_9);
	mu_run_test(test_read_query_10);
	mu_run_test(test_read_query_11);
	mu_run_test(test_read_query_12);
	mu_run_test(test_read_query_13);
	mu_run_test(test_read_query_14);
	mu_run_test(test_read_query_15);
	mu_run_test(test_read_query_16);
	mu_run_test(test_read_query_17);
	mu_run_test(test_read_query_18);
	mu_run_test(test_read_query_19);
	mu_run_test(test_read_query_20);
	mu_run_test(test_read_query_21);
	mu_run_test(test_read_query_22);
	mu_run_test(test_read_query_23);
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
