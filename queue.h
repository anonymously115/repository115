#ifndef _QUEUE_H_
#define _QUEUE_H_

/* �L���[�\���� */
typedef struct QUEUE* QUEUE;

/* �R���X�g���N�^ */
QUEUE newQueue(void);

/* �L���[�ɗv�f��ǉ����� */
void enqueue(QUEUE, void*);

/* �L���[����v�f�����o�� */
void* dequeue(QUEUE);

#endif //_QUEUE_H_