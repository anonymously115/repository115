#include <stdlib.h>
#include "priority_queue.h"

/* ヒープ木のノード */
typedef struct NODE{
	void* value; //データ
	struct NODE* child[2]; //child[0]が左の子、child[1]が右の子
}NODE;

struct PRIORITY_QUEUE{
	NODE* root; //ヒープ木の根
	size_t size; //要素数
	int (*cmp)(const void*, const void*); //比較関数
};

PRIORITY_QUEUE newPriorityQueue(int (*cmp)(const void*, const void*)){
	PRIORITY_QUEUE queue=(PRIORITY_QUEUE)malloc(sizeof(struct PRIORITY_QUEUE));
	if(!queue){
		abort();
	}
	queue->root=NULL;
	queue->cmp=cmp;
	queue->size=0;
	return queue;
}

void push(PRIORITY_QUEUE queue, void* value){
	NODE* node=(NODE*)malloc(sizeof(NODE));
	if(!node){
		abort();
	}
	node->value=value;
	node->child[0]=NULL;
	node->child[1]=NULL;

	/* 一旦、末尾に追加(*1) */
	size_t t=++queue->size;
	int A[8*sizeof(size_t)];
	size_t a=0;
	while(t){
		A[a++]=t&1;
		t>>=1;
	}

	NODE* nodes[a+1];
	nodes[a]=NULL; //番兵
	nodes[0]=node; //新ノード
	if(!queue->root){//要素数が0だった場合（この時に限りa=1）
		queue->root=node;
	}else{//すでに要素あり（この時a>=2）
		nodes[a-1]=queue->root;
		for(size_t i=a-2;i>0;i--){
			nodes[i]=nodes[i+1]->child[A[i]];
		}
		nodes[1]->child[A[0]]=node;
	}

	//子(child)の添字
	size_t c=0;

	//親(parent)の添字
	size_t p=c+1;
	
	//入れ替え作業
	while(nodes[p]){
		if(queue->cmp(nodes[c]->value,nodes[p]->value)<0){//子が「小さい」
			//ノード内の値を入れ替え
			void* tmp=nodes[c]->value;
			nodes[c]->value=nodes[p]->value;
			nodes[p]->value=tmp;
		}else{
			break;
		}
		
		//子の添え字を更新
		c=p;
		
		//親の添え字を更新
		p=c+1;
	}
}

void* pop(PRIORITY_QUEUE queue){
	if(!queue->size){
		return NULL;
	}
	
	//返却値
	void* value=queue->root->value;

	/* ヒープ再構築 */
	//末尾要素を先頭に移動
	size_t t=queue->size--;
	int A[8*sizeof(size_t)];
	size_t a=0;
	while(t){
		A[a++]=t&1;
		t>>=1;
	}

	NODE* nodes[a];
	nodes[a-1]=queue->root;
	for(size_t i=a-1;i>0;i--){
		nodes[i-1]=nodes[i]->child[A[i-1]];
	}
	//nodes[0]が末尾ノード
	queue->root->value=nodes[0]->value;
	free(nodes[0]);
	nodes[0]=NULL;
	if(a>1){
		nodes[1]->child[A[0]]=NULL;
	}else{
		queue->root=NULL;
	}
	
	//入れ替え作業
	NODE* parent=nodes[a-1];
	while(parent){
		if(!parent->child[0]){//子が存在しない
			break;
		}
		
		//比較対象とする子
		NODE* child=NULL;

		if(parent->child[1] && queue->cmp(parent->child[0]->value,parent->child[1]->value)>0){//右が存在し、かつ左＞右
			//右の子が比較対象
			child=parent->child[1];
		}else{//右が存在しない、または左≦右
			//左の子が比較対象
			child=parent->child[0];
		}

		if(queue->cmp(parent->value,child->value)>0){//親が大きい
			//入れ替え
			void* tmp=parent->value;
			parent->value=child->value;
			child->value=tmp;

			//現在の子を次の親とする
			parent=child;
		}else{
			break;
		}
	}

	return value;
}
