#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "map.h"

typedef struct node {
	char *key; //キー
	void *value; //値
	struct node *child[2]; //child[0]:左の子(キーが親より小さい)、child[1]:右の子(キーが親より大きい)
} Node;

struct map {
	Node *root; //根ノード
};

/*
 * コンストラクタ
 */
Map newMap() {
	//メモリ確保
	Map map = (Map) malloc(sizeof(struct map));
	if (!map) { //メモリ確保失敗
		abort();
	}
	//根ノードをNULLにセット
	map->root = NULL;

	return map;
}

/*
 * 部分木としての高さ
 */
int height(Node *node) {
	if (!node) { //NULLなら0を返す
		return 0;
	}

	//再帰的に、左部分木と右部分木の高さを取得する。
	int left = height(node->child[0]);
	int right = height(node->child[1]);

	//左部分木と右部分木の高い方の高さ+1を返す
	return (left > right ? left : right) + 1;
}

/*
 * 平衡係数。
 * 今回は、左部分木の高さ－右部分木の高さで定義する。
 */
int balance(Node *node) {
	return height(node->child[0]) - height(node->child[1]);
}

/*
 * 部分木の「回転」
 * node: 付け替え対象となるノードの親ノード
 * flag: 左回転=0, 右回転=1
 */
void rotate(Node **node, int flag) {
	Node *pivot = (*node)->child[1 - flag];
	(*node)->child[1 - flag] = pivot->child[flag];
	pivot->child[flag] = *node;
	*node = pivot;
}

/*
 * 連想配列を構成する二分木の平衡性を保つ処理
 * map: 連想配列
 * depth: 挿入ノードまたは削除ノードの深さ
 * nodes: 根ノードから挿入または削除ノードまで辿ったノード
 * （nodes[0]が根ノード、nodes[depth]が挿入されたノードまたは削除されたノード※削除された場合は既にNULLになっている）
 * flag: node[i+1](子)がnode[i](親)に対して左にあるか右にあるか
 * （flag[i]=0ならnode[i+1]はnode[i]の左の子、flag[i]=1ならnode[i+1]はnode[i]の右の子）
 */
void take_balance(Map map, int depth, Node *nodes[], bool flag[]) {
	//対象ノードの親から根に向かって進む
	for (int i = depth - 1; i >= 0; i--) {
		//平衡係数（左部分木の高さ－右部分木の高さ）
		int bal = balance(nodes[i]);
		if (bal > 1) { //左部分木の高さ－右部分木の高さ≧２の場合（平衡性が崩れているので修正）
			if (balance(nodes[i]->child[0]) < 0) { //左の子について、右部分木の高さが左のそれより高い場合
				//左の子をつけかえる
				rotate(&(nodes[i]->child[0]), 0);
			}
			//平衡係数を計算したノードの親に対する子ノードを繋ぎかえる
			if (i) {
				rotate(&(nodes[i - 1]->child[flag[i - 1]]), 1);
			} else {
				rotate(&(map->root), 1);
			}
		} else if (bal < -1) {             //右部分木の高さ－左部分木の高さ≧２の場合（平衡性が崩れているので修正）
			if (balance(nodes[i]->child[1]) > 0) {  //右の子について、左部分木の高さが右のそれより高い場合
				//右の子をつけかえる
				rotate(&(nodes[i]->child[1]), 1);
			}
			//平衡係数を計算したノードの親に対する子ノードを繋ぎかえる
			if (i) {
				rotate(&(nodes[i - 1]->child[flag[i - 1]]), 0);
			} else {
				rotate(&(map->root), 0);
			}
		}
	}
}

/*
 * キーと値をセットする
 */
void setValue(Map map, const char *key, void *value) {
	//辿ったノードを格納しておくための配列
	Node *nodes[8 * sizeof(void*)];

	//辿ったノードの左右を格納しておくための配列(左がfalse、右がtrue)
	bool flag[8 * sizeof(void*)];

	//辿ったノードの深さ
	int depth = 0;

	//0番目に根ノードを格納しておく
	nodes[depth] = map->root;

	//配列にNULLが格納されるまで子ノードを辿る
	while (nodes[depth]) {
		int cmp = strcmp(key, nodes[depth]->key);
		if (cmp == 0) {                //一致したキーが存在する場合
			/* update処理 */
			nodes[depth]->value = value;
			return;
		}

		//辞書順比較。新キーが早ければ0(左)、後ならば1(右)
		flag[depth] = (cmp > 0);

		//配列に子ノードを格納する（流石にnodes[++depth]=nodes[depth]->child[flag]は乱暴すぎる）
		nodes[depth + 1] = nodes[depth]->child[flag[depth]];
		depth++;
	}

	/* insert処理 */
	//新しいノードのメモリを確保
	Node *node = (Node*) malloc(sizeof(Node));
	if (!node) {                //メモリ確保失敗
		abort();
	}

	//乱暴な初期化をしてみる（keyもvalueもchild[i]（i=0,1）もNULL）
	memset(node, 0, sizeof(Node));

	//キーのメモリ確保
	node->key = (char*) malloc(strlen(key) + 1);
	if (!node->key) {                //メモリ確保失敗
		abort();
	}

	//キーをセット
	strcpy(node->key, key);

	//値をセット
	node->value = value;

	//最初に用意した配列に新ノードを格納（実は、後で使わない）
	nodes[depth] = node;
	if (depth) {
		//一つ前のノードが親ノード。親ノードに子ノードを紐づける。左右フラグは先程のwhile文の内部で回している。
		nodes[depth - 1]->child[flag[depth - 1]] = node;
	} else {
		//要素数が0だった場合、根ノードにセットする。
		map->root = node;
	}

	//一応、これで挿入もしくは更新できたのだが、挿入の場合、二分探索木の平衡性を保つことにする。
	//（その為に、`nodes`に根から辿っていったノードを格納しておいた）
	take_balance(map, depth, nodes, flag);
}

/*
 * 値を取得する
 * map : 連想配列
 * key : 探索キー
 */
void* getValue(Map map, const char *key) {
	Node *node = map->root;
	while (node) {
		int cmp = strcmp(key, node->key);
		if (cmp == 0) {	//キーがヒットした場合、値を返す。
			return node->value;
		}
		//引数キーがノードキーより早ければ左、後ならば右の子を探索していく
		node = node->child[cmp > 0];
	}

	//キーが無ければNULL
	return NULL;
}

/*
 * ノード内のキー・値に対して通りがけ順（左⇒親⇒右）で処理
 */
void _foreach(void (*func)(const char *key, const void *value), Node *node) {
	if (node) {	//node==NULLの場合はスキップ
		//左の子に対して処理
		_foreach(func, node->child[0]);

		//自分自身に対して処理
		func(node->key, node->value);

		//右の子に対して処理
		_foreach(func, node->child[1]);
	}
}

void foreach(Map map, void (*func)(const char *key, const void *value)) {
	//根ノードから再帰的に処理
	_foreach(func, map->root);
}

/*
 * 連想配列内のキーを削除
 * 注意：返却値について、mallocでメモリ確保していた場合、関数呼び出し元で責任をもって解放すること!!
 */
void* erase(Map map, const char *key) {
	//辿ったノードを格納しておくための配列
	Node *nodes[64];

	//辿ったノードの左右を格納しておくための配列(左がfalse、右がtrue)
	bool flag[64];

	//辿ったノードの深さ
	int depth = 0;

	//0番目に根ノードを格納しておく
	nodes[depth] = map->root;

	while (nodes[depth]) {
		int cmp = strcmp(key, nodes[depth]->key);
		if (cmp) {		//キーが一致しなかった場合
			//辞書順比較。新キーが早ければ0(左)、後ならば1(右)
			flag[depth] = (cmp > 0);

			//配列に子ノードを格納する
			nodes[depth + 1] = nodes[depth]->child[flag[depth]];
			depth++;
			continue;
		}

		//削除対象ノード
		Node *node = nodes[depth];

		//返却値を退避
		void *value = node->value;

		//削除ノードの、キーを格納するために確保したメモリを解放する。
		free(node->key);

		/* delete処理 */
		if (node->child[0] && node->child[1]) {			//削除対象ノードの左右の子が存在
			//削除対象ノードの左の右の右の…右のノード（末端ノード）を取得
			flag[depth] = 0;
			nodes[depth + 1] = node->child[0];
			depth++;
			while (nodes[depth]->child[1]) {
				flag[depth] = 1;
				nodes[depth + 1] = nodes[depth]->child[1];
				depth++;
			}

			//末端ノードのキーと値を削除対象ノードに移す
			node->key = nodes[depth]->key;
			node->value = nodes[depth]->value;

			//末端ノードの親の右を付け替える
			nodes[depth - 1]->child[flag[depth - 1]] = nodes[depth]->child[0];

			//末端ノードの解放
			free(nodes[depth]);
		} else {
			if (node->child[0]) {			//削除対象ノードの左の子が存在
				//親が自分に指していたポインタを、自分の左に付け替える
				if (depth) {
					nodes[depth - 1]->child[flag[depth - 1]] = node->child[0];
				} else {
					map->root = node->child[0];
				}
			} else if (node->child[1]) {				//削除対象ノードの右の子が存在
				//親が自分に指していたポインタを、自分の右に付け替える
				if (depth) {
					nodes[depth - 1]->child[flag[depth - 1]] = node->child[1];
				} else {
					map->root = node->child[1];
				}
			} else {
				//親が自分に指していたポインタを、NULLに付け替える
				if (depth) {
					nodes[depth - 1]->child[flag[depth - 1]] = NULL;
				} else {
					map->root = NULL;
				}
			}
			//削除ノードの解放
			free(node);
		}

		//nodes[depth]は解放された領域を指しているので、NULLにする。
		nodes[depth] = NULL;

		//末端ノードの前から根に向かって平衡性を保つように処理
		take_balance(map, depth, nodes, flag);

		//対象キーに対応していた値を返す（mallocでメモリ確保した場合、呼び出し元で解放せよ）
		return value;
	}

	//キーが存在しなかった場合、NULLを返却する。
	return NULL;
}

/*
 * 連想配列のノードを解放
 * 右⇒左⇒親の順で解放（左⇒右⇒親でも構わない）
 */
void _clear(Node *node, int flag) {
	if (node) {				//ノードがNULLでない場合
		//右を解放する
		_clear(node->child[1], flag);

		//左を解放する
		_clear(node->child[0], flag);

		//mallocでメモリ確保した場合、解放
		if (flag)
			free(node->value);

		//キーを格納するために確保したメモリを解放
		free(node->key);

		//ノードを解放
		free(node);
	}
}

/*
 * 連想配列を初期化
 */
void clear(Map map, int flag) {
	//根ノードから再帰的に解放
	_clear(map->root, flag);

	//根ノードをNULLにセット
	map->root = NULL;
}
