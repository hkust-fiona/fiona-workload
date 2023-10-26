#ifndef FIONA_NN_POOL_H
#define FIONA_NN_POOL_H

#include "math/all.h"

void nn_maxpooling2d(elem_t *y, const elem_t *_x, size_t rows, size_t cols, size_t channel_size, size_t batch_size,
    size_t kernel_size, size_t padding=0, size_t stride=0);

#endif /* FIONA_NN_POOL_H */