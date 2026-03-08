#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include "minunit.h"
#define SOURCE "main"
#define IN_FILE "in.txt"
#define OUT_FILE "out.txt"
#define ERR_FILE "err.txt"

int tests_run = 0;
char result[1][128];

static char* message_zu(size_t expected, size_t actual) {
	static char msg[72];
	snprintf(msg, sizeof(msg), "Error: expected: <%zu> but was: <%zu>", expected, actual);
	return msg;
}

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

static size_t test(size_t n, const char *lines[]) {
	FILE *file;
	if (!(file = fopen(IN_FILE, "w"))) {
		perror(NULL);
		exit(errno);
	}
	for (size_t i = 0; i < n; i++) {
		fputs(lines[i], file);
		fputc('\n', file);
	}
	fclose(file);
	clock_t clockt = clock();
	if (!!(errno = system(".\\" SOURCE " <" IN_FILE " 1>" OUT_FILE " 2>" ERR_FILE))) {
		perror(NULL);
		exit(errno);
	}
	fprintf(stderr, "#%d %f sec\n", tests_run, (float) (clock() - clockt) / CLOCKS_PER_SEC);
	fflush(stderr);
	if (!(file = fopen(OUT_FILE, "r"))) {
		perror(NULL);
		exit(errno);
	}
	size_t m = 0;
	while (fgets(result[m], sizeof(result[m]), file)) m++;
	fclose(file);
	return m;
}

static int test_err(size_t n, const char *lines[]) {
	FILE *file;
	if (!(file = fopen(IN_FILE, "w"))) {
		perror(NULL);
		exit(errno);
	}
	for (size_t i = 0; i < n; i++) {
		fputs(lines[i], file);
		fputc('\n', file);
	}
	fclose(file);
	clock_t clockt = clock();
	int e = system(".\\" SOURCE " <" IN_FILE " 1>" OUT_FILE " 2>" ERR_FILE);
	fprintf(stderr, "#%d %f sec\n", tests_run, (float) (clock() - clockt) / CLOCKS_PER_SEC);
	fflush(stderr);
	return e;
}

static char* test0() {
	int e = test_err(0, NULL);
	mu_assert(message_d(EXIT_FAILURE, e), e == EXIT_FAILURE);
	return 0;
}

static char* test1() {
	char s[64] = { };
	size_t i = 0;
	for (char c = '0'; c <= '9'; c++)
		s[i++] = c;
	for (char c = 'A'; c <= 'Z'; c++)
		s[i++] = c;
	for (char c = 'a'; c <= 'z'; c++)
		s[i++] = c;
	char t[64] = { };
	strcpy(t, s);
	strcat(t, "\n");
	const char *lines[] = { s };
	size_t n = test(sizeof(lines) / sizeof(lines[0]), lines);
	mu_assert(message_zu(1, n), n == 1);
	mu_assert(message_s(t, result[0]), !strcmp(result[0], t));
	return 0;
}

static char* test2() {
	char s[4][128] = { };
	size_t i = 0;
	for (char c = 0x20; c < 0x7F; c++)
		s[1][i++] = c;
	memset(s[2], '0', 101);
	memset(s[3], '0', 100);
	const char *lines[] = { s[0], s[1], s[2], s[3] };
	char t[128] = { };
	memset(t, '0', 100);
	t[100] = '\n';
	size_t n = test(sizeof(lines) / sizeof(lines[0]), lines);
	mu_assert(message_zu(1, n), n == 1);
	mu_assert(message_s(t, result[0]), !strcmp(result[0], t));
	return 0;
}

static char* all_tests() {
	mu_run_test(test0);
	mu_run_test(test1);
	mu_run_test(test2);
	return 0;
}

int main() {
	if (!!(errno = system("gcc -Wall -Wextra -Werror -DNDEBUG -std=c99 " SOURCE ".c input.c util.c -o " SOURCE " 1>" SOURCE ".txt 2>&1"))) {
		perror(NULL);
		FILE *file = fopen(SOURCE ".txt", "r");
		if (file) {
			int c = 0;
			while ((c = fgetc(file)) != EOF)
				putchar(c);
			fclose(file);
		}
		exit(errno);
	}
	char *result = all_tests();
	if (result != 0) {
		fprintf(stderr, "%s\n", result);
		fprintf(stderr, "Tests run: %d\n", tests_run);
	} else {
		fprintf(stdout, "ALL TESTS PASSED\n");
		fprintf(stdout, "Tests run: %d\n", tests_run);
	}
	remove(ERR_FILE);
	remove(OUT_FILE);
	remove(IN_FILE);
	remove(SOURCE ".exe");
	remove(SOURCE ".txt");
	if (errno) {
		return errno;
	} else {
		return result != 0;
	}
}
