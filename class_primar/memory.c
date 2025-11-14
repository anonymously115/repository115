#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Pub.h"

int main() {
	(void) getchar();
	Pub *pub = new_Pub();
	for (size_t i = 0; i < 1000; i++) {
		pub->add_customer(pub, (uint8_t) (rand() & 0xFF));
	}
	(void) getchar();
	del_Pub(&pub);
	(void) getchar();
	return 0;
}
