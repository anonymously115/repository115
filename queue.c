#include <stdlib.h>
#include "queue.h"

/* ノード */
typedef struct NODE{
	void* value; //データ
	struct NODE* next; //次のデータの格納位置を示すポインタ
}NODE;

/* キュー構造 */
struct QUEUE{
	NODE* front; //先頭ノードへのポインタ
	NODE* back; //末尾ノードへのポインタ
};

/*
 * キューのコンストラクタ
 */
QUEUE newQueue(void){
	//メモリ確保
	QUEUE queue=(QUEUE)malloc(sizeof(struct QUEUE));
	if(!queue){//メモリ確保失敗
		abort();
	}

	//キューの先頭ノードと末尾ノードをNULLにセットする
	queue->front=NULL;
	queue->back=NULL;
	return queue;
}

/*
 * キューの末尾に要素を追加
 * queue : キュー
 * value : 追加するデータ
 */
void enqueue(QUEUE queue, void* value){
	//メモリ確保
	NODE* node=(NODE*)malloc(sizeof(NODE));
	if(!node){//メモリ確保失敗
		abort();
	}

	//ノードにデータをセット
	node->value=value;

	//新しいノードの次はNULL
	node->next=NULL;
	
	//末尾ノードの次は新しいノード
	if(queue->back){
		queue->back->next=node; 
	}

	//末尾ノードは新しいノード
	queue->back=node;

	//空だった場合、先頭ノードは新しいノードを指す
	if(!queue->front){
		queue->front=node;
	}
}

/*
 * キューの先頭から要素を取り出す
 * queue : キュー
 * 返却値 : 取り出すデータ
 */
void* dequeue(QUEUE queue){
	//要素が空ならNULLを返す
	if(!queue->front){
		return NULL;
	}

	//先頭ノードを取得
	NODE* node=queue->front;

	//返却値を取得
	void* value=node->value;

	//キューの先頭を繋ぎ替える
	queue->front=node->next;

	//空になった場合、キューの末尾はNULL
	if(!queue->front){
		queue->back=NULL;
	}

	//旧先頭ノードを解放
	free(node);

	//取得した値を返す
	return value;
}