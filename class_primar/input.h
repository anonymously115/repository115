#ifndef INPUT_H_
#define INPUT_H_

#include <stdbool.h>
#include <stdint.h>

bool read_numbers(const char*, size_t*, uint16_t*);

bool read_age(const char*, uint8_t*);

bool read_query(const char*, size_t*, char*, uint32_t*);

#endif /* INPUT_H_ */
