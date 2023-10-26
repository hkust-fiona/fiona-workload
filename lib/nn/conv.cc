#include "nn/common.h"
#include "nn/conv.h"

/******************** Conv2d ********************/
void nn_conv2d(elem_t *y, const elem_t *k, const elem_t *_x, size_t batch_size, size_t x_rows, size_t x_cols,
    size_t channel_in, size_t channel_out, size_t kernel_size, size_t stride, size_t padding) {
    // @k: (kernel_size * kernel_size) * (channel_in * channel_out)
    // @x: (x_cols * x_rows) * channel_in * batch_size
    // @y: (y_cols * y_rows) * channel_out * batch_size
    assert(stride > 0);
    if(y == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: nn_conv2d().\n");
        printf("[HINT] elem_t y[batch_size][out_channels][y_rows][y_cols];\n");
        printf("[HINT] --> generate using conv2d_shape() in <fiona_utils.h>\n");
        exit(-1);
    }
    size_t padded_size, padded_rows, padded_cols;
    padding2d_shape(&padded_size, &padded_rows, &padded_cols, padding, x_rows, x_cols, channel_in, batch_size);
    elem_t x[padded_size];
    padding2d(x, _x, padding, 0, x_rows, x_cols, channel_in, batch_size);

    size_t y_rows = size_t((x_rows + 2 * padding - (kernel_size - 1) - 1) / stride) + 1;
    size_t y_cols = size_t((x_cols + 2 * padding - (kernel_size - 1) - 1) / stride) + 1;
    
    const size_t kelem_per_chin = kernel_size * kernel_size;
    const size_t kelem_per_chout = kelem_per_chin * channel_in;
    const size_t xelem_per_channel = x_cols * x_rows;
    const size_t xelem_per_batch = xelem_per_channel * channel_in;
    const size_t yelem_per_channel = y_cols * y_rows;
    const size_t yelem_per_batch = yelem_per_channel * channel_out;

    for(size_t l = 0; l < batch_size; ++l) {
        size_t xoffset_batch = l * xelem_per_batch;
        size_t yoffset_batch = l * yelem_per_batch;

        for(size_t m = 0; m < channel_out; ++m) {
            size_t koffset_chout = m * kelem_per_chout;
            size_t yoffset_chout = m * yelem_per_channel;
            for(size_t n = 0; n < channel_in; ++n) {
                size_t koffset_chin = n * kelem_per_chin;
                size_t xoffset_chin = n * xelem_per_channel;

                for(size_t r = 0; r < y_rows; ++r){
                    for(size_t c = 0; c < y_cols; ++c) {
                        size_t xoffset_pixel = (r * x_cols + c) * stride;
                        size_t yoffset_pixel = r * y_cols + c;

                        size_t y_index = yoffset_batch + yoffset_chout + yoffset_pixel;
                        
                        for(size_t s = 0; s < kernel_size; ++s) {
                            size_t k_index = koffset_chout + koffset_chin + kernel_size * s;
                            size_t x_index = xoffset_batch + xoffset_chin + xoffset_pixel + x_cols * s;

                            elem_t val;
                            tiled_dotprod(&val, &k[k_index], &x[x_index], kernel_size);
                            y[y_index] += val;
                        }
                    }
                }

            }
        }

    }
}
