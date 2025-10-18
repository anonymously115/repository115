#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#define SOURCE "main"
#define IN_FILE "in.txt"
#define OUT_FILE "out.txt"
#define ERR_FILE "err.txt"
#define try(expression) \
	do { \
		if (!(expression)) { \
			perror(strerror(errno)); \
			exit(errno); \
		} \
	} while (0)

char result[1 << 10][1 << 4];

typedef struct {
	size_t n;
	char *s;
	unsigned m;
} Order;

size_t test(size_t n, size_t k, unsigned A[n], Order o[k]) {
	static unsigned i = 0;
	FILE *file = NULL;
	try(file = fopen(IN_FILE, "w"));
	fprintf(file, "%zu %zu\n", n, k);
	for (size_t i = 0; i < n; i++) fprintf(file, "%u\n", A[i]);
	for (size_t i = 0; i < k; i++) {
		if (o[i].m) fprintf(file, "%zu %s %u\n", o[i].n, o[i].s, o[i].m);
		else fprintf(file, "%zu %s\n", o[i].n, o[i].s);
	}
	try(!fclose(file));
	clock_t clockt = clock();
	try(!(errno = system(".\\" SOURCE " <" IN_FILE " 1>" OUT_FILE " 2>" ERR_FILE)));
	fprintf(stderr, "#%d %f sec\n", ++i, (float) (clock() - clockt) / CLOCKS_PER_SEC);
	fflush(stderr);
	try(file = fopen(OUT_FILE, "r"));
	size_t m = 0;
	for (; fgets(result[m], sizeof(result[m]), file); m++);
	try(!fclose(file));
	return m;
}

void test0() {
	unsigned A[] = { };
	Order orders[] = { };
	assert(test(sizeof(A) / sizeof(A[0]), sizeof(orders) / sizeof(orders[0]), A, orders) == 1);
	assert(!strcmp(result[0], "0\n"));
}

void test1() {
	unsigned A[] = { 20 };
	Order orders[] = { { 1, "0", 0 }, { 1, "A", 0 } };
	assert(test(sizeof(A) / sizeof(A[0]), sizeof(orders) / sizeof(orders[0]), A, orders) == 2);
	assert(!strcmp(result[0], "500\n"));
	assert(!strcmp(result[1], "1\n"));
}

void all_tests() {
	test0();
	test1();
}

int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;
	try(!system("gcc -Wall -Wextra -std=c99 -DNDEBUG " SOURCE ".c Pub.c Adult.c Customer.c -o " SOURCE " 1>" SOURCE ".txt 2>&1"));
	all_tests();
	try(!remove(OUT_FILE));
	try(!remove(IN_FILE));
	return errno;
}
