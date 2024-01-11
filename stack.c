#include <stdlib.h>
#include "stack.h"

/* ノード */
typedef struct node{
	void* value; //データ
	struct node* next; //次のデータの格納位置を示すポインタ
}Node;

/* スタック構造 */
struct stack{
	Node* front; //先頭ノードへのポインタ
};

/*
 * スタックのコンストラクタ
 */
Stack newStack(void){
	//メモリ確保
	Stack stack=(Stack)malloc(sizeof(struct stack));
	if(!stack){//メモリ確保失敗
		abort();
	}

	//スタックの先頭ノードをNULLにセットする
	stack->front=NULL;
	return stack;
}

/*
 * スタックの先頭に要素を追加
 * stack : スタック
 * value : 追加するデータ
 */
void push(Stack stack, void* value){
	//メモリ確保
	Node* node=(Node*)malloc(sizeof(Node));
	if(!node){//メモリ確保失敗
		abort();
	}

	//ノードにデータをセット
	node->value=value;

	//新しいノードの次は現在の先頭ノード
	node->next=stack->front;

	//先頭ノードは新しいノード
	stack->front=node;
}

/*
 * スタックから要素を取り出す
 * stack : スタック
 * 返却値 : 取り出すデータ
 */
void* pop(Stack stack){
	//要素が空ならNULLを返す
	if(!stack->front){
		return NULL;
	}

	//先頭ノードを取得
	Node* node=stack->front;

	//返却値を取得
	void* value=node->value;

	//スタックの先頭を繋ぎ替える
	stack->front=node->next;

	//旧先頭ノードを解放
	free(node);

	//取得した値を返す
	return value;
}