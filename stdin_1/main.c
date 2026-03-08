#include <stdio.h>
#include <stdlib.h>
#ifdef NDEBUG
#include <string.h>
#include <errno.h>
#include "input.h"
const char END[] = { EOF, '\n', 0 };
#else
#include <time.h>
#define PRINT(format, ...)                      \
	do {                                        \
		fprintf(stderr, format, ##__VA_ARGS__); \
		fflush(stderr);                         \
	} while (0)
#endif

int main(int argc, char *argv[]) {
#ifndef NDEBUG
	clock_t clockt = clock();
#endif
	char str[102] = { };
#ifdef NDEBUG
	if (argc <= 1 || atoi(argv[1]) == 0) {
		do {
			errno = 0;
			char s[102];
			fgets(s, sizeof(s), stdin);
			if (!strchr(s, '\n')) {
				for (int c = getchar(); !strchr(END, c); c = getchar());
				errno = EINVAL;
			} else if (parse(s, str)) {
				break;
			}
			perror("Each character of the input value must be a lowercase letter, an uppercase letter, or a digit.");
		} while (true);
	}
#else
	if (argc <= 1 || atoi(argv[1]) == 0) {}
#endif
	puts(str);
#ifndef NDEBUG
	PRINT("%f sec.\n", (float) (clock() - clockt) / CLOCKS_PER_SEC);
#endif
	return 0;
}
