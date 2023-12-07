#include <stdlib.h>
#include "list.h"

typedef struct NODE{
  void* value;
  struct NODE* next;
}NODE;

struct LIST{
  NODE* front;
};

LIST newList(void){
  LIST list=(LIST)malloc(sizeof(struct LIST));
  if(!list)abort();
  list->front=NULL;
  return list;
}

void add(LIST list, void* value){
  NODE* node=(NODE*)malloc(sizeof(NODE));
  if(!node)abort();
  node->value=value;
  node->next=NULL;
  if(!list->front){
    list->front=node;
  }else{
    NODE* n=list->front;
    while(n->next)n=n->next;
    n->next=node;
  }
}

void foreach(LIST list, void (*func)(void*)){
	for(NODE* node=list->front;node;node=node->next)func(node->value);
}

void clear(LIST list, int flag){
	while(list->front){
		NODE* node=list->front;
		if(flag)free(node->value);
		list->front=node->next;
		free(node);
	}
}
