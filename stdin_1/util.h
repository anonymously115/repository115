#ifndef UTIL_H_
#define UTIL_H_
#include <stdint.h>
#include <stdbool.h>

char* chomp(char*);

bool parse_ulong(const char*, size_t*);

bool parse_int(const char*, int*);

#endif /* UTIL_H_ */
