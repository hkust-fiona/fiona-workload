#ifndef FIONA_NONLINEAR_UNIT_H
#define FIONA_NONLINEAR_UNIT_H

#include "base/config.h"
#include "base/instr.h"

// @relu.v
void fit_vector_relu(elem_t *retval, const elem_t *vec, size_t vlen);
void tiled_vector_relu(elem_t *retval, const elem_t *vec, size_t vlen);
void tiled_matrix_relu(elem_t *retval, const elem_t *mat, size_t rows, size_t cols);

// @tanh.v
void fit_vector_tanh(elem_t *retval, const elem_t *vec, size_t vlen);
void tiled_vector_tanh(elem_t *retval, const elem_t *vec, size_t vlen);
void tiled_matrix_tanh(elem_t *retval, const elem_t *mat, size_t rows, size_t cols);

// @sigmoid.v
void fit_vector_sigmoid(elem_t *retval, const elem_t *vec, size_t vlen);
void tiled_vector_sigmoid(elem_t *retval, const elem_t *vec, size_t vlen);
void tiled_matrix_sigmoid(elem_t *retval, const elem_t *mat, size_t rows, size_t cols);

#endif /* FIONA_NONLINEAR_UNIT_H */