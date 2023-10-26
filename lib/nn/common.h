#ifndef FIONA_NN_COMMON_H
#define FIONA_NN_COMMON_H

#include "math/all.h"
#include <string.h>

typedef enum {INFERENCE, TRAINING} stage_t;


void array_init(elem_t *y, size_t y_size, elem_t default_val);

void conv2d_shape(size_t *y_size, size_t *y_rows, size_t *y_cols, size_t batch_size, size_t x_rows, size_t x_cols,
    size_t channel_in, size_t channel_out, size_t kernel_size, size_t stride=1, size_t padding=0);

void padding2d_shape(size_t *size_padded, size_t *rows_padded, size_t *cols_padded,
    size_t padding, size_t rows, size_t cols, size_t channels=1, size_t batch_size=1);
void padding2d(elem_t *y_padded, const elem_t *y, size_t padding, elem_t pad_val, size_t rows, size_t cols);
void padding2d(elem_t *y_padded, const elem_t *y, size_t padding, elem_t pad_val, size_t rows, size_t cols, size_t channels);
void padding2d(elem_t *y_padded, const elem_t *y, size_t padding, elem_t pad_val, size_t rows, size_t cols, size_t channels, size_t batch_size);

void pooling2d_shape(size_t *y_size, size_t *y_rows, size_t *y_cols, size_t x_rows, size_t x_cols, size_t channel_size, size_t batch_size, 
    size_t kernel_size, size_t padding=0, size_t stride=1);

#endif /* FIONA_NN_COMMON_H */