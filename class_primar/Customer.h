#ifndef CUSTOMER_H_
#define CUSTOMER_H_

typedef struct __Customer* _Customer;

typedef struct Customer {
	unsigned amount;
	void (*take_food)(struct Customer*, unsigned);
	void (*take_softdrink)(struct Customer*, unsigned);
	void (*take_alcohol)(struct Customer*, unsigned);
	void (*take_beer)(struct Customer*);
	void (*accounting)(struct Customer*);
} Customer;

void customer_init(Customer*);

Customer* new_customer();

size_t get_num_of_left();

#endif /* CUSTOMER_H_ */
