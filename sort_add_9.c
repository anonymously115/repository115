#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
	char* key; 
	void* value; 
	struct node* child[2]; 
}Node;

struct map{
	Node* root; 
};

typedef struct map* Map;

Map newMap(){
    Map map=(Map)malloc(sizeof(struct map));
    if(!map){
        abort();
    }
    map->root=NULL;
    return map;
}

int height(Node* node){
	if(!node){
		return 0;
	}
	int left=height(node->child[0]);
	int right=height(node->child[1]);
	return (left>right?left:right)+1;
}

int balance(Node* node){
	return height(node->child[0])-height(node->child[1]);
}

void rotate(Node** node, int flag){
	Node* pivot=(*node)->child[1-flag];
	(*node)->child[1-flag]=pivot->child[flag];
	pivot->child[flag]=*node;
	*node=pivot;
}

void take_balance(Map map, int depth, Node* nodes[], bool flag[]){
	for(int i=depth-1;i>=0;i--){
        int bal=balance(nodes[i]);
		if(bal>1){
			if(balance(nodes[i]->child[0])<0){
				rotate(&(nodes[i]->child[0]),0);
			}
			if(i){
				rotate(&(nodes[i-1]->child[flag[i-1]]),1);
			}else{
				rotate(&(map->root),1);
			}
		}else if(bal<-1){
			if(balance(nodes[i]->child[1])>0){
				rotate(&(nodes[i]->child[1]),1);
			}
			if(i){
				rotate(&(nodes[i-1]->child[flag[i-1]]),0);
			}else{
				rotate(&(map->root),0);
			}
		}
	}
}

void setValue(Map map, const char* key, void* value){
	Node* nodes[64];
	bool flag[64];
	int depth=0;
	nodes[depth]=map->root;
	while(nodes[depth]){
		int cmp=strcmp(key,nodes[depth]->key);
		if(cmp==0){
			/* update処理 */
			nodes[depth]->value=value;
			return;
		}
		flag[depth]=(cmp>0);
		nodes[depth+1]=nodes[depth]->child[flag[depth]];
		depth++;
	}

	Node* node=(Node*)malloc(sizeof(Node));
	if(!node){
		abort();
	}
	memset(node,0,sizeof(Node));
	node->key=(char*)malloc(strlen(key)+1);
	if(!node->key){
		abort();
	}
	strcpy(node->key,key);
	node->value=value;
	nodes[depth]=node;
	if(depth){
    	nodes[depth-1]->child[flag[depth-1]]=node;
	}else{
		map->root=node;
	}
	take_balance(map, depth, nodes, flag);
}

void* getValue(Map map, const char* key){
	Node* node=map->root;
	while(node){
		int cmp=strcmp(key,node->key);
		if(cmp==0){
			return node->value;
		}
		node=node->child[cmp>0];
	}
	return NULL;
}

void _foreach(void (*func)(const char* key, const void* value), Node* node){
	if(node){
		_foreach(func, node->child[0]);
		func(node->key, node->value);
		_foreach(func, node->child[1]);
	}
}

void foreach(Map map, void (*func)(const char* key, const void* value)){
	_foreach(func, map->root);
}

void* erase(Map map, const char* key){
	Node* nodes[64];
	bool flag[64];
	int depth=0;
	nodes[depth]=map->root;
	while(nodes[depth]){
		int cmp=strcmp(key,nodes[depth]->key);
		if(cmp){
			flag[depth]=(cmp>0);
			nodes[depth+1]=nodes[depth]->child[flag[depth]];
			depth++;
			continue;
		}
		Node* node=nodes[depth];
		void* value=node->value;
        free(node->key);
		if(node->child[0] && node->child[1]){
			flag[depth]=0;
			nodes[depth+1]=node->child[0];
			depth++;
			while(nodes[depth]->child[1]){
				flag[depth]=1;
				nodes[depth+1]=nodes[depth]->child[1];
				depth++;
			}
			node->key=nodes[depth]->key;
			node->value=nodes[depth]->value;
			nodes[depth-1]->child[flag[depth-1]]=nodes[depth]->child[0];
			free(nodes[depth]);
		}else{
			if(node->child[0]){
				if(depth){
					nodes[depth-1]->child[flag[depth-1]]=node->child[0];
				}else{
					map->root=node->child[0];
				}
			}else if(node->child[1]){
				if(depth){
					nodes[depth-1]->child[flag[depth-1]]=node->child[1];
				}else{
					map->root=node->child[1];
				}
			}else{
				if(depth){
					nodes[depth-1]->child[flag[depth-1]]=NULL;
				}else{
					map->root=NULL;
				}
			}
			free(node);
		}
		nodes[depth]=NULL;
		take_balance(map, depth, nodes, flag);
		return value;
	}
	return NULL;
}

void _clear(Node* node, int flag){
	if(node){
		_clear(node->child[1],flag);
		_clear(node->child[0],flag);
		if(flag)free(node->value);
		free(node->key);
		free(node);
	}
}

void clear(Map map, int flag){
	_clear(map->root,flag);
	map->root=NULL;
}

struct priority_queue{
	Node* root; 
	size_t size; 
	int (*cmp)(const void*, const void*); 
};

typedef struct priority_queue* PriorityQueue;

PriorityQueue newPriorityQueue(int (*cmp)(const void*, const void*)){
    PriorityQueue queue=(PriorityQueue)malloc(sizeof(struct priority_queue));
    if(!queue){
        abort();
    }
    queue->root=NULL;
    queue->cmp=cmp;
    queue->size=0;
    return queue;
}

void push(PriorityQueue queue, void* value){
    Node* node=(Node*)malloc(sizeof(struct node));
    if(!node){
        abort();
    }
    node->value=value;
    node->child[0]=NULL;
    node->child[1]=NULL;
    size_t n=++queue->size;
    int bits[8*sizeof(size_t)];
    size_t b=0;
    while(n){
        bits[b++]=n&1;
        n>>=1;
    }
    Node* nodes[b+1];
    nodes[b]=NULL; 
    nodes[b-1]=queue->root; 
    nodes[0]=node; 
    if(!queue->root){
        queue->root=node;
    }else{
        for(size_t i=b-2;i>0;i--){
            nodes[i]=nodes[i+1]->child[bits[i]];
        }
        nodes[1]->child[bits[0]]=node;
    }
    size_t c=0;
    size_t p=c+1;
    while(nodes[p]){
        if(queue->cmp(nodes[c]->value,nodes[p]->value)<0){
            void* tmp=nodes[c]->value;
            nodes[c]->value=nodes[p]->value;
            nodes[p]->value=tmp;
        }else{
            break;
        }
        c=p;
        p=c+1;
    }
}

void* pop(PriorityQueue queue){
    if(!queue->size){
        return NULL;
    }
    void* value=queue->root->value;
    size_t n=queue->size--;
    int bits[8*sizeof(size_t)];
    size_t b=0;
    while(n){
        bits[b++]=n&1;
        n>>=1;
    }
    Node* nodes[b];
    nodes[b-1]=queue->root; 
    for(size_t i=b-1;i>0;i--){
        
        nodes[i-1]=nodes[i]->child[bits[i-1]];
    }
    queue->root->value=nodes[0]->value;
    free(nodes[0]);
    nodes[0]=NULL;
    if(b>1){
        nodes[1]->child[bits[0]]=NULL;
    }else{
        queue->root=NULL;
    }
    Node* parent=nodes[b-1];
    while(parent){
        if(!parent->child[0]){
            break;
        }
        Node* child=NULL;
        if(parent->child[1] && queue->cmp(parent->child[0]->value,parent->child[1]->value)>0){
            child=parent->child[1];
        }else{
            child=parent->child[0];
        }
        if(queue->cmp(parent->value,child->value)>0){
            void* tmp=parent->value;
            parent->value=child->value;
            child->value=tmp;
            parent=child;
        }else{
            break;
        }
    }
    return value;
}

typedef struct pair{
    char key[2];
    int value;
}pair;

int compare(const void* a, const void* b){
    pair p=*(pair*)a;
    pair q=*(pair*)b;
    if(p.value<q.value)return 1;
    else if(p.value>q.value)return -1;
    else return strcmp(p.key,q.key);
}

PriorityQueue Q;
void func(const char* key, const void* value){
    pair* p=(pair*)malloc(sizeof(pair));
    strcpy(p->key,key);
    p->value=*(int*)value;
    push(Q,p);
}

int main(void){
    int n;
    scanf("%d\n",&n);
    Map map=newMap();
    for(int i=0;i<n;i++){
        char s[2];
        int d;
        scanf("%s %d\n",s,&d);
        int* p=getValue(map,s);
        if(!p){
            p=(int*)malloc(sizeof(int));
            *p=0;
            setValue(map,s,p);
        }
        *p+=d;
    }
    Q=newPriorityQueue(compare);
    foreach(map,func);
    pair* q=NULL;
    while((q=pop(Q))!=NULL){
        printf("%s %d\n",q->key,q->value);
        free(q);
    }
    free(Q);
    clear(map,!0);
    free(map);
    return 0;
}