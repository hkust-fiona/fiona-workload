#include "math/ealu.h"

//! >>> eALU: add
/***********************************************************************/
void fit_vector_add(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec1);
    LOAD_V(2, vec2);
    ADD_V(3, 1, 2);
    STORE_V(3, retval);
}

void tiled_vector_add(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_add().\n");
        printf("[HINT] elem_t retval[vlen=%d];\n", vlen);
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_add(retval, vec1, vec2, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_add(&retval[index], &vec1[index], &vec2[index], EU_VEC_ELEM);
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_add(&retval[offset], &vec1[offset], &vec2[offset], remainder);
        }
    }
}

void tiled_matrix_vector_add(elem_t *retval, const elem_t *mat, const elem_t *vec, size_t rows, size_t vlen) {
    // >>> [add vec to each row of mat] <<<
    // @mat: rows * vlen
    // @vec: vlen
    // @retval: rows * vlen
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_vector_add().\n");
        printf("[HINT] elem_t retval[rows=%d][vlen=%d];\n", rows, vlen);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_add(&retval[i * vlen], &mat[i * vlen], &vec[0], vlen);
    }
}

//! >>> eALU: sub
/***********************************************************************/
void fit_vector_sub(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec1);
    LOAD_V(2, vec2);
    SUB_V(3, 1, 2);
    STORE_V(3, retval);
}

void tiled_vector_sub(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_sub().\n");
        printf("[HINT] elem_t retval[vlen=%d];\n", vlen);
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_sub(retval, vec1, vec2, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_sub(&retval[index], &vec1[index], &vec2[index], EU_VEC_ELEM);
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_sub(&retval[offset], &vec1[offset], &vec2[offset], remainder);
        }
    }
}

void tiled_matrix_vector_sub(elem_t *retval, const elem_t *mat, const elem_t *vec, size_t rows, size_t vlen) {
    // >>> [add vec to each row of mat] <<<
    // @mat: rows * vlen
    // @vec: vlen
    // @retval: rows * vlen
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_vector_sub().\n");
        printf("[HINT] elem_t retval[rows=%d][vlen=%d];\n", rows, vlen);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_sub(&retval[i * vlen], &mat[i * vlen], &vec[0], vlen);
    }
}

//! >>> eALU: add scalar
/***********************************************************************/
void fit_vector_add_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec);
    ADD_VS(2, scalar, 1);
    STORE_V(3, retval);
}

void tiled_vector_add_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_add_scalar().\n");
        printf("[HINT] elem_t retval[vlen=%d];\n", vlen);
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_add_scalar(retval, vec, scalar, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_add_scalar(&retval[index], &vec[index], scalar, EU_VEC_ELEM);
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_add_scalar(&retval[offset], &vec[offset], scalar, remainder);
        }
    }
}

void tiled_matrix_add_scalar(elem_t *retval, const elem_t *mat, const elem_t scalar, size_t rows, size_t vlen) {
    // >>> [add scalar to each element of mat] <<<
    // @mat: rows * vlen
    // @scalar: 1
    // @retval: rows * vlen
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_add_scalar().\n");
        printf("[HINT] elem_t retval[rows=%d][vlen=%d];\n", rows, vlen);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_add_scalar(&retval[i * vlen], &mat[i * vlen], scalar, vlen);
    }
}

//! >>> eALU: sub scalar
/***********************************************************************/
void fit_vector_sub_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec);
    SUB_VS(2, scalar, 1);
    STORE_V(3, retval);
}

void tiled_vector_sub_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_sub_scalar().\n");
        printf("[HINT] elem_t retval[vlen=%d];\n", vlen);
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_sub_scalar(retval, vec, scalar, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_sub_scalar(&retval[index], &vec[index], scalar, EU_VEC_ELEM);
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_sub_scalar(&retval[offset], &vec[offset], scalar, remainder);
        }
    }
}

void tiled_matrix_sub_scalar(elem_t *retval, const elem_t *mat, const elem_t scalar, size_t rows, size_t vlen) {
    // >>> [sub scalar to each element of mat] <<<
    // @mat: rows * vlen
    // @scalar: 1
    // @retval: rows * vlen
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_sub_scalar().\n");
        printf("[HINT] elem_t retval[rows=%d][vlen=%d];\n", rows, vlen);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_sub_scalar(&retval[i * vlen], &mat[i * vlen], scalar, vlen);
    }
}

//! >>> eALU: multiply scalar
/***********************************************************************/
void fit_vector_mul_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec);
    MUL_VS(2, scalar, 1);
    STORE_V(3, retval);
}

void tiled_vector_mul_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_mul_scalar().\n");
        printf("[HINT] elem_t retval[vlen=%d];\n", vlen);
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_mul_scalar(retval, vec, scalar, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_mul_scalar(&retval[index], &vec[index], scalar, EU_VEC_ELEM);
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_mul_scalar(&retval[offset], &vec[offset], scalar, remainder);
        }
    }
}

void tiled_matrix_mul_scalar(elem_t *retval, const elem_t *mat, const elem_t scalar, size_t rows, size_t vlen) {
    // >>> [multiply scalar to each element of mat] <<<
    // @mat: rows * vlen
    // @scalar: 1
    // @retval: rows * vlen
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_mul_scalar().\n");
        printf("[HINT] elem_t retval[rows=%d][vlen=%d];\n", rows, vlen);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_mul_scalar(&retval[i * vlen], &mat[i * vlen], scalar, vlen);
    }
}

//! >>> eALU: divide scalar
/***********************************************************************/
void fit_vector_div_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen) {
    assert(vlen <= EU_VEC_ELEM);
    SET_VLEN(vlen);
    LOAD_V(1, vec);
    DIV_VS(2, scalar, 1);
    STORE_V(3, retval);
}

void tiled_vector_div_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_vector_div_scalar().\n");
        printf("[HINT] elem_t retval[vlen=%d];\n", vlen);
        exit(-1);
    }
    if(vlen <= EU_VEC_ELEM) {
        fit_vector_div_scalar(retval, vec, scalar, vlen);
    } else {
        size_t remainder = vlen % EU_VEC_ELEM;
        size_t loop_num = vlen / EU_VEC_ELEM;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * EU_VEC_ELEM;
            fit_vector_div_scalar(&retval[index], &vec[index], scalar, EU_VEC_ELEM);
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_vector_div_scalar(&retval[offset], &vec[offset], scalar, remainder);
        }
    }
}

void tiled_matrix_div_scalar(elem_t *retval, const elem_t *mat, const elem_t scalar, size_t rows, size_t vlen) {
    // >>> [divide scalar to each element of mat] <<<
    // @mat: rows * vlen
    // @scalar: 1
    // @retval: rows * vlen
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matrix_div_scalar().\n");
        printf("[HINT] elem_t retval[rows=%d][vlen=%d];\n", rows, vlen);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_vector_div_scalar(&retval[i * vlen], &mat[i * vlen], scalar, vlen);
    }
}

