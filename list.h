#ifndef LIST_H_
#define LIST_H_

/* リスト構造体 */
typedef struct list *List;

/* コンストラクタ */
List newList(void);

/* リストに要素を追加 */
void add(List, void*);

/* リストの要素に処理を適用 */
void foreach(const List, void (*)(void*));

/* リスト解放 */
void clear(List, int);

#endif /* LIST_H_ */
