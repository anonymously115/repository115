#ifndef _STACK_H_
#define _STACK_H_

/* �X�^�b�N�\���� */
typedef struct STACK* STACK;

/* �R���X�g���N�^ */
STACK newStack(void);

/* �X�^�b�N�ɗv�f��ǉ����� */
void push(STACK, void*);

/* �X�^�b�N����v�f�����o�� */
void* pop(STACK);

#endif //_STACK_H_