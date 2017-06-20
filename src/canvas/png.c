#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <png.h>

#include "../../include/util.h"
#include "../../include/type.h"


/** struct canvas の書き込み
 * @png_path: 書き込み PNG パス
 * @png_canvas: struct canva データ
 */
int
pnwrite(const char *png_path,
    const struct canvas png_canvas)
{ /* {{{ */
  int i;

  FILE          *png_fp;
  png_structp   png_ptr;
  png_infop     png_info;
  unsigned char **png_data;

  if((png_fp = fopen(png_path, "wb")) == NULL) {
    eprintf(stderr, "fopen(3)", png_path);
    return EOF;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_info = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, png_fp);

  png_set_IHDR(png_ptr, png_info,
      png_canvas.width, png_canvas.height, 8,
      PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);


  png_data = (unsigned char **)calloc(
      png_canvas.height, sizeof(unsigned char *));

  for(i = 0; i < png_canvas.height; i++) {
    png_data[i] = (unsigned char *)calloc(png_canvas.width, sizeof(unsigned char));

    memmove((void *)png_data[i],
        (const void *)(png_canvas.data + (i * png_canvas.height)),
        sizeof(unsigned char) * png_canvas.width);
  }

  png_write_info(png_ptr, png_info);
  png_write_image(png_ptr, (png_bytepp)png_data);
  png_write_end(png_ptr, png_info);


  for(i = 0; i < png_canvas.height; i++) {
    memset((void *)png_data[i], '\0',
        sizeof(unsigned char) * png_canvas.width);
    free((void *)png_data[i]); png_data[i] = NULL;
  }
  free((void *)png_data); png_data = NULL;

  png_destroy_info_struct(png_ptr, &png_info);
  png_destroy_write_struct(&png_ptr, &png_info);

  fclose(png_fp);
  return 0;
} /* }}} */
