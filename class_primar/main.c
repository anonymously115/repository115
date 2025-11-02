#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "util.h"
#include "input.h"
#include "Pub.h"
#include "Customer.h"

int main() {
	char line[] = "1000 softdrink 5000\n";
	size_t N;
	uint16_t k;
	if (!read_numbers(chomp(fgets(line, sizeof(line), stdin)), &N, &k)) {
		fprintf(stderr, "%s\n", strerror(errno));
		return errno;
	}

	Pub *pub = new_Pub();
	while (N--) {
		uint8_t a;
		if (!read_age(chomp(fgets(line, sizeof(line), stdin)), &a)) {
			del_Pub(&pub);
			fprintf(stderr, "%s\n", strerror(errno));
			return errno;
		}
		if (!pub->add_customer(pub, a)) {
			del_Pub(&pub);
			fprintf(stderr, "%s\n", strerror(errno));
			return errno;
		}
	}

	while (k--) {
		size_t n = 0;
		char s[] = "softdrink";
		uint32_t m = 0;
		if (!read_query(chomp(fgets(line, sizeof(line), stdin)), &n, s, &m)) {
			del_Pub(&pub);
			fprintf(stderr, "%s\n", strerror(errno));
			return errno;
		}
		if (!pub->order(pub, n - 1, s, m)) {
			del_Pub(&pub);
			fprintf(stderr, "%s\n", strerror(errno));
			return errno;
		}
	}

	printf("%zu\n", get_num_of_left());
	return EXIT_SUCCESS;
}
