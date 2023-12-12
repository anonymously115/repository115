#include <stdlib.h>
#include "queue.h"

/* �m�[�h */
typedef struct NODE{
	void* value; //�f�[�^
	struct NODE* next; //���̃f�[�^�̊i�[�ʒu�������|�C���^
}NODE;

/* �L���[�\�� */
struct QUEUE{
	NODE* front; //�擪�m�[�h�ւ̃|�C���^
	NODE* back; //�����m�[�h�ւ̃|�C���^
};

/*
 * �L���[�̃R���X�g���N�^
 */
QUEUE newQueue(void){
	//�������m��
	QUEUE queue=(QUEUE)malloc(sizeof(struct QUEUE));
	if(!queue){//�������m�ێ��s
		abort();
	}

	//�L���[�̐擪�m�[�h�Ɩ����m�[�h��NULL�ɃZ�b�g����
	queue->front=NULL;
	queue->back=NULL;
	return queue;
}

/*
 * �L���[�̖����ɗv�f��ǉ�
 * queue : �L���[
 * value : �ǉ�����f�[�^
 */
void enqueue(QUEUE queue, void* value){
	//�������m��
	NODE* node=(NODE*)malloc(sizeof(NODE));
	if(!node){//�������m�ێ��s
		abort();
	}

	//�m�[�h�Ƀf�[�^���Z�b�g
	node->value=value;

	//�V�����m�[�h�̎���NULL
	node->next=NULL;
	
	//�����m�[�h�̎��͐V�����m�[�h
	if(queue->back){
		queue->back->next=node; 
	}

	//�����m�[�h�͐V�����m�[�h
	queue->back=node;

	//�󂾂����ꍇ�A�擪�m�[�h�͐V�����m�[�h���w��
	if(!queue->front){
		queue->front=node;
	}
}

/*
 * �L���[�̐擪����v�f�����o��
 * queue : �L���[
 * �ԋp�l : ���o���f�[�^
 */
void* dequeue(QUEUE queue){
	//�v�f����Ȃ�NULL��Ԃ�
	if(!queue->front){
		return NULL;
	}

	//�擪�m�[�h���擾
	NODE* node=queue->front;

	//�ԋp�l���擾
	void* value=node->value;

	//�L���[�̐擪���q���ւ���
	queue->front=node->next;

	//��ɂȂ����ꍇ�A�L���[�̖�����NULL
	if(!queue->front){
		queue->back=NULL;
	}

	//���擪�m�[�h�����
	free(node);

	//�擾�����l��Ԃ�
	return value;
}