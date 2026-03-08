#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "minunit.h"
#include "input.h"

int tests_run = 0;

static char* message_s(const char *expected, const char *actual) {
	static char msg[256];
	snprintf(msg, sizeof(msg), "Error: expected: <%s> but was: <%s>", expected, actual);
	return msg;
}

static char* message_d(int expected, int actual) {
	static char msg[72];
	snprintf(msg, sizeof(msg), "Error: expected: <%d> but was: <%d>", expected, actual);
	return msg;
}

static char* test_parse(const char *str, const char *expected) {
	char actual[strlen(str) + 1];
	mu_assert("Error: expected: <true> but was: <false>", parse(str, actual));
	mu_assert(message_s(expected, actual), !strcmp(actual, expected));
	mu_assert(message_d(0, errno), errno == 0);
	return 0;
}

static char* test_parse_invalid(const char *str) {
	char actual[str ? strlen(str) + 1 : 0];
	mu_assert("Error: expected: <false> but was: <true>", !parse(str, actual));
	mu_assert(message_d(EINVAL, errno), errno == EINVAL);
	return 0;
}

static char* test_parse_0() {return test_parse_invalid(NULL);}
static char* test_parse_1() {return test_parse_invalid("");}
static char* test_parse_2() {return test_parse_invalid("\n");}
static char* test_parse_3() {return test_parse("0\n", "0");}
static char* test_parse_4() {return test_parse("9\n", "9");}
static char* test_parse_5() {return test_parse("A\n", "A");}
static char* test_parse_6() {return test_parse("Z\n", "Z");}
static char* test_parse_7() {return test_parse("a\n", "a");}
static char* test_parse_8() {return test_parse("z\n", "z");}

static char* test_parse_9() {
	const char str[] = { '0' - 1, 0x0A, 0x00 };
	return test_parse_invalid(str);
}

static char* test_parse_10() {
	const char str[] = { '9' + 1, 0x0A, 0x00 };
	return test_parse_invalid(str);
}

static char* test_parse_11() {
	const char str[] = { 'A' - 1, 0x0A, 0x00 };
	return test_parse_invalid(str);
}

static char* test_parse_12() {
	const char str[] = { 'Z' + 1, 0x0A, 0x00 };
	return test_parse_invalid(str);
}

static char* test_parse_13() {
	const char str[] = { 'a' - 1, 0x0A, 0x00 };
	return test_parse_invalid(str);
}

static char* test_parse_14() {
	const char str[] = { 'z' + 1, 0x0A, 0x00 };
	return test_parse_invalid(str);
}

static char* test_parse_15() {return test_parse("00\n", "00");}
static char* test_parse_16() {return test_parse_invalid("_0\n");}
static char* test_parse_17() {return test_parse_invalid("0_\n");}
static char* test_parse_18() {return test_parse("000\n", "000");}
static char* test_parse_19() {return test_parse_invalid("_00\n");}
static char* test_parse_20() {return test_parse_invalid("0_0\n");}
static char* test_parse_21() {return test_parse_invalid("00_\n");}

static char* test_parse_22() {
	char str[102] = { };
	memset(str, '0', 100);
	str[100] = '\n';
	char expected[101] = { };
	memset(expected, '0', 100);
	return test_parse(str, expected);
}

static char* test_parse_23() {
	char str[103] = { };
	memset(str, '0', 101);
	str[101] = '\n';
	return test_parse_invalid(str);
}

static char* all_tests() {
	mu_run_test(test_parse_0);
	mu_run_test(test_parse_1);
	mu_run_test(test_parse_2);
	mu_run_test(test_parse_3);
	mu_run_test(test_parse_4);
	mu_run_test(test_parse_5);
	mu_run_test(test_parse_6);
	mu_run_test(test_parse_7);
	mu_run_test(test_parse_8);
	mu_run_test(test_parse_9);
	mu_run_test(test_parse_10);
	mu_run_test(test_parse_11);
	mu_run_test(test_parse_12);
	mu_run_test(test_parse_13);
	mu_run_test(test_parse_14);
	mu_run_test(test_parse_15);
	mu_run_test(test_parse_16);
	mu_run_test(test_parse_17);
	mu_run_test(test_parse_18);
	mu_run_test(test_parse_19);
	mu_run_test(test_parse_20);
	mu_run_test(test_parse_21);
	mu_run_test(test_parse_22);
	mu_run_test(test_parse_23);
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
