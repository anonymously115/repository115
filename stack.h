#ifndef STACK_H_
#define STACK_H_

/* スタック構造体 */
typedef struct stack* Stack;

/* コンストラクタ */
Stack newStack(void);

/* スタックに要素を追加する */
void push(Stack, void*);

/* スタックから要素を取り出す */
void* pop(Stack);

#endif /* STACK_H_ */