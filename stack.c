#include <stdlib.h>
#include "stack.h"

/* �m�[�h */
typedef struct NODE{
	void* value; //�f�[�^
	struct NODE* next; //���̃f�[�^�̊i�[�ʒu�������|�C���^
}NODE;

/* �X�^�b�N�\�� */
struct STACK{
	NODE* front; //�擪�m�[�h�ւ̃|�C���^
};

/*
 * �X�^�b�N�̃R���X�g���N�^
 */
STACK newStack(void){
	//�������m��
	STACK stack=(STACK)malloc(sizeof(struct STACK));
	if(!stack){//�������m�ێ��s
		abort();
	}

	//�X�^�b�N�̐擪�m�[�h��NULL�ɃZ�b�g����
	stack->front=NULL;
	return stack;
}

/*
 * �X�^�b�N�̐擪�ɗv�f��ǉ�
 * stack : �X�^�b�N
 * value : �ǉ�����f�[�^
 */
void push(STACK stack, void* value){
	//�������m��
	NODE* node=(NODE*)malloc(sizeof(NODE));
	if(!node){//�������m�ێ��s
		abort();
	}

	//�m�[�h�Ƀf�[�^���Z�b�g
	node->value=value;

	//�V�����m�[�h�̎��͌��݂̐擪�m�[�h
	node->next=stack->front;
	
	//�擪�m�[�h�͐V�����m�[�h
	stack->front=node;
}

/*
 * �X�^�b�N����v�f�����o��
 * stack : �X�^�b�N
 * �ԋp�l : ���o���f�[�^
 */
void* pop(STACK stack){
	//�v�f����Ȃ�NULL��Ԃ�
	if(!stack->front){
		return NULL;
	}

	//�擪�m�[�h���擾
	NODE* node=stack->front;

	//�ԋp�l���擾
	void* value=node->value;

	//�X�^�b�N�̐擪���q���ւ���
	stack->front=node->next;

	//���擪�m�[�h�����
	free(node);

	//�擾�����l��Ԃ�
	return value;
}

