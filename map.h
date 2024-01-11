#ifndef MAP_H_
#define MAP_H_

/* 連想配列構造体 */
typedef struct map* Map;

/* コンストラクタ */
Map newMap();

/* キーと値をセット（キーが既に存在していればupdate, 無ければinsertの役割） */
void setValue(Map map, const char* key, void* value);

/* 値を取得 */
void* getValue(Map map, const char* key);

/* 連想配列内の全てのキー、値に対して処理 */
void foreach(Map map, void (*func)(const char* key, const void* value));

/* 連想配列内のキーを削除 */
void* erase(Map map, const char* key);

/* 連想配列を初期化（プログラム終了時に忘れない!!） */
void clear(Map map, int flag);

#endif /* MAP_H_ */
