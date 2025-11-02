#include <string.h>
#include <errno.h>
#include "input.h"
#include "util.h"

bool read_numbers(const char *str, size_t *n, uint16_t *k) {
	if (!str || !n || !k) {
		errno = EINVAL;
		return false;
	}
	errno = 0;
	char s[strlen(str) + 1];
	strcpy(s, str);
	if (!parse_ulong(strtok(s, " "), n)) {
		return false;
	}
	if (*n < 1 || 1000 < *n) {
		errno = ERANGE;
		return false;
	}
	if (!parse_ushort(strtok(NULL, " "), k)) {
		return false;
	}
	if (*k < 1 || 1000 < *k) {
		errno = ERANGE;
		return false;
	}
	if (strtok(NULL, " ")) {
		errno = EINVAL;
		return false;
	}
	return true;
}

bool read_age(const char *str, uint8_t *a) {
	if (!str || !a) {
		errno = EINVAL;
		return false;
	}
	errno = 0;
	if (!parse_ubyte(str, a)) {
		return false;
	}
	if (*a < 1 || 100 < *a) {
		errno = ERANGE;
		return false;
	}
	return true;
}

bool read_query(const char *str, size_t *n, char *s, uint32_t *m) {
	if (!str || !n || !s || !m) {
		errno = EINVAL;
		return false;
	}
	errno = 0;
	char t[strlen(str) + 1];
	strcpy(t, str);
	if (!parse_ulong(strtok(t, " "), n)) {
		return false;
	}
	if (*n < 1 || 1000 < *n) {
		errno = ERANGE;
		return false;
	}
	char *u = NULL;
	if (!(u = strtok(NULL, " "))) {
		errno = EINVAL;
		return false;
	}
	strcpy(s, u);
	if (!strcmp(s, "food") || !strcmp(s, "softdrink") || !strcmp(s, "alcohol")) {
		if (!parse_uint(strtok(NULL, " "), m)) {
			return false;
		}
		if (*m < 300 || 5000 < *m) {
			errno = ERANGE;
			return false;
		}
		if (strtok(NULL, " ")) {
			errno = EINVAL;
			return false;
		}
	} else if (!strcmp(s, "0") || !strcmp(s, "A")) {
		if (strtok(NULL, " ")) {
			errno = EINVAL;
			return false;
		}
	} else {
		errno = EINVAL;
		return false;
	}
	return true;
}

