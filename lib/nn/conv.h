#ifndef FIONA_NN_CONV_H
#define FIONA_NN_CONV_H

#include "math/all.h"

void nn_conv2d(elem_t *y, const elem_t *k, const elem_t *_x, size_t batch_size, size_t x_rows, size_t x_cols,
    size_t channel_in, size_t channel_out, size_t kernel_size, size_t stride=1, size_t padding=0);

#endif /* FIONA_NN_CONV_H */