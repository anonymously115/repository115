#ifndef _LIST_H_
#define _LIST_H_

/* ���X�g�\���� */
typedef struct LIST* LIST;

/* �R���X�g���N�^ */
LIST newList(void);

/* ���X�g�ɗv�f��ǉ� */
void add(LIST, void*);

/* ���X�g�̗v�f�ɏ�����K�p */
void foreach(const LIST, void (*)(void*));

/* ���X�g��� */
void clear(LIST, int);

#endif //_LIST_H_