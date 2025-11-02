#include <stdlib.h>
#include <stdbool.h>
#include "Adult.h"

struct __Adult {
	Customer super;
	bool alcohol;
	void (*take_food)(struct Customer*, uint32_t);
};

static void Adult_take_food(Customer *self, uint32_t price) {
	Adult *adult = (Adult*) self;
	if (adult->alcohol) {
		adult->take_food(self, price - 200);
	} else {
		adult->take_food(self, price);
	}
}

static void Adult_take_alcohol(Customer *self, uint32_t price) {
	Adult *adult = (Adult*) self;
	adult->alcohol = true;
	self->set_amount(self, self->get_amount(self) + price);
}

bool Adult_init(Adult *adult) {
	if (!Customer_init(&adult->super)) return false;
	adult->alcohol = false;
	adult->take_food = adult->super.take_food;
	adult->super.take_food = Adult_take_food;
	adult->super.take_alcohol = Adult_take_alcohol;
	return true;
}

Adult* new_Adult() {
	Adult *adult = NULL;
	if (!(adult = (Adult*) malloc(sizeof(Adult)))) return NULL;
	if (!Adult_init(adult)) {
		del_Customer((Customer**) &adult);
		return NULL;
	}
	return adult;
}
