#ifndef _LIST_H_
#define _LIST_H_

/* リスト構造体 */
typedef struct LIST* LIST;

/* コンストラクタ */
LIST newList(void);

/* リストに要素を追加 */
void add(LIST, void*);

/* リストの要素に処理を適用 */
void foreach(const LIST, void (*)(void*));

/* リスト解放 */
void clear(LIST, int);

#endif //_LIST_H_