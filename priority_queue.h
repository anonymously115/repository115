#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

/* 優先度付きキュー構造体 */
typedef struct PRIORITY_QUEUE* PRIORITY_QUEUE;

/* コンストラクタ */
PRIORITY_QUEUE newPriorityQueue(int (*)(const void*, const void*));

/* 要素を追加する */
void push(PRIORITY_QUEUE queue, void* value);

/* 要素を取り出す */
void* pop(PRIORITY_QUEUE queue);

#endif //_PRIORITY_QUEUE_H_