#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

/* 優先度付きキュー構造体 */
typedef struct priority_queue* PriorityQueue;

/* コンストラクタ */
PriorityQueue newPriorityQueue(int (*)(const void*, const void*));

/* 要素を追加する */
void push(PriorityQueue queue, void* value);

/* 要素を取り出す */
void* pop(PriorityQueue queue);

#endif /* PRIORITY_QUEUE_H_ */
