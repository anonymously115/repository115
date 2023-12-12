#include <string.h>
#include "replace.h"

/*
 * 文字列内の特定のテキストを置換する
 * dst : 置換後の文字列
 * src : 置換する文字列
 * old : 検索文字列
 * new : 置換文字列
 * 戻り値 : 置換後の文字列の先頭へのポインタ
 */
char* replace(char* dst, const char* src, const char* old, const char* new){
	if(!strcmp(old,"")){//検索文字列が空文字の場合
		//置換後の文字列に置換前の文字列をコピー
		strcpy(dst,src);
		
		//置換後の文字列（の先頭へのポインタ）を返す
		return dst;
	}

	//出力文字列を空文字列で初期化
	strcpy(dst, "");
	
	//検索文字列長
	int a=(int)strlen(old);
	
	//置換する文字列の先頭へのポインタ
	const char* c=src;

	//置換する文字列に検索文字列が含まれていれば、その部分の先頭へのポインタ（無ければNULL）
	char* s=strstr(c,old);
	
	while(s){//置換する文字列に検索文字列が含まれていた
		//検索文字列にヒットするまでの文字列を出力文字列に結合
		strncat(dst,c,s-c);

		//出力文字列に置換文字列を結合
		strcat(dst,new);

		//次の検索位置はヒットした検索文字列の末尾の次
		c=s+a;

		//次の検索文字列を探索する
		s=strstr(c,old);
	}

	//最後の検索文字列以降の文字列を出力文字列に結合する
	strcat(dst,c);

	//置換後の文字列の先頭へのポインタを返す
	return dst;
}