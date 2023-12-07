#ifndef _LIST_H_
#define _LIST_H_
typedef struct LIST* LIST;
LIST newList(void);
void add(LIST, void*);
void foreach(const LIST, void (*)(void*));
void clear(LIST, int);
#endif //_LIST_H_
