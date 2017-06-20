#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/util.h"
#include "../include/type.h"

#define MSB2LSB32(m) \
  ((m >> 24) & 0x000000FF) + \
  ((m >>  8) & 0x0000FF00) + \
  ((m <<  8) & 0x00FF0000) + \
  ((m << 24) & 0xFF000000)


struct mnist_train_label *
load_labels(FILE *label_fp)
{ /* {{{ */
  int    nlabel;
  size_t nbyte;
  struct mnist_train_label *label;


  label = (struct mnist_train_label *)calloc
    (1, sizeof(struct mnist_train_label));
  if(label == NULL) {
    eprintf(stderr, "calloc(3)", NULL);
    return NULL;
  }

  nbyte = fread((void *)label->magic, sizeof(char), 4, label_fp);
  if(nbyte < 0) {
    eprintf(stderr, "fread(3)", NULL);

    free((void *)label); label = NULL;
    return NULL;
  }

  nbyte = fread((void *)&nlabel, sizeof(char), 4, label_fp);
  if(nbyte < 0) {
    eprintf(stderr, "fread(3)", NULL);
    
    free((void *)label); label = NULL;
    return NULL;
  }

  label->number_of_items = MSB2LSB32(nlabel);

  label->label = (unsigned char *)calloc
    (label->number_of_items, sizeof(unsigned char));

  nbyte = fread((void *)label->label, sizeof(unsigned char),
      label->number_of_items, label_fp);

  return label;
} /* }}} */


struct mnist_train_image *
load_images(FILE *image_fp)
{ /* {{{ */
  int    i, n, size;
  size_t nbyte;
  struct mnist_train_image *images = NULL;

  images = (struct mnist_train_image *)calloc
    (1, sizeof(struct mnist_train_image));


  nbyte = fread((void *)images->magic, sizeof(char), 4, image_fp);
  if(nbyte < 0) {
    eprintf(stderr, "fread(3)", NULL);

    free((void *)images); images = NULL;
    return NULL;
  }

  nbyte = fread((void *)&n, sizeof(char), 4, image_fp);
  if(nbyte < 0) {
    eprintf(stderr, "fread(3)", NULL);

    free((void *)images); images = NULL;
    return NULL;
  }

  images->number_of_images = MSB2LSB32(n);

  nbyte = fread((void *)&n, sizeof(char), 4, image_fp);
  images->rows = MSB2LSB32(n);

  nbyte = fread((void *)&n, sizeof(char), 4, image_fp);
  images->columns = MSB2LSB32(n);


  images->image = (unsigned char **)calloc
    (images->number_of_images, sizeof(unsigned char *));


  size = images->rows * images->columns;

  for(i = 0; i < images->number_of_images; i++) {
    images->image[i] = (unsigned char *)calloc(size, sizeof(unsigned char));

    nbyte = fread((void *)images->image[i],
        sizeof(unsigned char), size, image_fp);
  }

  return images;
} /* }}} */


void
free_mnist_train_label(struct mnist_train_label *plabel)
{ /* {{{ */
  memset((void *)plabel->label, '\0',
      sizeof(unsigned char) * plabel->number_of_items);
  free((void *)plabel->label);
  plabel->label = NULL;

  memset((void *)plabel, '\0', sizeof(struct mnist_train_label));
  free((void *)plabel);
  plabel = NULL;
} /* }}} */


void
free_mnist_train_image(struct mnist_train_image *pimage)
{ /* {{{ */
  int i, size;

  size = pimage->rows * pimage->columns;
  for(i = 0; i < pimage->number_of_images; i++) {
    memset((void *)pimage->image[i], '\0', size);
    free((void *)pimage->image[i]); pimage->image[i] = NULL;
  }
  free((void *)pimage->image);

  memset((void *)pimage, '\0', sizeof(struct mnist_train_image));
  free((void *)pimage); pimage = NULL;
} /* }}} */
