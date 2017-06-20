#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/canvas.h"
#include "../include/mnist.h"
#include "../include/util.h"



int
main(int argc,
     char *argv[])
{
  FILE   *label_fp,        *image_fp;
  struct mnist_train_label *labels;
  struct mnist_train_image *images;
  
  int      i;
  unsigned counter[10];
  struct   canvas cv;
  char     write_path[1024];
  

  if((label_fp = fopen(MNIST_LABEL_PATH, "rb")) == NULL) {
    eprintf(stderr, "fopen(3)", MNIST_LABEL_PATH);
    return EOF;
  }

  labels = load_labels(label_fp);
  fclose(label_fp);

  if((image_fp = fopen(MNIST_IMAGE_PATH, "rb")) == NULL) {
    eprintf(stderr, "fopen(3)", MNIST_IMAGE_PATH);
    return EOF;
  }
  images = load_images(image_fp);
  fclose(image_fp);


  // ラベルの個数と画像の個数の確認
  if(labels->number_of_items != images->number_of_images) {
    free_mnist_train_image(images); images = NULL;
    free_mnist_train_label(labels); labels = NULL;
    return EOF;
  }


  memset((void *)counter, '\0', sizeof(counter));

  // MNIST データを PNG へ変換を行う.
  cv.width  = images->columns;
  cv.height = images->rows;
  for(i = 0; i < images->number_of_images; i++) {
    memset((void *)write_path, '\0', sizeof(write_path));

    sprintf(write_path, "images/%c_%04d.png",
        labels->label[i] + '0', counter[labels->label[i]]++);

    cv.data = images->image[i];
    if(pnwrite(write_path, cv) == 0) {
      fprintf(stderr, "%6d %s: done.\n", i, write_path);
    }
  }

  free_mnist_train_image(images);
  images = NULL;
  free_mnist_train_label(labels);
  labels = NULL;

	return 0;
}
