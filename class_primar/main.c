//#define NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>
#include "Pub.h"

char* chomp(char* s) {
	size_t n = strlen(s);
	while (n--) {
		if (isspace(s[n])) s[n] = '\0';
		else break;
	}
	return s;
}

int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;
#ifdef NDEBUG
	size_t N;
	uint16_t k;
	scanf("%zu %hd\n", &N, &k);
	uint8_t A[N];
	for (size_t i = 0; i < N; i++) {
		scanf("%u\n", &A[i]);
	}
	Pub* pub = new_pub(N, A);
	char query[] = "1000 softdrink 5000";
	while (k--) {
		pub->query(pub, chomp(fgets(query, sizeof(query), stdin)));
	}
#else
	uint8_t A[] = { 19, 20 };
	Pub* pub = new_pub(sizeof(A)/sizeof(A[0]), A);
	pub->query(pub, "1 softdrink 300");
	pub->query(pub, "1 food 400");
	pub->query(pub, "1 0");
	pub->query(pub, "1 softdrink 600");
	pub->query(pub, "1 food 700");
	pub->query(pub, "1 A");
	pub->query(pub, "2 softdrink 300");
	pub->query(pub, "2 food 400");
	pub->query(pub, "2 0");
	pub->query(pub, "2 softdrink 600");
	pub->query(pub, "2 food 700");
	pub->query(pub, "2 A");
	assert(get_num_of_left() == 2);
#endif
	printf("%zu\n", get_num_of_left());
	del_pub(&pub);
	return 0;
}
