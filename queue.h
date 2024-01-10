#ifndef QUEUE_H_
#define QUEUE_H_

/* キュー構造体 */
typedef struct queue* Queue;

/* コンストラクタ */
Queue newQueue(void);

/* キューに要素を追加する */
void enqueue(Queue, void*);

/* キューから要素を取り出す */
void* dequeue(Queue);

#endif /* QUEUE_H_ */
