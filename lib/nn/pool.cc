#include "nn/common.h"
#include "nn/pool.h"

void nn_maxpooling2d(elem_t *y, const elem_t *_x, size_t rows, size_t cols, size_t channel_size, size_t batch_size,
    size_t kernel_size, size_t padding, size_t stride) {
    if(y == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: nn_maxpooling2d().\n");
        printf("[HINT] elem_t y[batch_size][out_channels][y_rows][y_cols];\n");
        printf("[HINT] --> generate using pooling2d_shape() in <fiona_utils.h>\n");
        exit(-1);
    }
    // stride
    assert(kernel_size > 0);
    if(stride == 0) stride = kernel_size;

    // padding
    size_t padded_size, padded_rows, padded_cols;
    padding2d_shape(&padded_size, &padded_rows, &padded_cols, padding, rows, cols, channel_size, batch_size);
    elem_t *x = new elem_t[padded_size];
    padding2d(x, _x, padding, elem_t_min, rows, cols, channel_size, batch_size);

    // pooling
    size_t pooled_sized, pooled_rows, pooled_cols;
    pooling2d_shape(&pooled_sized, &pooled_rows, &pooled_cols, rows, cols, channel_size, batch_size, kernel_size, padding, stride);

    const size_t yelem_per_channel = pooled_rows * pooled_cols;
    const size_t yelem_per_batch = channel_size * yelem_per_channel;
    const size_t xelem_per_channel = padded_rows * padded_cols;
    const size_t xelem_per_batch = channel_size * xelem_per_channel;
    for(size_t b = 0; b < batch_size; ++b) {
        size_t yoffset_batch = b * yelem_per_batch;
        size_t xoffset_batch = b * xelem_per_batch;
        for(size_t c = 0; c < channel_size; ++c) {
            size_t yoffset_channel = c * yelem_per_channel;
            size_t xoffset_channel = c * xelem_per_channel;

            for(size_t i = 0; i < pooled_rows; ++i) {
                for(size_t j = 0; j < pooled_cols; ++j) {
                    elem_t maxval = elem_t_min;
                    size_t yoffset_pixel = yoffset_batch + yoffset_channel + i * pooled_cols + j;
                    size_t xoffset_pixel = xoffset_batch + xoffset_channel + (i * padded_cols + j) * stride;

                    for(size_t p = 0; p < kernel_size; ++p) {
                        for(size_t q = 0; q < kernel_size; ++q) {
                            size_t offset_x = xoffset_pixel + p * padded_cols + q;
                            if(maxval < x[offset_x]) {
                                maxval = x[offset_x];
                            }
                        }
                    }
                    y[yoffset_pixel] = maxval;
                }
            }

        }
    }
}
