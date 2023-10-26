#ifndef FIONA_MATH_CONTRIB_H
#define FIONA_MATH_CONTRIB_H

#include "base/config.h"
#include "base/instr.h"

#include "math/palu.h"
#include "math/ealu.h"
#include "math/misc.h"

// @vector
void vector_equal(elem_t *ret_bool, const elem_t *vec1, const elem_t *vec2, size_t vlen);
void vector_sum(elem_t *retval, const elem_t *vec, size_t vlen);
void vector_mean(elem_t *retval, const elem_t *vec, size_t vlen);
void vector_var(elem_t *retval, const elem_t *vec, size_t vlen);
void vector_softmax(elem_t *retval, const elem_t *vec, size_t vlen, elem_t factor);

// @matrix
void matrix_sum(elem_t *retval, const elem_t *mat, size_t rows, size_t cols);
void matrix_sum(elem_t *retval, const elem_t *mat, size_t rows, size_t cols, size_t channel_size);
void matrix_mean(elem_t *retval, const elem_t *mat, size_t rows, size_t cols);
void matrix_mean(elem_t *retval, const elem_t *mat, size_t rows, size_t cols, size_t channel_size);

#endif /* FIONA_MATH_CONTRIB_H */