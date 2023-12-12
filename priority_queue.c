#include <stdlib.h>
#include "priority_queue.h"

/* �q�[�v�؂̃m�[�h */
typedef struct NODE{
	void* value; //�f�[�^
	struct NODE* child[2]; //child[0]�����̎q�Achild[1]���E�̎q
}NODE;

struct PRIORITY_QUEUE{
	NODE* root; //�q�[�v�؂̍�
	size_t size; //�v�f��
	int (*cmp)(const void*, const void*); //��r�֐�
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

	/* ��U�A�����ɒǉ�(*1) */
	size_t t=++queue->size;
	int A[8*sizeof(size_t)];
	size_t a=0;
	while(t){
		A[a++]=t&1;
		t>>=1;
	}

	NODE* nodes[a+1];
	nodes[a]=NULL; //�ԕ�
	nodes[0]=node; //�V�m�[�h
	if(!queue->root){//�v�f����0�������ꍇ�i���̎��Ɍ���a=1�j
		queue->root=node;
	}else{//���łɗv�f����i���̎�a>=2�j
		nodes[a-1]=queue->root;
		for(size_t i=a-2;i>0;i--){
			nodes[i]=nodes[i+1]->child[A[i]];
		}
		nodes[1]->child[A[0]]=node;
	}

	//�q(child)�̓Y��
	size_t c=0;

	//�e(parent)�̓Y��
	size_t p=c+1;
	
	//����ւ����
	while(nodes[p]){
		if(queue->cmp(nodes[c]->value,nodes[p]->value)<0){//�q���u�������v
			//�m�[�h���̒l�����ւ�
			void* tmp=nodes[c]->value;
			nodes[c]->value=nodes[p]->value;
			nodes[p]->value=tmp;
		}else{
			break;
		}
		
		//�q�̓Y�������X�V
		c=p;
		
		//�e�̓Y�������X�V
		p=c+1;
	}
}

void* pop(PRIORITY_QUEUE queue){
	if(!queue->size){
		return NULL;
	}
	
	//�ԋp�l
	void* value=queue->root->value;

	/* �q�[�v�č\�z */
	//�����v�f��擪�Ɉړ�
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
	//nodes[0]�������m�[�h
	queue->root->value=nodes[0]->value;
	free(nodes[0]);
	nodes[0]=NULL;
	if(a>1){
		nodes[1]->child[A[0]]=NULL;
	}else{
		queue->root=NULL;
	}
	
	//����ւ����
	NODE* parent=nodes[a-1];
	while(parent){
		if(!parent->child[0]){//�q�����݂��Ȃ�
			break;
		}
		
		//��r�ΏۂƂ���q
		NODE* child=NULL;

		if(parent->child[1] && queue->cmp(parent->child[0]->value,parent->child[1]->value)>0){//�E�����݂��A�������E
			//�E�̎q����r�Ώ�
			child=parent->child[1];
		}else{//�E�����݂��Ȃ��A�܂��͍����E
			//���̎q����r�Ώ�
			child=parent->child[0];
		}

		if(queue->cmp(parent->value,child->value)>0){//�e���傫��
			//����ւ�
			void* tmp=parent->value;
			parent->value=child->value;
			child->value=tmp;

			//���݂̎q�����̐e�Ƃ���
			parent=child;
		}else{
			break;
		}
	}

	return value;
}
