#ifndef PUB_H_
#define PUB_H_
#include <stdint.h>
#include "Adult.h"

typedef struct __Pub* _Pub;

typedef struct Pub {
	_Pub _pub;
	void (*query)(struct Pub*, const char*);
} Pub;

void pub_init(Pub*, size_t, const uint8_t*);

Pub* new_pub(size_t, const uint8_t*);

void del_pub(Pub**);

#endif /* PUB_H_ */
