#ifndef FIONA_ELECTRONIC_ALU_H
#define FIONA_ELECTRONIC_ALU_H

#include "base/config.h"
#include "base/instr.h"

// @add.v
void fit_vector_add(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen);
void tiled_vector_add(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen);
void tiled_matrix_vector_add(elem_t *retval, const elem_t *mat, const elem_t *vec, size_t rows, size_t vlen);

// @sub.v
void fit_vector_sub(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen);
void tiled_vector_sub(elem_t *retval, const elem_t *vec1, const elem_t *vec2, size_t vlen);
void tiled_matrix_vector_sub(elem_t *retval, const elem_t *mat, const elem_t *vec, size_t rows, size_t vlen);

// @add.vs
void fit_vector_add_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen);
void tiled_vector_add_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen);
void tiled_matrix_add_scalar(elem_t *retval, const elem_t *mat, const elem_t scalar, size_t rows, size_t vlen);

// @sub.vs
void fit_vector_sub_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen);
void tiled_vector_sub_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen);
void tiled_matrix_sub_scalar(elem_t *retval, const elem_t *mat, const elem_t scalar, size_t rows, size_t vlen);

// @mul.vs
void fit_vector_mul_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen);
void tiled_vector_mul_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen);
void tiled_matrix_mul_scalar(elem_t *retval, const elem_t *mat, const elem_t scalar, size_t rows, size_t vlen);

// @div.vs
void fit_vector_div_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen);
void tiled_vector_div_scalar(elem_t *retval, const elem_t *vec, const elem_t scalar, size_t vlen);
void tiled_matrix_div_scalar(elem_t *retval, const elem_t *mat, const elem_t scalar, size_t rows, size_t vlen);


#endif /* FIONA_ELECTRONIC_ALU_H */