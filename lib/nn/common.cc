#include "nn/common.h"

/************************ INITIALIZATION ***********************/
void array_init(elem_t *y, size_t y_size, elem_t default_val=0) {
    for(size_t i = 0; i < y_size; ++i) {
        y[i] = default_val;
    }
}

/************************ CONVOLUTION ***********************/
void conv2d_shape(size_t *y_size, size_t *y_rows, size_t *y_cols, size_t batch_size, size_t x_rows, size_t x_cols,
    size_t channel_in, size_t channel_out, size_t kernel_size, size_t stride, size_t padding) {
    
    size_t rows = size_t((x_rows + 2 * padding - (kernel_size - 1) - 1) / stride) + 1;
    size_t cols = size_t((x_cols + 2 * padding - (kernel_size - 1) - 1) / stride) + 1;

    *y_size = batch_size * channel_out * rows * cols;
    *y_rows = rows;
    *y_cols = cols;
}

/************************ PADDING ***********************/
void padding2d_shape(size_t *size_padded, size_t *rows_padded, size_t *cols_padded,
    size_t padding, size_t rows, size_t cols, size_t channels, size_t batch_size) {
    *rows_padded = rows + padding * 2;
    *cols_padded = cols + padding * 2;
    *size_padded = (*rows_padded) * (*cols_padded) * channels * batch_size;
}

void padding2d(elem_t *y_padded, const elem_t *y, size_t padding, elem_t pad_val, size_t rows, size_t cols) {
    size_t dst_index = 0, src_index = 0;
    const size_t margin_offset = padding * (cols + 2 * padding);
    for(size_t i = 0; i < margin_offset; ++i) y_padded[dst_index + i] = pad_val;
    dst_index += margin_offset;
    for(size_t i = 0; i < rows; ++i) {
        for(size_t j = 0; j < padding; ++j) y_padded[dst_index + j] = pad_val;
        dst_index += padding;
        memcpy(&y_padded[dst_index], &y[src_index], cols * sizeof(elem_t));
        dst_index += cols;
        src_index += cols;
        for(size_t j = 0; j < padding; ++j) y_padded[dst_index + j] = pad_val;
        dst_index += padding;
    }
    for(size_t i = 0; i < margin_offset; ++i) y_padded[dst_index + i] = pad_val;
    dst_index += margin_offset;
}

void padding2d(elem_t *y_padded, const elem_t *y, size_t padding, elem_t pad_val, size_t rows, size_t cols, size_t channels) {
    const size_t dst_size_per = (rows + padding * 2) * (cols + padding * 2);
    const size_t src_size_per = rows * cols;
    for(size_t i = 0; i < channels; ++i) {
        padding2d(&y_padded[dst_size_per * i], &y[src_size_per * i], padding, pad_val, rows, cols);
    }
}

void padding2d(elem_t *y_padded, const elem_t *y, size_t padding, elem_t pad_val, size_t rows, size_t cols, size_t channels, size_t batch_size) {
    const size_t dst_size_per = (rows + padding * 2) * (cols + padding * 2) * channels;
    const size_t src_size_per = rows * cols * channels;
    for(size_t i = 0; i < batch_size; ++i) {
        padding2d(&y_padded[dst_size_per * i], &y[src_size_per * i], padding, pad_val, rows, cols, channels);
    }
}

/************************ POOLING ***********************/
void pooling2d_shape(size_t *y_size, size_t *y_rows, size_t *y_cols, size_t x_rows, size_t x_cols, size_t channel_size, size_t batch_size, 
    size_t kernel_size, size_t padding, size_t stride) {
    if(stride == 0) stride = kernel_size;
    size_t padded_size, padded_rows, padded_cols;
    padding2d_shape(&padded_size, &padded_rows, &padded_cols, padding, x_rows, x_cols, channel_size, batch_size);

    *y_rows = size_t((padded_rows - kernel_size) / stride) + 1;
    *y_cols = size_t((padded_cols - kernel_size) / stride) + 1;
    *y_size = (*y_rows) * (*y_cols) * channel_size * batch_size;
}
