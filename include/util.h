#ifndef _UTIL_H
#define _UTIL_H

/* src/util.c */
/** エラー表示
 * @strm:  出力先
 * @fn:    関数名
 * @param: パラメータ
 */
extern int
eprintf(FILE *strm,
    const char *fn,
    const char *param);
#endif
