#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "input.h"
#include "util.h"

bool parse(const char *str, char *s) {
	errno = 0;
	if (!(str && *str)) {
		errno = EINVAL;
		return false;
	}
	char t[strlen(str) + 1];
	if (strlen(chomp(strcpy(t, str))) > 100) {
		errno = EINVAL;
		return false;
	}
	if (!*t) {
		errno = EINVAL;
		return false;
	}
	for (const char *c = t; *c; c++) {
		if (!isalnum(*c)) {
			errno = EINVAL;
			return false;
		}
	}
	strcpy(s, t);
	return true;
}

