#ifndef FIONA_NN_LINEAR_H
#define FIONA_NN_LINEAR_H

#include "math/all.h"

void nn_linear(elem_t *y, const elem_t *w, const elem_t *x, size_t feature_in, size_t feature_out, size_t batch_size);
void nn_linear(elem_t *y, const elem_t *w, const elem_t *x, const elem_t *b, size_t feature_in, size_t feature_out, size_t batch_size);

#endif /* FIONA_NN_LINEAR_H */