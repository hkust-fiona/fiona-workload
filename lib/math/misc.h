#ifndef FIONA_MISCELLANEOUS_H
#define FIONA_MISCELLANEOUS_H

#include "base/config.h"
#include "base/instr.h"

// @max.v
void fit_vector_max(elem_t *retval, const elem_t *vec, size_t vlen);
void tiled_vector_max(elem_t *retval, const elem_t *vec, size_t vlen);
void tiled_matrix_vector_max(elem_t *retval, const elem_t *mat, size_t rows, size_t cols);

// @min.v
void fit_vector_min(elem_t *retval, const elem_t *vec, size_t vlen);
void tiled_vector_min(elem_t *retval, const elem_t *vec, size_t vlen);
void tiled_matrix_vector_min(elem_t *retval, const elem_t *mat, size_t rows, size_t cols);

// @dropout
void fit_vector_dropout(elem_t *retval, const elem_t *vec, const elem_t mask, size_t vlen);

// @argmax
void vector_argmax(elem_t *retval, const elem_t *vec, size_t vlen);
void matrix_vector_argmax(elem_t *retval, const elem_t *mat, size_t rows, size_t cols);

// @reshape
typedef enum {LEFT, RIGHT} direction_t;
void vector_shift(elem_t *vec, size_t vlen, size_t bit_shift, direction_t direction);
void mat_transpose(elem_t *mat_T, const elem_t *mat, size_t rows, size_t cols);

#endif /* FIONA_MISCELLANEOUS_H */