#ifndef _STACK_H_
#define _STACK_H_

/* スタック構造体 */
typedef struct STACK* STACK;

/* コンストラクタ */
STACK newStack(void);

/* スタックに要素を追加する */
void push(STACK, void*);

/* スタックから要素を取り出す */
void* pop(STACK);

#endif //_STACK_H_