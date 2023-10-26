#include "math/contrib.h"
#include <math.h>

/************************ VECTOR ***********************/
void vector_equal(elem_t *ret_bool, const elem_t *vec1, const elem_t *vec2, size_t vlen) {
    if(ret_bool == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: vector_equal().\n");
        printf("[HINT] elem_t ret_bool[vlen=%d];\n", vlen);
        exit(-1);
    }
    for(size_t i = 0; i < vlen; ++i) {
        if(vec1[i] == vec2[i]) {
            ret_bool[i] = 1;
        } else {
            ret_bool[i] = 0;
        }
    }
}

void vector_sum(elem_t *retval, const elem_t *vec, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: vector_sum().\n");
        printf("[HINT] elem_t retval;\n");
        exit(-1);
    }
    elem_t sum = 0;
    for(size_t i = 0; i < vlen; ++i) {
        sum += vec[i];
    }
    *retval = sum;
}

void vector_mean(elem_t *retval, const elem_t *vec, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: vector_mean().\n");
        printf("[HINT] elem_t retval;\n");
        exit(-1);
    }
    elem_t sum = 0;
    vector_sum(&sum, vec, vlen);
    *retval = sum / vlen;
}

void vector_var(elem_t *retval, const elem_t *vec, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: vector_var().\n");
        printf("[HINT] elem_t retval;\n");
        exit(-1);
    }
    elem_t mean = 0;
    elem_t *tmp = new elem_t[vlen];
    vector_mean(&mean, vec, vlen);
    tiled_vector_sub_scalar(tmp, vec, mean, vlen);
    tiled_dotprod(retval, tmp, tmp, vlen);
}

void vector_softmax(elem_t *retval, const elem_t *vec, size_t vlen, elem_t factor=100) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: vector_softmax().\n");
        printf("[HINT] elem_t retval;\n");
        exit(-1);
    }
    elem_t maxval;
    tiled_vector_max(&maxval, vec, vlen);
    tiled_vector_sub_scalar(retval, vec, maxval, vlen);
    double exp_sum = 0.0;
    for(size_t i = 0; i < vlen; ++i) {
        exp_sum += exp(retval[i]);
    }
    for(size_t i = 0; i < vlen; ++i) {
        retval[i] = retval[i] * factor / exp_sum;
    }
}

/************************ MATRIX ***********************/
void matrix_sum(elem_t *retval, const elem_t *mat, size_t rows, size_t cols) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: matrix_sum().\n");
        printf("[HINT] elem_t retval;\n");
        exit(-1);
    }
    elem_t sum = 0, tmp = 0;
    for(size_t i = 0; i < rows; ++i) {
        vector_sum(&tmp, &mat[rows * i], cols);
        sum += tmp;
    }
    *retval = sum;
}

void matrix_sum(elem_t *retval, const elem_t *mat, size_t rows, size_t cols, size_t channel_size) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: matrix_sum().\n");
        printf("[HINT] elem_t retval;\n");
        exit(-1);
    }
    elem_t sum = 0, tmp = 0;
    for(size_t i = 0; i < channel_size; ++i) {
        matrix_sum(&tmp, &mat[channel_size * i], rows, cols);
        sum += tmp;
    }
    *retval = sum;
}

void matrix_mean(elem_t *retval, const elem_t *mat, size_t rows, size_t cols) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: matrix_mean().\n");
        printf("[HINT] elem_t retval;\n");
        exit(-1);
    }
    elem_t sum = 0;
    matrix_sum(&sum, mat, rows, cols);
    *retval = (elem_t)(sum / (rows * cols));
}

void matrix_mean(elem_t *retval, const elem_t *mat, size_t rows, size_t cols, size_t channel_size) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: matrix_mean().\n");
        printf("[HINT] elem_t retval;\n");
        exit(-1);
    }
    elem_t sum = 0;
    matrix_sum(&sum, mat, rows, cols, channel_size);
    *retval = (elem_t)(sum / (rows * cols * channel_size));
}
