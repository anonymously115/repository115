#include <stdlib.h>
#include "priority_queue.h"

/* ヒープ木のノード */
typedef struct node {
	void *value; //データ
	struct node *child[2]; //child[0]が左の子、child[1]が右の子
} Node;

struct priority_queue {
	Node *root; //ヒープ木の根
	size_t size; //要素数
	int (*cmp)(const void*, const void*); //比較関数
};

PriorityQueue newPriorityQueue(int (*cmp)(const void*, const void*)) {
	PriorityQueue queue = (PriorityQueue) malloc(sizeof(struct priority_queue));
	if (!queue) { //メモリ確保失敗
		abort();
	}

	//根ノードをNULLで初期化
	queue->root = NULL;

	//比較関数をセット
	queue->cmp = cmp;

	//要素数は0で初期化
	queue->size = 0;

	return queue;
}

void push(PriorityQueue queue, void *value) {
	//ノードのメモリを確保
	Node *node = (Node*) malloc(sizeof(struct node));
	if (!node) { //メモリ確保失敗
		abort();
	}
	//ノードに値をセット
	node->value = value;

	//左右の子はNULLで初期化しておく
	node->child[0] = NULL;
	node->child[1] = NULL;

	/* 一旦、末尾に追加(*1) */
	//サイズをインクリメントし、インクリメント後の値を二進法表記する
	size_t n = ++queue->size;

	//新しい要素数の二進法表記
	int bits[8 * sizeof(size_t)];

	//新しい要素数を二進法表記した時の桁数
	size_t b = 0;

	//新しい要素数を二進法表記していく
	while (n) {
		bits[b++] = n & 1;
		n >>= 1;
	}

	Node *nodes[b + 1];
	nodes[b] = NULL; //番兵
	nodes[b - 1] = queue->root; //根ノード（対応するbits[b-1]の値は1）
	nodes[0] = node; //新ノード
	if (!queue->root) { //要素数が0だった場合（この時に限りb=1）
		//根ノードに新ノードをセット
		queue->root = node;
	} else {
		for (size_t i = b - 2; i > 0; i--) {
			//二進法表記に対応して、0ならば左、1ならば右を辿っていく
			nodes[i] = nodes[i + 1]->child[bits[i]];
		}
		//末尾に新ノードをセット
		nodes[1]->child[bits[0]] = node;
	}

	//子(child)の添字
	size_t c = 0;

	//親(parent)の添字
	size_t p = c + 1;

	//入れ替え作業（葉⇒根）
	while (nodes[p]) {
		if (queue->cmp(nodes[c]->value, nodes[p]->value) < 0) {        //子が「小さい」
			//ノード内の値を入れ替え
			void *tmp = nodes[c]->value;
			nodes[c]->value = nodes[p]->value;
			nodes[p]->value = tmp;
		} else {
			break;
		}

		//子の添え字を更新
		c = p;

		//親の添え字を更新
		p = c + 1;
	}
}

void* pop(PriorityQueue queue) {
	if (!queue->size) {            //要素数が0の場合
		//NULLを返す
		return NULL;
	}

	//返却値
	void *value = queue->root->value;

	/* ヒープ再構築 */
	//現在の要素数を二進法表記する
	size_t n = queue->size--;

	//現在の要素数の二進法表記
	int bits[8 * sizeof(size_t)];

	//現時点での要素数を二進法表記した時の桁数
	size_t b = 0;

	//現在の要素数を二進法表記していく
	while (n) {
		bits[b++] = n & 1;
		n >>= 1;
	}

	Node *nodes[b];
	nodes[b - 1] = queue->root; //根ノード（対応するbits[b-1]の値は1）
	for (size_t i = b - 1; i > 0; i--) {
		//二進法表記に対応して、0ならば左、1ならば右の子を辿っていく
		nodes[i - 1] = nodes[i]->child[bits[i - 1]];
	}

	//nodes[0]が末尾ノード。末尾ノードの要素を根ノードの要素に移動
	queue->root->value = nodes[0]->value;

	//末尾ノードのメモリを解放
	free(nodes[0]);

	//末尾ノードを指していたポインタにNULLをセットする
	nodes[0] = NULL;
	if (b > 1) {
		nodes[1]->child[bits[0]] = NULL;
	} else {
		queue->root = NULL;
	}

	//入れ替え作業（根⇒葉）
	Node *parent = nodes[b - 1];
	while (parent) {
		if (!parent->child[0]) { //子が存在しない
			break;
		}

		//比較対象とする子
		Node *child = NULL;

		if (parent->child[1]
				&& queue->cmp(parent->child[0]->value, parent->child[1]->value)
						> 0) { //右が存在し、かつ左＞右
				//右の子が比較対象
			child = parent->child[1];
		} else {            //右が存在しない、または左≦右
							//左の子が比較対象
			child = parent->child[0];
		}

		if (queue->cmp(parent->value, child->value) > 0) {            //親が大きい
			//入れ替え
			void *tmp = parent->value;
			parent->value = child->value;
			child->value = tmp;

			//現在の子を次の親とする
			parent = child;
		} else {
			break;
		}
	}

	//元の根ノードの値を返す
	return value;
}
