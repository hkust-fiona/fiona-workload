#include "nn/common.h"
#include "nn/linear.h"

/******************** Linear ********************/
void nn_linear(elem_t *y, const elem_t *w, const elem_t *x, size_t feature_in, size_t feature_out, size_t batch_size) {
    // @w: feature_out * feature_in
    // @x: batch_size * feature_in
    if(y == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: nn_linear().\n");
        printf("[HINT] elem_t y[batch_size=%d][feature_out=%d];\n", batch_size, feature_out);
        exit(-1);
    }
    tiled_matmul_transpose(y, w, x, feature_out, feature_in, batch_size);
}

void nn_linear(elem_t *y, const elem_t *w, const elem_t *x, const elem_t *b, size_t feature_in, size_t feature_out, size_t batch_size) {
    // @w: feature_out * feature_in
    // @x: batch_size * feature_in
    // @b: feature_out
    if(y == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: nn_linear().\n");
        printf("[HINT] elem_t y[batch_size=%d][feature_out=%d];\n", batch_size, feature_out);
        exit(-1);
    }
    tiled_matmul_transpose(y, w, x, feature_out, feature_in, batch_size);
    tiled_matrix_vector_add(y, y, b, batch_size, feature_out);
}
