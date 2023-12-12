#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "map.h"

typedef struct NODE{
	char* key; //キー
	void* value; //値
	struct NODE* child[2]; //child[0]:左の子(キーが親より小さい)、child[1]:右の子(キーが親より大きい)
}NODE;

struct MAP{
	NODE* root; //根ノード
};

/*
 * コンストラクタ
 */
MAP newMap(){
	MAP map=(MAP)malloc(sizeof(struct MAP));
	if(!map){
		abort();
	}
	map->root=NULL;
	return map;
}

int height(NODE* node){
	if(!node){
		return 0;
	}
	int left=height(node->child[0]);
	int right=height(node->child[1]);
	return (left>right?left:right)+1;
}

int balance(NODE* node){
	if(!node){
		abort();
	}
	return height(node->child[0])-height(node->child[1]);
}

void rotate(NODE** node, int flag){//左回転=0, 右回転=1
	NODE* pivot=(*node)->child[1-flag];
	(*node)->child[1-flag]=pivot->child[flag];
	pivot->child[flag]=*node;
	*node=pivot;
}

void take_balance(MAP map, int depth, NODE* nodes[], bool flag[]){
	for(int i=depth-1;i>=0;i--){
		int bal=balance(nodes[i]);
		if(bal>1){
			if(balance(nodes[i]->child[0])<0){
				rotate(&(nodes[i]->child[0]),0);
			}
			if(i){
				rotate(&(nodes[i-1]->child[flag[i-1]]),1);
			}else{
				rotate(&(map->root),1);
			}
		}else if(bal<-1){
			if(balance(nodes[i]->child[1])>0){
				rotate(&(nodes[i]->child[1]),1);
			}
			if(i){
				rotate(&(nodes[i-1]->child[flag[i-1]]),0);
			}else{
				rotate(&(map->root),0);
			}
		}
	}
}

void setValue(MAP map, const char* key, void* value){
	NODE* nodes[64];
	bool flag[64];
	int depth=0;
	nodes[depth]=map->root;
	while(nodes[depth]){
		int cmp=strcmp(key,nodes[depth]->key);
		if(cmp==0){
			//update処理
			nodes[depth]->value=value;
			return;
		}
		flag[depth]=(cmp>0);
		nodes[depth+1]=nodes[depth]->child[flag[depth]];//流石にnodes[++depth]=nodes[depth]->child[flag]は乱暴すぎる
		depth++;
	}
	
	/* insert処理 */
	//ノードのメモリを確保
	NODE* node=(NODE*)malloc(sizeof(NODE));
	if(!node){
		abort();
	}

	//乱暴な初期化をしてみる（keyもvalueもchild[i]（i=0,1）もNULL）
	memset(node,0,sizeof(NODE));

	//キーのメモリ確保
	node->key=(char*)malloc(strlen(key)+1);
	if(!node->key){
		abort();
	}

	//キーをセット
	strcpy(node->key,key);

	//値をセット
	node->value=value;

	nodes[depth]=node;
	if(depth){
		nodes[depth-1]->child[flag[depth-1]]=node;
	}else{
		map->root=node;
	}

	//一応、これで挿入もしくは更新できたのだが、挿入の場合、AVL木の考え方を用いて二分探索木の平衡性を保つことにする。
	//（その為に、`nodes`に根から辿っていったノードを格納しておいた）
	take_balance(map, depth, nodes, flag);
}

/*
 * 値を取得する
 * map : 連想配列
 * key : 探索キー
 */
void* getValue(MAP map, const char* key){
	NODE* node=map->root;
	while(node){
		int cmp=strcmp(key,node->key);
		if(cmp==0){
			return node->value;
		}
		node=node->child[cmp>0];
	}

	//キーが無ければNULL
	return NULL;
}

/*
 * ノード内のキー・値に対して通りがけ順（左⇒親⇒右）で処理
 */
void _foreach(void (*func)(const char* key, const void* value), NODE* node){
	if(node){
		_foreach(func, node->child[0]);
		func(node->key, node->value);
		_foreach(func, node->child[1]);
	}
}

void foreach(MAP map, void (*func)(const char* key, const void* value)){
	_foreach(func, map->root);
}

/*
 * 連想配列内のキーを削除
 */
void* erase(MAP map, const char* key){
	NODE* nodes[64];
	bool flag[64];
	int depth=0;
	nodes[depth]=map->root;
	while(nodes[depth]){
		int cmp=strcmp(key,nodes[depth]->key);
		if(cmp){
			flag[depth]=(cmp>0);
			nodes[depth+1]=nodes[depth]->child[flag[depth]];
			depth++;
			continue;
		}

		//削除対象ノード
		NODE* node=nodes[depth];

		//値を退避
		void* value=node->value;
		
		/* delete処理 */
		if(node->child[0] && node->child[1]){//削除対象ノードの左右の子が存在
			//削除対象ノードの左の右の右の…右のノード（末端ノード）を取得
			flag[depth]=0;
			nodes[depth+1]=node->child[0];
			depth++;
			while(nodes[depth]->child[1]){
				flag[depth]=1;
				nodes[depth+1]=nodes[depth]->child[1];
				depth++;
			}
			
			//末端ノードのキーと値を削除対象ノードに移す
			free(node->key);
			node->key=nodes[depth]->key;
			node->value=nodes[depth]->value;

			//末端ノードの親の右を付け替える
			nodes[depth-1]->child[flag[depth-1]]=nodes[depth]->child[0];

			//末端ノードの解放
			free(nodes[depth]);
		}else{
			if(node->child[0]){//削除対象ノードの左の子が存在
				if(depth){
					nodes[depth-1]->child[flag[depth-1]]=node->child[0];
				}else{
					map->root=node->child[0];
				}
				
			}else if(node->child[1]){//削除対象ノードの右の子が存在
				if(depth){
					nodes[depth-1]->child[flag[depth-1]]=node->child[1];
				}else{
					map->root=node->child[1];
				}
			}else{
				if(depth){
					nodes[depth-1]->child[flag[depth-1]]=NULL;
				}else{
					map->root=NULL;
				}
			}
			free(node->key);
			free(node);
		}
		nodes[depth]=NULL;

		//末端ノードの前から根に向かって平衡性を保つように処理
		take_balance(map, depth, nodes, flag);
		return value;
	}

	return NULL;
}

/*
 * 連想配列のノードを解放
 * 右⇒左⇒親の順で解放
 */
void _clear(NODE* node, int flag){
	if(node){
		_clear(node->child[1],flag);
		_clear(node->child[0],flag);
		if(flag)free(node->value);
		free(node->key);
		free(node);
	}
}

/*
 * 連想配列を初期化
 */
void clear(MAP map, int flag){
	_clear(map->root,flag);
	map->root=NULL;
}
