#ifndef _MNIST_H
#define _MNIST_H

#ifndef _TYPE_H
#include "type.h"
#endif

#define MNIST_LABEL_PATH "train-labels-idx1-ubyte"
#define MNIST_IMAGE_PATH "train-images-idx3-ubyte"


/* src/mnist.c */
extern struct mnist_train_label *
load_labels(FILE *label_fp);

extern struct mnist_train_image *
load_images(FILE *image_fp);

extern void
free_mnist_train_label(struct mnist_train_label *plabel);
extern void
free_mnist_train_image(struct mnist_train_image *pimage);
#endif
