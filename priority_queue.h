#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

/* �D��x�t���L���[�\���� */
typedef struct PRIORITY_QUEUE* PRIORITY_QUEUE;

/* �R���X�g���N�^ */
PRIORITY_QUEUE newPriorityQueue(int (*)(const void*, const void*));

/* �v�f��ǉ����� */
void push(PRIORITY_QUEUE queue, void* value);

/* �v�f�����o�� */
void* pop(PRIORITY_QUEUE queue);

#endif //_PRIORITY_QUEUE_H_