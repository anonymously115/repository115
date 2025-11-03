#ifndef PUB_H_
#define PUB_H_
#include <stdbool.h>
#include <stdint.h>
#include "Customer.h"

typedef struct __Pub _Pub;

typedef struct Pub {
	_Pub *_pub;
	Customer* (*add_customer)(struct Pub*, uint8_t);
	bool (*order)(struct Pub*, size_t, const char*, uint32_t);
} Pub;

Pub* new_Pub();
void del_Pub(Pub**);

#endif /* PUB_H_ */
