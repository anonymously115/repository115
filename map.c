#include <stdlib.h>
#include <string.h>
#include "map.h"

typedef struct NODE{
	char* key; //�L�[
	void* value; //�l
	struct NODE* child[2]; //child[0]:���̎q(�L�[���e��菬����)�Achild[1]:�E�̎q(�L�[���e���傫��)
}NODE;

struct MAP{
	NODE* root; //���m�[�h
};

/*
 * �R���X�g���N�^
 */
MAP newMap(){
	MAP map=(MAP)malloc(sizeof(struct MAP));
	if(!map){
		abort();
	}
	map->root=NULL;
	return map;
}

int height(NODE* node){
	if(!node){
		return 0;
	}
	int left=height(node->child[0]);
	int right=height(node->child[1]);
	return left>right?left:right;
}

int balance(NODE* node){
	if(!node){
		abort();
	}
	return height(node->child[0])-height(node->child[1]);
}

void rotate(NODE** node, int flag){//����]=0, �E��]=1
	NODE* pivot=(*node)->child[1-flag];
	(*node)->child[1-flag]=pivot->child[flag];
	pivot->child[flag]=*node;
	*node=pivot;
}

void take_balance(int depth, NODE* nodes[]){
	for(int i=depth-1;i>=0;i--){
		int bal=balance(nodes[i]);
		if(bal>1){
			if(balance(nodes[i]->child[0])<0){
				rotate(&(nodes[i]->child[0]),0);
			}
			rotate(&nodes[i],1);
		}else if(bal<-1){
			if(balance(nodes[i]->child[1])>0){
				rotate(&(nodes[i]->child[1]),1);
			}
			rotate(&nodes[i],0);
		}
	}
}

void setValue(MAP map, const char* key, void* value){
	NODE* nodes[64];
	int depth=0;
	nodes[depth]=map->root;
	int flag=-1;
	while(nodes[depth]){
		int cmp=strcmp(key,nodes[depth]->key);
		if(cmp==0){
			//update����
			nodes[depth]->value=value;
			return;
		}
		flag=(cmp>0);
		nodes[depth+1]=nodes[depth]->child[flag];//���΂�nodes[++depth]=nodes[depth]->child[flag]�͗��\������
		depth++;
	}
	
	/* insert���� */
	//�m�[�h�̃��������m��
	NODE* node=(NODE*)malloc(sizeof(NODE));
	if(!node){
		abort();
	}

	//���\�ȏ����������Ă݂�ikey��value��child[i]�ii=0,1�j��NULL�j
	memset(node,0,sizeof(NODE));

	//�L�[�̃������m��
	node->key=(char*)malloc(strlen(key)+1);
	if(!node->key){
		abort();
	}

	//�L�[���Z�b�g
	strcpy(node->key,key);

	//�l���Z�b�g
	node->value=value;

	nodes[depth]=node;
	if(depth){
		nodes[depth-1]->child[flag]=node;
	}else{
		map->root=node;
	}

	//�ꉞ�A����ő}���������͍X�V�ł����̂����A�}���̏ꍇ�AAVL�؂̍l������p���ē񕪒T���؂̕��t����ۂ��Ƃɂ���B
	//�i���ׂ̈ɁA`nodes`�ɍ�����H���Ă������m�[�h���i�[���Ă������j
	take_balance(depth, nodes);
}

/*
 * �l���擾����
 * map : �A�z�z��
 * key : �T���L�[
 */
void* getValue(MAP map, const char* key){
	NODE* node=map->root;
	while(node){
		int cmp=strcmp(key,node->key);
		if(cmp==0){
			return node->value;
		}
		node=node->child[cmp>0];
	}

	//�L�[���������NULL
	return NULL;
}

/*
 * �m�[�h���̃L�[�E�l�ɑ΂��Ēʂ肪�����i���ːe�ˉE�j�ŏ���
 */
void _foreach(void (*func)(const char* key, const void* value), NODE* node){
	if(node){
		_foreach(func, node->child[0]);
		func(node->key, node->value);
		_foreach(func, node->child[1]);
	}
}

void foreach(MAP map, void (*func)(const char* key, const void* value)){
	_foreach(func, map->root);
}

/*
 * �A�z�z����̃L�[���폜
 */
void* erase(MAP map, const char* key){
	NODE* nodes[64];
	int depth=0;
	nodes[depth]=map->root;
	int flag=-1;
	while(nodes[depth]){
		int cmp=strcmp(key,nodes[depth]->key);
		if(cmp){
			flag=(cmp>0);
			nodes[depth+1]=nodes[depth]->child[flag];
			depth++;
			continue;
		}

		//�폜�Ώۃm�[�h
		NODE* node=nodes[depth];

		//�l��ޔ�
		void* value=node->value;
		
		/* delete���� */
		if(node->child[0] && node->child[1]){//�폜�Ώۃm�[�h�̍��E�̎q������
			//�폜�Ώۃm�[�h�̍��̉E�̉E�́c�E�̃m�[�h�i���[�m�[�h�j���擾
			nodes[++depth]=node->child[0];
			flag=(nodes[depth]->child[1]!=NULL);
			while(nodes[depth]->child[1]){
				nodes[depth+1]=nodes[depth]->child[1];
				depth++;
			}
			
			//���[�m�[�h�̃L�[�ƒl���폜�Ώۃm�[�h�Ɉڂ�
			node->key=nodes[depth]->key;
			node->value=nodes[depth]->value;

			//���[�m�[�h�̐e�̉E��t���ւ���
			nodes[depth-1]->child[flag]=nodes[depth]->child[0];

			//���[�m�[�h�̉��
			free(nodes[depth]->key);
			free(nodes[depth]);
		}else{
			if(node->child[0]){//�폜�Ώۃm�[�h�̍��̎q������
				if(depth){
					nodes[depth-1]->child[flag]=node->child[0];
				}else{
					map->root=node->child[0];
				}
				
			}else if(node->child[1]){//�폜�Ώۃm�[�h�̉E�̎q������
				if(depth){
					nodes[depth-1]->child[flag]=node->child[1];
				}else{
					map->root=node->child[1];
				}
			}else{
				if(depth){
					nodes[depth-1]->child[flag]=NULL;
				}else{
					map->root=NULL;
				}
			}
			free(node->key);
			free(node);
		}
		nodes[depth]=NULL;

		//���[�m�[�h�̑O���獪�Ɍ������ĕ��t����ۂ悤�ɏ���
		take_balance(depth,nodes);
		return value;
	}

	return NULL;
}

/*
 * �A�z�z��̃m�[�h�����
 * �E�ˍ��ːe�̏��ŉ��
 */
void _clear(NODE* node, int flag){
	if(node){
		_clear(node->child[1],flag);
		_clear(node->child[0],flag);
		if(flag)free(node->value);
		free(node->key);
		free(node);
	}
}

/*
 * �A�z�z���������
 */
void clear(MAP map, int flag){
	_clear(map->root,flag);
	map->root=NULL;
}