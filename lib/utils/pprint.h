#ifndef FIONA_UTILS_PPRINT_H
#define FIONA_UTILS_PPRINT_H

#include "base/config.h"

void print_sep();
void print_vec(const elem_t *array, size_t len);
void print_mat(const elem_t *array, size_t rows, size_t cols);
void print_mat(const elem_t *array, size_t rows, size_t cols, size_t chns);
void print_mat(const elem_t *array, size_t rows, size_t cols, size_t chns, size_t batch_size);

#endif /* FIONA_UTILS_PPRINT_H */