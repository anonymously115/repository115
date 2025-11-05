#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "minunit.h"
#include "input.h"

int tests_run = 0;
char msg[] = "Error: expected: <18446744073709551615> but was: <18446744073709551616>";
size_t n;
uint16_t k;
uint8_t a;
char s[] = "softdrink";
uint32_t m;

static char* message_hhu(uint8_t expected, uint8_t actual) {
	sprintf(msg, "Error: expected: <%hhu> but was: <%hhu>", expected, actual);
	return msg;
}

static char* message_d(int expected, int actual) {
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, actual);
	return msg;
}

static char* message_u(uint32_t expected, uint32_t actual) {
	sprintf(msg, "Error: expected: <%u> but was: <%u>", expected, actual);
	return msg;
}

static char* message_zu(size_t expected, size_t actual) {
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", expected, actual);
	return msg;
}

static char* message_s(const char *expected, const char *actual) {
	sprintf(msg, "Error: expected: <%s> but was: <%s>", expected, actual);
	return msg;
}

static char* test_read_num(const char *str, size_t en, uint16_t ek) {
	mu_assert("Error: expected: <true> but was: <false>", read_numbers(str, &n, &k));
	mu_assert(message_d(errno, 0), errno == 0);
	mu_assert(message_zu(en, n), n == en);
	mu_assert(message_u(ek, k), k == ek);
	return 0;
}

static char* test_read_num_null() {
	mu_assert("Error: expected: <false> but was: <true>", !read_numbers(NULL, &n, &k));
	mu_assert(message_d(EINVAL, errno), errno == EINVAL);
	return 0;
}

static char* test_read_num_invalid(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_numbers(str, &n, &k));
	mu_assert(message_d(EINVAL, errno), errno == EINVAL);
	return 0;
}

static char* test_read_num_out_of_range(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_numbers(str, &n, &k));
	mu_assert(message_d(ERANGE, errno), errno == ERANGE);
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

static char* test_read_age(const char *str, uint8_t ea) {
	mu_assert("Error: expected: <true> but was: <false>", read_age(str, &a));
	mu_assert(message_d(0, errno), errno == 0);
	mu_assert(message_hhu(ea, a), a == ea);
	return 0;
}

static char* test_read_age_null() {
	mu_assert("Error: expected: <false> but was: <true>", !read_age(NULL, &a));
	mu_assert(message_d(EINVAL, errno), errno == EINVAL);
	return 0;
}

static char* test_read_age_invalid(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_age(str, &a));
	mu_assert(message_d(EINVAL, errno), errno == EINVAL);
	return 0;
}

static char* test_read_age_out_of_range(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_age(str, &a));
	mu_assert(message_d(ERANGE, errno), errno == ERANGE);
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

static char* test_read_query_3_args(const char *str, size_t en, const char* es, uint32_t em) {
	mu_assert("Error: expected: <true> but was: <false>", read_query(str, &n, s, &m));
	mu_assert(message_d(0, errno), errno == 0);
	mu_assert(message_zu(en, n), n == en);
	mu_assert(message_s(es, s), !strcmp(s, es));
	mu_assert(message_u(em, m), m == em);
	return 0;
}

static char* test_read_query_2_args(const char *str, size_t en, const char* es) {
	mu_assert("Error: expected: <true> but was: <false>", read_query(str, &n, s, &m));
	mu_assert(message_d(0, errno), errno == 0);
	mu_assert(message_zu(en, n), n == en);
	mu_assert(message_s(es, s), !strcmp(s, es));
	return 0;
}

static char* test_read_query_null() {
	mu_assert("Error: expected: <false> but was: <true>", !read_query(NULL, &n, s, &m));
	mu_assert(message_d(EINVAL, errno), errno == EINVAL);
	return 0;
}

static char* test_read_query_invalid(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_query(str, &n, s, &m));
	mu_assert(message_d(EINVAL, errno), errno == EINVAL);
	return 0;
}

static char* test_read_query_out_of_range(const char *str) {
	mu_assert("Error: expected: <false> but was: <true>", !read_query(str, &n, s, &m));
	mu_assert(message_d(ERANGE, errno), errno == ERANGE);
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
