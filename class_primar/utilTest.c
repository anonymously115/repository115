#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "minunit.h"
#include "util.h"

char msg[] = "Error: expected: <18446744073709551615> but was: <18446744073709551616>";

int tests_run = 0;

static char* test_chomp(const char *str, const char *expected) {
	char s[strlen(str) + 1];
	strcpy(s, str);
	char *actual = chomp(s);
	sprintf(msg, "Error: expected: <%s> but was: <%s>", expected, s);
	mu_assert(msg, !strcmp(s, expected));
	sprintf(msg, "Error: expected: <%s> but was: <%s>", expected, actual);
	mu_assert(msg, !strcmp(actual, expected));
	return 0;
}

static char* test_chomp_0() {
	mu_assert("Error: expected: <null> but was: not <null>", !chomp(NULL));
	return 0;
}

static char* test_chomp_1() {return test_chomp("", "");}
static char* test_chomp_2() {return test_chomp("\n", "");}
static char* test_chomp_3() {return test_chomp("0", "0");}
static char* test_chomp_4() {return test_chomp(" 0", " 0");}

static char* test_parse_ubyte(const char *str, uint8_t expected) {
	uint8_t n = 0;
	mu_assert("Error: expected: <true> but was: <false>", parse_ubyte(str, &n));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 0, errno);
	mu_assert(msg, errno == 0);
	sprintf(msg, "Error: expected: <%hhu> but was: <%hhu>", expected, n);
	mu_assert(msg, n == expected);
	return 0;
}

static char* test_parse_ubyte_fail(const char *str, int expected) {
	uint8_t n = 0;
	mu_assert("Error: expected: <false> but was: <true>", !parse_ubyte(str, &n));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", expected, errno);
	mu_assert(msg, errno == expected);
	return 0;
}

static char* test_parse_ubyte_0() {return test_parse_ubyte_fail(NULL, EINVAL);}
static char* test_parse_ubyte_1() {return test_parse_ubyte_fail("", EINVAL);}
static char* test_parse_ubyte_2() {return test_parse_ubyte("0", 0U);}
static char* test_parse_ubyte_3() {return test_parse_ubyte_fail(" ", EINVAL);}
static char* test_parse_ubyte_4() {return test_parse_ubyte("90", 90U);}
static char* test_parse_ubyte_5() {return test_parse_ubyte_fail("-1", EINVAL);}
static char* test_parse_ubyte_6() {return test_parse_ubyte_fail("1.", EINVAL);}
static char* test_parse_ubyte_7() {return test_parse_ubyte("255", 255U);}
static char* test_parse_ubyte_8() {return test_parse_ubyte_fail("/90", EINVAL);}
static char* test_parse_ubyte_9() {return test_parse_ubyte_fail("9:0", EINVAL);}
static char* test_parse_ubyte_10() {return test_parse_ubyte_fail("90~", EINVAL);}
static char* test_parse_ubyte_11() {return test_parse_ubyte_fail("256", ERANGE);}

static char* test_parse_ushort() {
	uint16_t n = 0;
	mu_assert("Error: expected: <true> but was: <false>", parse_ushort("65535", &n));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 0, errno);
	mu_assert(msg, errno == 0);
	sprintf(msg, "Error: expected: <%hu> but was: <%hu>", 65535U, n);
	mu_assert(msg, n == 65535U);
	return 0;
}

static char* test_parse_ushort_fail() {
	uint16_t n = 0;
	mu_assert("Error: expected: <false> but was: <true>", !parse_ushort("65536", &n));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", ERANGE, errno);
	mu_assert(msg, errno == ERANGE);
	return 0;
}

static char* test_parse_uint() {
	uint32_t n = 0;
	mu_assert("Error: expected: <true> but was: <false>", parse_uint("4294967295", &n));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 0, errno);
	mu_assert(msg, errno == 0);
	sprintf(msg, "Error: expected: <%u> but was: <%u>", 4294967295U, n);
	mu_assert(msg, n == 4294967295U);
	return 0;
}

static char* test_parse_uint_fail() {
	uint32_t n = 0;
	mu_assert("Error: expected: <false> but was: <true>", !parse_uint("4294967296", &n));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", ERANGE, errno);
	mu_assert(msg, errno == ERANGE);
	return 0;
}

static char* test_parse_ulong() {
	size_t n = 0;
	mu_assert("Error: expected: <true> but was: <false>", parse_ulong("18446744073709551615", &n));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", 0, errno);
	mu_assert(msg, errno == 0);
	sprintf(msg, "Error: expected: <%zu> but was: <%zu>", 18446744073709551615ULL, n);
	mu_assert(msg, n == 18446744073709551615ULL);
	return 0;
}

static char* test_parse_ulong_fail() {
	size_t n = 0;
	mu_assert("Error: expected: <false> but was: <true>", !parse_ulong("18446744073709551616", &n));
	sprintf(msg, "Error: expected: <%d> but was: <%d>", ERANGE, errno);
	mu_assert(msg, errno == ERANGE);
	return 0;
}

static char* all_tests() {
	mu_run_test(test_chomp_0);
	mu_run_test(test_chomp_1);
	mu_run_test(test_chomp_2);
	mu_run_test(test_chomp_3);
	mu_run_test(test_chomp_4);
	mu_run_test(test_parse_ubyte_0);
	mu_run_test(test_parse_ubyte_1);
	mu_run_test(test_parse_ubyte_2);
	mu_run_test(test_parse_ubyte_3);
	mu_run_test(test_parse_ubyte_4);
	mu_run_test(test_parse_ubyte_5);
	mu_run_test(test_parse_ubyte_6);
	mu_run_test(test_parse_ubyte_7);
	mu_run_test(test_parse_ubyte_8);
	mu_run_test(test_parse_ubyte_9);
	mu_run_test(test_parse_ubyte_10);
	mu_run_test(test_parse_ubyte_11);
	mu_run_test(test_parse_ushort);
	mu_run_test(test_parse_ushort_fail);
	mu_run_test(test_parse_uint);
	mu_run_test(test_parse_uint_fail);
	mu_run_test(test_parse_ulong);
	mu_run_test(test_parse_ulong_fail);
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
