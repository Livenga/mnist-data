#ifndef _TYPE_H
#define _TYPE_H

struct mnist_train_label {
  char magic[4];
  int  number_of_items;
  unsigned char *label;
};

struct mnist_train_image {
  char magic[4];
  int  number_of_images;
  int  rows;
  int  columns;
  unsigned char **image;
};


struct canvas {
  int width;
  int height;
  unsigned char *data;
};

#endif
