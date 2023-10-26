#include "math/misc.h"

//! >>> eMISC: max
/***********************************************************************/
void fit_vector_max(elem_t *retval, const elem_t *vec, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec);
    MAX_V(*retval, 1);
}

void tiled_vector_max(elem_t *retval, const elem_t *vec, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_max().\n");
        printf("[HINT] elem_t retval;\n");
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_max(retval, vec, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        elem_t val, maxval = elem_t_min;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_max(&val, &vec[index], EU_VEC_ELEM);
            if(val > maxval) maxval = val;
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_max(&val, &vec[offset], remainder);
            if(val > maxval) maxval = val;
        }
        *retval = maxval;
    }
}

void tiled_matrix_vector_max(elem_t *retval, const elem_t *mat, size_t rows, size_t cols) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_vector_max().\n");
        printf("[HINT] elem_t retval[rows=%d];\n", rows);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_max(&retval[i], &mat[i * cols], cols);
    }
}

//! >>> eMISC: min
/***********************************************************************/
void fit_vector_min(elem_t *retval, const elem_t *vec, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec);
    MIN_V(*retval, 1);
}

void tiled_vector_min(elem_t *retval, const elem_t *vec, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_min().\n");
        printf("[HINT] elem_t retval;\n");
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_min(retval, vec, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        elem_t val, minval = elem_t_max;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_min(&val, &vec[index], EU_VEC_ELEM);
            if(val < minval) minval = val;
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_min(&val, &vec[offset], remainder);
            if(val < minval) minval = val;
        }
        *retval = minval;
    }
}

void tiled_matrix_vector_min(elem_t *retval, const elem_t *mat, size_t rows, size_t cols) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_vector_min().\n");
        printf("[HINT] elem_t retval[rows=%d];\n", rows);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_min(&retval[i], &mat[i * cols], cols);
    }
}

//! >>> helper: dropout
/***********************************************************************/
void fit_vector_dropout(elem_t *retval, const elem_t *vec, const elem_t mask, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    LOAD_V(11, vec);
    SET_VLEN(vlen);
    SET_VMASK(11, mask);
    ADD_V(11, 11, 0);
    SET_VMASK(11, -1);
}

//! >>> helper: argmax
/***********************************************************************/
void vector_argmax(elem_t *retval, const elem_t *vec, size_t vlen) {
    elem_t maxval;
    tiled_vector_max(&maxval, vec, vlen);
    size_t i = 0;
    for(i = 0; i < vlen; ++i) {
        if(maxval == vec[i]) break;
    }
    *retval = i;
}

void matrix_vector_argmax(elem_t *retval, const elem_t *mat, size_t rows, size_t cols) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: matrix_vector_argmax().\n");
        printf("[HINT] elem_t retval[rows=%d];\n", rows);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        vector_argmax(&retval[i], &mat[i * cols], cols);
    }
}

//! >>> helper: reshape
/***********************************************************************/
void vector_shift(elem_t *vec, size_t vlen, size_t bit_shift, direction_t direction) {
    // @direction: LEFT - left shift, RIGHT - right shift
    if(bit_shift == 0) return;
    if(vec == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: vec_shift().\n");
        printf("[HINT] elem_t vec[rows=%d];\n", vlen);
        exit(-1);
    }
    if(direction == RIGHT) { for(size_t i = 0; i < vlen; ++i) { vec[i] >>= bit_shift; } } 
    else { for(size_t i = 0; i < vlen; ++i) { vec[i] <<= bit_shift; } }
}

void mat_transpose(elem_t *mat_T, const elem_t *mat, size_t rows, size_t cols) {
    // row-major storage
    if(mat_T == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: mat_transpose().\n");
        printf("[HINT] elem_t mat_T[rows=%d][cols=%d];\n", cols, rows);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        for(size_t j = 0; j < cols; ++j) {
            auto index = i * cols + j;
            auto index_T = j * rows + i;
            mat_T[index_T] = mat[index];
        }
    }
}
