#ifndef UTIL_H_
#define UTIL_H_
#include <stdint.h>
#include <stdbool.h>

char* chomp(char*);

bool parse_ubyte(const char*, uint8_t*);

bool parse_ushort(const char*, uint16_t*);

bool parse_uint(const char*, uint32_t*);

bool parse_ulong(const char*, size_t*);

#endif /* UTIL_H_ */
