/* 連想配列構造体 */
typedef struct MAP* MAP;

/* コンストラクタ */
MAP newMap();

/* キーと値をセット（キーが既に存在していればupdate, 無ければinsertの役割） */
void setValue(MAP map, const char* key, void* value);

/* 値を取得 */
void* getValue(MAP map, const char* key);

/* 連想配列内の全てのキー、値に対して処理 */
void foreach(MAP map, void (*func)(const char* key, const void* value));

/* 連想配列内のキーを削除 */
void* erase(MAP map, const char* key);

/* 連想配列を初期化（プログラム終了時に忘れない!!） */
void clear(MAP map, int flag);