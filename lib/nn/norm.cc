#include "nn/common.h"
#include "nn/norm.h"

/******************** BatchNorm2d ********************/
void nn_batchnorm2d(elem_t *y, const elem_t *x, size_t batch_size, size_t channel_size, size_t rows, size_t cols,
    BatchNormParam& bn_param, stage_t stage) {
    // @x: batch_size * channel_size * rows * cols
    // @bn_param: channel_size
    // @stage: 0 - inference, 1 - training
    if(y == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: nn_batchnorm2d().\n");
        printf("[HINT] elem_t y[batch_size=%d][channel_size=%d][rows=%d][cols=%d];\n", batch_size, channel_size, rows, cols);
        exit(-1);
    }
    const size_t pixels_per_channel = rows * cols;
    const size_t pixels_per_batch = channel_size * pixels_per_channel;
    if(stage == 0) {
        for(size_t b = 0; b < batch_size; ++b) {
            size_t batch_index = b * pixels_per_batch;
            for(size_t c = 0; c < channel_size; ++c) {
                size_t offset = batch_index + c * pixels_per_channel; 
                elem_t running_std = sqrt(bn_param.running_var[c] + bn_param.eps); 
                tiled_matrix_sub_scalar(&y[offset], &x[offset], bn_param.running_mean[c], rows, cols);
                tiled_matrix_div_scalar(&y[offset], &y[offset], running_std, rows, cols);
                tiled_matrix_mul_scalar(&y[offset], &y[offset], bn_param.weight[c], rows, cols);
                tiled_matrix_add_scalar(&y[offset], &y[offset], bn_param.bias[c], rows, cols);
            }
        }
    } else if(stage == 1) {
        printf("[ERROR] nn_batchnorm2d yet supports training.");
        exit(-1);
    }
}

/******************** LayerNorm2d ********************/
void nn_layernorm2d(elem_t *y, const elem_t *x, size_t batch_size, size_t channel_size, size_t rows, size_t cols,
    LayerNormParam& ln_param, stage_t stage) {
    // @x: batch_size * channel_size * rows * cols
    // @ln_param: batch_size
    // @stage: 0 - inference, 1 - training
    if(y == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: nn_layernorm2d().\n");
        printf("[HINT] elem_t y[batch_size=%d][channel_size=%d][rows=%d][cols=%d];\n", batch_size, channel_size, rows, cols);
        exit(-1);
    }
    const size_t pixels_per_channel = rows * cols;
    const size_t pixels_per_batch = channel_size * pixels_per_channel;
    if(stage == 0) {
        for(size_t b = 0; b < batch_size; ++b) {
            size_t batch_index = b * pixels_per_batch;
            elem_t layer_mean, layer_var;
            matrix_mean(&layer_mean, &x[batch_index], rows, cols, channel_size);
            vector_var(&layer_var, &x[batch_index], pixels_per_batch);
            elem_t layer_std = sqrt(layer_var + ln_param.eps);
            for(size_t c = 0; c < channel_size; ++c) {
                size_t offset = batch_index + c * pixels_per_channel; 
                tiled_matrix_sub_scalar(&y[offset], &x[offset], layer_mean, rows, cols);
                tiled_matrix_div_scalar(&y[offset], &y[offset], layer_std, rows, cols);
                tiled_matrix_mul_scalar(&y[offset], &y[offset], ln_param.gamma[b], rows, cols);
                tiled_matrix_add_scalar(&y[offset], &y[offset], ln_param.beta[b], rows, cols);
            }
        }
    } else if(stage == 1) {
        printf("[ERROR] nn_layernorm2d yet supports training.");
        exit(-1);
    }
}
