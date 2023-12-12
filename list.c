#include <stdlib.h>
#include "list.h"

/* �m�[�h�i�P�������X�g�j */
typedef struct NODE{
	void* value; //�f�[�^
	struct NODE* next; //���̃f�[�^�̊i�[�ʒu�������|�C���^
}NODE;

/* ���X�g�\�� */
struct LIST{
	NODE* front; //�擪�m�[�h�ւ̃|�C���^
};

/*
 * ���X�g�̃R���X�g���N�^
 */
LIST newList(void){
	//�������m��
	LIST list=(LIST)malloc(sizeof(struct LIST));
	if(!list){//�������m�ێ��s
		abort();
	}

	//���X�g�̐擪�m�[�h��NULL�ɃZ�b�g����
	list->front=NULL;
	return list;
}

/*
 * ���X�g�̖����ɗv�f��ǉ�
 * list : ���X�g
 * value : �ǉ�����f�[�^
 */
void add(LIST list, void* value){
	//�������m��
	NODE* node=(NODE*)malloc(sizeof(NODE));
	if(!node){//�������m�ێ��s
		abort();
	}

	//�m�[�h�Ƀf�[�^���Z�b�g
	node->value=value;

	//�V�����m�[�h�̎���NULL
	node->next=NULL;

	//�����m�[�h�̎��ɐV�����m�[�h���Z�b�g
	if(!list->front){//�󃊃X�g�̏ꍇ
		//�擪�v�f�ɒǉ�
		list->front=node;
	}else{
		//���݂̖����m�[�h�i�u���̃m�[�h��NULL�v�ƂȂ��Ă���m�[�h�j��T��
		NODE* n=list->front;
		while(n->next){
			n=n->next;
		}

		//�����m�[�h�̎����V�����m�[�h
		n->next=node;
	}
}

/*
 * ���X�g�̗v�f�ɏ�����K�p
 * list : ���X�g
 * func : �����i�֐��j
 */
void foreach(LIST list, void (*func)(void*)){
	for(NODE* node=list->front;node;node=node->next){//���X�g�̐擪����m�[�h��H���Ă���
		//�m�[�h���̃f�[�^�ɏ�����K�p
		func(node->value);
	}
}

/*
 * ���X�g�̉��
 * list : ���X�g
 * flag : malloc���Ń������m�ۂ����v�f��ǉ������ꍇ�͔��
 */
void clear(LIST list, int flag){
	//���X�g�̐擪���珇�Ƀm�[�h��������Ă���
	while(list->front){
		NODE* node=list->front;
		
		//malloc���Ŋm�ۂ����v�f��ǉ������ꍇ�A���̃����������
		if(flag){
			free(node->value);
		}

		//���X�g�̐擪�m�[�h���q���ւ���
		list->front=node->next;

		//�m�[�h���
		free(node);
	}
}
