#include "math/palu.h"

void fit_dotprod(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen) {
    assert(vlen <= PU_MRR_RING);
    SET_VLEN(vlen);
    LOAD_V(1, vec1);  // @x1: [v]
    LOAD_V(2, vec2);  // @x2: [v]
    DOTP(*retval, 1, 2);   // @retval: [s]
}

void tiled_dotprod(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen) {
    if(vlen <= PU_MRR_RING) {
        fit_dotprod(retval, vec1, vec2, vlen);
    } else {
        size_t remainder = vlen % PU_MRR_RING;
        size_t loop_num = vlen / PU_MRR_RING;
        elem_t sum = 0, val = 0;
        for(size_t i = 0; i < loop_num; ++i) {
            size_t index = i * PU_MRR_RING;
            fit_dotprod(&val, &vec1[index], &vec2[index], PU_MRR_RING);
            sum += val;
        }
        if(remainder > 0) {
            size_t offset = vlen - remainder;
            fit_dotprod(&val, &vec1[offset], &vec2[offset], remainder);
            sum += val;
        }
        *retval = sum;
    }
}

void tiled_mvm(elem_t *retval, const elem_t *mat, const elem_t *vec, size_t rows, size_t cols) {
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_mvm().\n");
        printf("[HINT] elem_t retval[rows=%d];\n", rows);
        exit(-1);
    }
    for(size_t i = 0; i < rows; ++i) {
        tiled_dotprod(&retval[i], &mat[i * cols], &vec[0], cols);
    }
}

void tiled_matmul_transpose(elem_t *retval, const elem_t *mat1, const elem_t *mat2_T, size_t I, size_t J, size_t K) {
    // @mat1: size I*J
    // @mat2: size J*K --> mat2_T: size K*J
    // @retval: size K*I (column-major)
    if(retval == nullptr) {
        printf("[ERROR] please allocate memory for retval before call func: tiled_matmul_transpose().\n");
        printf("[HINT] elem_t retval[K=%d][I=%d];\n", K, I);
        exit(-1);
    }
    for(size_t k = 0; k < K; ++k) {
        tiled_mvm(&retval[k * I], &mat1[0], &mat2_T[k * J], I, J);
    }
}

