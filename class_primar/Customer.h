#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct __Customer _Customer;

typedef struct Customer {
	_Customer *_customer;
	void (*set_amount)(struct Customer*, uint32_t);
	uint32_t (*get_amount)(struct Customer*);
	void (*take_food)(struct Customer*, uint32_t);
	void (*take_softdrink)(struct Customer*, uint32_t);
	void (*take_alcohol)(struct Customer*, uint32_t);
	void (*take_beer)(struct Customer*);
	void (*accounting)(struct Customer*);
} Customer;

bool Customer_init(Customer*);
Customer* new_Customer(void);
size_t get_num_of_left(void);
void del_Customer(Customer**);

#endif /* CUSTOMER_H_ */
