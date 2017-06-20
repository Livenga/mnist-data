#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


/** エラー表示
 * @strm:  出力先
 * @fn:    関数名
 * @param: パラメータ
 */
int
eprintf(FILE *strm,
    const char *fn,
    const char *param)
{ /* {{{ */
  extern int errno;

  if(param != NULL)
    return fprintf(strm, "%s: %s %s\n",
        fn, param, strerror(errno));
  return fprintf(strm, "%s: %s\n",
      fn, strerror(errno));
} /* }}} */
