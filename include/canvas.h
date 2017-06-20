#ifndef _CANVAS_H

#ifndef _TYPE_H
#include "type.h"
#endif


/* src/canvas/png.c */
/** struct canvas の書き込み
 * @png_path: 書き込み PNG パス
 * @png_canvas: struct canva データ
 */
extern int
pnwrite(const char *png_path,
    const struct canvas png_canvas);

#endif
