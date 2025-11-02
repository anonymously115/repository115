#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "util.h"

char* chomp(char *str) {
	if (!str) return NULL;
	size_t len = strlen(str);
	while (len--) {
		if (isspace(str[len])) {
			str[len] = '\0';
		} else {
			break;
		}
	}
	return str;
}

static bool is_positive_number(const char *s) {
	if (!(s && *s)) return false;
	for (const char *c = s; *c; c++) {
		if (!isdigit(*c)) return false;
	}
	return true;
}

static bool parse_unsigned(const char *str, uintmax_t *n, uintmax_t max) {
	errno = 0;
	if (!is_positive_number(str)) {
		errno = EINVAL;
		return false;
	}
	char *s = NULL;
	unsigned long long ull = strtoull(str, &s, 10);
	if (errno) {
		return false;
	} else if (s && *s) {
		errno = EINVAL;
		return false;
	} else if (ull > max) {
		errno = ERANGE;
		return false;
	}
	*n = (uintmax_t)ull;
	return true;
}

bool parse_ubyte(const char *str, uint8_t *n) {
	uintmax_t m = 0;
	if (!parse_unsigned(str, &m, UINT8_MAX)) return false;
	*n = (uint8_t)m;
	return true;
}

bool parse_ushort(const char *str, uint16_t *n) {
	uintmax_t m = 0;
	if (!parse_unsigned(str, &m, UINT16_MAX)) return false;
	*n = (uint16_t)m;
	return true;
}

bool parse_uint(const char *str, uint32_t *n) {
	uintmax_t m = 0;
	if (!parse_unsigned(str, &m, UINT32_MAX)) return false;
	*n = (uint32_t)m;
	return true;
}

bool parse_ulong(const char *str, size_t *n) {
	uintmax_t m = 0;
	if (!parse_unsigned(str, &m, SIZE_MAX)) return false;
	*n = (size_t)m;
	return true;
}
