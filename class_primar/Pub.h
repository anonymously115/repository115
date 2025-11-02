#ifndef PUB_H_
#define PUB_H_
#include <stdint.h>
#include <stdbool.h>

typedef struct __Pub _Pub;

typedef struct Pub {
	_Pub *_pub;
	bool (*add_customer)(struct Pub*, uint8_t);
	bool (*order)(struct Pub*, size_t, const char*, uint32_t);
} Pub;

bool Pub_init(Pub*);
Pub* new_Pub();
void del_Pub(Pub**);

#endif /* PUB_H_ */
