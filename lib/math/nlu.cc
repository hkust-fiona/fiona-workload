#include "math/nlu.h"

//! >>> eNLU: relu
/***********************************************************************/
void fit_vector_relu(elem_t *retval, const elem_t *vec, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec);
    PRELU_V(2, 0, 1);
    STORE_V(2, retval);
}

void tiled_vector_relu(elem_t *retval, const elem_t *vec, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_relu().\n");
        printf("[HINT] elem_t retval[vlen=%d];\n", vlen);
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_relu(retval, vec, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_relu(&retval[index], &vec[index], EU_VEC_ELEM);
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_relu(&retval[offset], &vec[offset], remainder);
        }
    }
}

void tiled_matrix_relu(elem_t *retval, const elem_t *mat, size_t rows, size_t cols) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_relu().\n");
        printf("[HINT] elem_t retval[rows=%d][cols=%d];\n", rows, cols);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_relu(&retval[i * cols], &mat[i * cols], cols);
    }
}

//! >>> eNLU: tanh
/***********************************************************************/
void fit_vector_tanh(elem_t *retval, const elem_t *vec, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec);
    TANH_V(2, 1);
    STORE_V(2, retval);
}

void tiled_vector_tanh(elem_t *retval, const elem_t *vec, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_tanh().\n");
        printf("[HINT] elem_t retval[vlen=%d];\n", vlen);
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_tanh(retval, vec, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_tanh(&retval[index], &vec[index], EU_VEC_ELEM);
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_tanh(&retval[offset], &vec[offset], remainder);
        }
    }
}

void tiled_matrix_tanh(elem_t *retval, const elem_t *mat, size_t rows, size_t cols) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_tanh().\n");
        printf("[HINT] elem_t retval[rows=%d][cols=%d];\n", rows, cols);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_tanh(&retval[i * cols], &mat[i * cols], cols);
    }
}

//! >>> eNLU: sigmoid
/***********************************************************************/
void fit_vector_sigmoid(elem_t *retval, const elem_t *vec, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec);
    SIGMOID_V(2, 1);
    STORE_V(2, retval);
}

void tiled_vector_sigmoid(elem_t *retval, const elem_t *vec, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_sigmoid().\n");
        printf("[HINT] elem_t retval[vlen=%d];\n", vlen);
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_sigmoid(retval, vec, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_sigmoid(&retval[index], &vec[index], EU_VEC_ELEM);
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_sigmoid(&retval[offset], &vec[offset], remainder);
        }
    }
}

void tiled_matrix_sigmoid(elem_t *retval, const elem_t *mat, size_t rows, size_t cols) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_sigmoid().\n");
        printf("[HINT] elem_t retval[rows=%d][cols=%d];\n", rows, cols);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_sigmoid(&retval[i * cols], &mat[i * cols], cols);
    }
}
