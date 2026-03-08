#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <errno.h>
#include "util.h"

char* chomp(char *s) {
	if (!s)
		return NULL;
	size_t n = strlen(s);
	while (n--)
		if (isspace(s[n]))
			s[n] = '\0';
		else
			break;
	return s;
}

static bool is_positive_number(const char *s) {
	if (!(s && *s))
		return false;
	if (*s == '0')
		return s[1] == 0;
	for (const char *c = s; *c; c++)
		if (!isdigit(*c))
			return false;
	return true;
}

static bool is_number(const char *s) {
	if (!(s && *s))
		return false;
	if (*s == '-')
		return s[1] != 0 && s[1] != '0' && is_positive_number(s + 1);
	else
		return is_positive_number(s);
}

static bool parse_unsigned(const char *str, uintmax_t *u, uintmax_t max) {
	errno = 0;
	if (!is_positive_number(str)) {
		errno = EINVAL;
		return false;
	}
	char *s = NULL;
	*u = strtoumax(str, &s, 10);
	if (errno) {
		return false;
	} else if (s && *s) {
		errno = EINVAL;
		return false;
	} else if (*u > max) {
		errno = ERANGE;
		return false;
	}
	return true;
}

static bool parse_signed(const char *str, intmax_t *i, intmax_t max) {
	errno = 0;
	if (!is_number(str)) {
		errno = EINVAL;
		return false;
	}
	char *s = NULL;
	*i = strtoimax(str, &s, 10);
	if (errno) {
		return false;
	} else if (s && *s) {
		errno = EINVAL;
		return false;
	} else if (*i < ~max || max < *i) {
		errno = ERANGE;
		return false;
	}
	return true;
}

bool parse_ulong(const char *str, size_t *n) {
	uintmax_t m = 0;
	if (!parse_unsigned(str, &m, SIZE_MAX))
		return false;
	*n = (size_t) m;
	return true;
}

bool parse_int(const char *str, int *n) {
	intmax_t m = 0;
	if (!parse_signed(str, &m, INT_MAX))
		return false;
	*n = (int) m;
	return true;
}
