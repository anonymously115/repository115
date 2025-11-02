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

char result[1001][9];

size_t test(size_t n, const char *lines[])
{
	static unsigned k = 0;
	FILE *file;
	if (!(file = fopen(IN_FILE, "w")))
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(errno);
	}
	for (size_t i = 0; i < n; i++)
	{
		fputs(lines[i], file);
		fputc('\n', file);
	}
	fclose(file);
	clock_t start = clock();
	if (!!(errno = system(".\\" SOURCE " <" IN_FILE " 1>" OUT_FILE " 2>" ERR_FILE)))
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(errno);
	}
	fprintf(stderr, "#%u %f sec\n", ++k, (float)(clock() - start) / CLOCKS_PER_SEC);
	fflush(stderr);
	if (!(file = fopen(OUT_FILE, "r")))
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(errno);
	}
	size_t m = 0;
	while (fgets(result[m], sizeof(result[m]), file)) m++;
	fclose(file);
	return m;
}

void test0()
{
#if 0
	const char *lines[] = {"0 0"};
#else
	const char *lines[] = {"1 1", "1", "1 0"};
#endif
	assert(test(sizeof(lines) / sizeof(lines[0]), lines) == 1);
	assert(!strcmp(result[0], "0\n"));
}

void test1()
{
	const char *lines[] = {
		"3 21",
		"19",
		"20",
		"20",
		"1 softdrink 300",
		"1 food 340",
		"1 alcohol 380",
		"1 softdrink 420",
		"1 food 460",
		"1 0",
		"1 softdrink 540",
		"1 food 580",
		"1 A",
		"2 softdrink 1000",
		"2 food 2000",
		"2 alcohol 3000",
		"2 softdrink 4000",
		"2 food 5000",
		"2 A",
		"3 softdrink 300",
		"3 food 400",
		"3 0",
		"3 softdrink 600",
		"3 food 700",
		"3 A",
	};
	assert(test(sizeof(lines) / sizeof(lines[0]), lines) == 4);
	assert(!strcmp(result[0], "2640\n"));
	assert(!strcmp(result[1], "14800\n"));
	assert(!strcmp(result[2], "2300\n"));
	assert(!strcmp(result[3], "3\n"));
}

void all_tests()
{
	test0();
	test1();
}

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	if (system("gcc -Wall -Wextra -Werror -std=c99 " SOURCE ".c input.c util.c Pub.c Adult.c Customer.c -o " SOURCE " 1>" SOURCE ".txt 2>&1"))
	{
		perror(NULL);
		exit(errno);
	}
	all_tests();
	remove(OUT_FILE);
	remove(IN_FILE);
	remove(SOURCE ".exe");
	return errno;
}
