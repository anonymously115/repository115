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
	size_t N = 0;
	uint16_t K = 0;
	if (!read_numbers(chomp(fgets(line, sizeof(line), stdin)), &N, &K)) {
		int err_no = errno;
		if (err_no == EINVAL) {
			if (!N) perror("The number of customers must be a positive integer.");
			else if (!K) perror("The number of orders must be a positive integer.");
			else perror(NULL);
		} else if (err_no == ERANGE) {
			if (!N) perror("The number of customers must be a positive integer.");
			else if (N > 1000) perror("The number of customers must be 1000 or less.");
			else if (!K) perror("The number of orders must be a positive integer.");
			else if (K > 1000) perror("The number of orders must be 1000 or less.");
			else perror(NULL);
		} else {
			perror(NULL);
		}
		return err_no;
	}

	Pub *pub = new_Pub();
	Customer *customers[N];
	for (size_t i = 0; i < N; i++) {
		uint8_t a = 0;
		if (!read_age(chomp(fgets(line, sizeof(line), stdin)), &a)) {
			del_Pub(&pub);
			int err_no = errno;
			if (err_no == EINVAL) {
				perror("The age must be a positive integer.");
			} else if (err_no == ERANGE) {
				if (!a) perror("The age must be a positive integer.");
				else perror("The age must be 100 or less.");
			} else {
				perror(NULL);
			}
			return err_no;
		}
		if (!(customers[i] = pub->add_customer(pub, a))) {
			del_Pub(&pub);
			int err_no = errno;
			perror(NULL);
			return err_no;
		}
	}

	while (K--) {
		size_t n = 0;
		char s[] = "softdrink";
		uint32_t m = 0;
		if (!read_query(chomp(fgets(line, sizeof(line), stdin)), &n, s, &m)) {
			del_Pub(&pub);
			int err_no = errno;
			if (err_no == EINVAL) {
				perror(NULL);
				fprintf(stderr, "Usage: n <food|softdrink|alcohol> m\n");
				fprintf(stderr, "   or  n <0|A>\n");
				fprintf(stderr, "where  n: The customer number\n");
				fprintf(stderr, "  and  m: The price of the order.");
			} else if (err_no == ERANGE) {
				if (!n) perror("The customer number must be a positive integer.");
				else if (n > 1000) perror("The customer number must be 1000 or less.");
				else if (m < 300 || 5000 < m) perror("The price must be an integer between 300 and 5000.");
				else perror(NULL);
			} else {
				perror(NULL);
			}
			return err_no;
		}
		if (!pub->order(pub, n - 1, s, m)) {
			del_Pub(&pub);
			int err_no = errno;
			if (err_no == EINVAL) {
				perror("The type of order must be either food, softdrink, alcohol, 0, or A.");
			} else if (err_no == ERANGE) {
				perror("The customer number must be less than the number of customers.");
			} else {
				perror(NULL);
			}
			return err_no;
		}
	}
	del_Pub(&pub);
	printf("%zu\n", get_num_of_left());
	return EXIT_SUCCESS;
}
