#ifndef FIONA_PHOTONIC_ALU_H
#define FIONA_PHOTONIC_ALU_H

#include "base/config.h"
#include "base/instr.h"

void fit_dotprod(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen);
void tiled_dotprod(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen);
void tiled_mvm(elem_t *retval, const elem_t *mat, const elem_t *vec, size_t rows, size_t cols);
void tiled_matmul_transpose(elem_t *retval, const elem_t *mat1, const elem_t *mat2_T, size_t I, size_t J, size_t K);

#endif /* FIONA_PHOTONIC_ALU_H */