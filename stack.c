#include <stdlib.h>
#include "stack.h"

/* ノード */
typedef struct NODE{
	void* value; //データ
	struct NODE* next; //次のデータの格納位置を示すポインタ
}NODE;

/* スタック構造 */
struct STACK{
	NODE* front; //先頭ノードへのポインタ
};

/*
 * スタックのコンストラクタ
 */
STACK newStack(void){
	//メモリ確保
	STACK stack=(STACK)malloc(sizeof(struct STACK));
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
void push(STACK stack, void* value){
	//メモリ確保
	NODE* node=(NODE*)malloc(sizeof(NODE));
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
void* pop(STACK stack){
	//要素が空ならNULLを返す
	if(!stack->front){
		return NULL;
	}

	//先頭ノードを取得
	NODE* node=stack->front;

	//返却値を取得
	void* value=node->value;

	//スタックの先頭を繋ぎ替える
	stack->front=node->next;

	//旧先頭ノードを解放
	free(node);

	//取得した値を返す
	return value;
}

