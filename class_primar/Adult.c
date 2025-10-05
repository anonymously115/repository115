#include <stdlib.h>
#include <stdbool.h>
#include "Adult.h"

typedef struct _Adult{
	Customer super;
	bool alcohol;
	void (*take_food)(struct Customer*, unsigned);
};

static void Adult_take_food(Customer *self, unsigned price) {
	Adult adult = (Adult) self;
	if (adult->alcohol) {
		adult->take_food(self, price > 200 ? price - 200 : 0);
	} else {
		adult->take_food(self, price);
	}
}

static void Adult_take_alcohol(Customer *self, unsigned price) {
	Adult adult = (Adult) self;
	adult->alcohol = true;
	self->amount += price;
}

Adult new_adult() {
	Adult adult = (Adult) malloc(sizeof(struct _Adult));
	customer_init(&adult->super);
	adult->alcohol = false;
	adult->take_food = adult->super.take_food;
	adult->super.take_food = Adult_take_food;
	adult->super.take_alcohol = Adult_take_alcohol;
	return adult;
}
