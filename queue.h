#ifndef _QUEUE_H_
#define _QUEUE_H_

/* キュー構造体 */
typedef struct QUEUE* QUEUE;

/* コンストラクタ */
QUEUE newQueue(void);

/* キューに要素を追加する */
void enqueue(QUEUE, void*);

/* キューから要素を取り出す */
void* dequeue(QUEUE);

#endif //_QUEUE_H_