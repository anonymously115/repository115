#include <stdlib.h>
#include "list.h"

/* ノード（単方向リスト） */
typedef struct NODE{
	void* value; //データ
	struct NODE* next; //次のデータの格納位置を示すポインタ
}NODE;

/* リスト構造 */
struct LIST{
	NODE* front; //先頭ノードへのポインタ
};

/*
 * リストのコンストラクタ
 */
LIST newList(void){
	//メモリ確保
	LIST list=(LIST)malloc(sizeof(struct LIST));
	if(!list){//メモリ確保失敗
		abort();
	}

	//リストの先頭ノードをNULLにセットする
	list->front=NULL;
	return list;
}

/*
 * リストの末尾に要素を追加
 * list : リスト
 * value : 追加するデータ
 */
void add(LIST list, void* value){
	//メモリ確保
	NODE* node=(NODE*)malloc(sizeof(NODE));
	if(!node){//メモリ確保失敗
		abort();
	}

	//ノードにデータをセット
	node->value=value;

	//新しいノードの次はNULL
	node->next=NULL;

	//末尾ノードの次に新しいノードをセット
	if(!list->front){//空リストの場合
		//先頭要素に追加
		list->front=node;
	}else{
		//現在の末尾ノード（「次のノードがNULL」となっているノード）を探す
		NODE* n=list->front;
		while(n->next){
			n=n->next;
		}

		//末尾ノードの次が新しいノード
		n->next=node;
	}
}

/*
 * リストの要素に処理を適用
 * list : リスト
 * func : 処理（関数）
 */
void foreach(LIST list, void (*func)(void*)){
	for(NODE* node=list->front;node;node=node->next){//リストの先頭からノードを辿っていく
		//ノード内のデータに処理を適用
		func(node->value);
	}
}

/*
 * リストの解放
 * list : リスト
 * flag : malloc等でメモリ確保した要素を追加した場合は非零
 */
void clear(LIST list, int flag){
	//リストの先頭から順にノードを解放していく
	while(list->front){
		NODE* node=list->front;
		
		//malloc等で確保した要素を追加した場合、そのメモリを解放
		if(flag){
			free(node->value);
		}

		//リストの先頭ノードを繋ぎ替える
		list->front=node->next;

		//ノード解放
		free(node);
	}
}
