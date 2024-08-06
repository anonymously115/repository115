#include <string.h>
#include <stdlib.h>
#include "split.h"

int split(char *dst[], const char *src, const char *delim, const char *quote) {
	//分割後の文字列数
	int n = 0;
	//入力文字列の先頭から、区切り文字や引用符を探索
	const char *s = src;

	for (;;) { //(*1)
		//出力領域を確実に空文字列で初期化
		strcpy(dst[n], "");

		//開き引用符チェック
		char *q = strchr(quote, *s);

		if (q && *q) {		//開き引用符だった場合
			//次の引用符が閉じなのか2個続きで1個の引用符を表すのか不明なので、無限ループ処理としておく
			for (;;) {			//(*2)
				//閉じ引用符候補を探索（同じ引用符で探索。無ければSegmentation faultで落とす）
				char *c = strchr(s + 1, *s);

				//開き引用符直後から閉じ引用符直前までの文字列を結合
				strncat(dst[n], s + 1, c - s - 1);

				//閉じ引用符の次の文字
				s = c + 1;
				if (*s == *q) {				//同じ引用符が2個続いた
					//引用符を1個結合
					strncat(dst[n], s, 1);
				} else {
					//*cは閉じ引用符だったので、(*2)のループ脱出
					break;
				}
			}
			if (*s == '\0') {
				//閉じ引用符で文字列が終了した場合、(*1)のループ脱出
				break;
			}
			if (strchr(delim, *s)) {					//閉じ引用符の次が区切り文字
				//次の探索位置を進める
				s++;
			} else {
				//閉じ引用符の次が区切り文字でも終端文字でもない場合、不正
				abort();
			}
		} else {				//引用符以外
								//区切り文字の直後または文字列の先頭から、次の区切り文字を探索
			char *c = strpbrk(s, delim);

			if (!c) {			//区切り文字がない
								//残りの文字列を結合
				strcat(dst[n], s);

				//(*1)のループから脱出
				break;
			}

			//区切り文字直前までの文字列を結合
			strncat(dst[n], s, c - s);

			//次の探索位置は区切り文字の次
			s = c + 1;
		}

		//分割後の文字列数をインクリメントし、次の出力領域に格納していく
		n++;
	}				//(*1)

					//最後にインクリメントし、実際の分割後の文字列数を返す
	return ++n;
}
