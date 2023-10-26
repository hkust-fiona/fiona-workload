#include "fiona.h"
#include "utils/pprint.h"
#include <iostream>

/************************ TEST [vector_max] ***********************/
void test_tiled_matrix_vector_max() {
    print_sep();
    std::cout << __func__ << std::endl;

    int R = 7, C = 61;
    elem_t mat[R][C];
    for(auto i = 0; i < R; ++i) {
        for(auto j = 0; j < C; ++j) {
            mat[i][j] = - i + j;
        }
    }

    elem_t val[R];
    tiled_matrix_vector_max(&val[0], &mat[0][0], R, C);
    printf("mat = "); print_mat(&mat[0][0], R, C);
    printf("result = "); print_vec(&val[0], R);
}

/************************ TEST [vector_argmax] ***********************/
void test_matrix_vector_argmax() {
    print_sep();
    std::cout << __func__ << std::endl;

    int R = 7, C = 61;
    elem_t mat[R][C];
    for(auto i = 0; i < R; ++i) {
        for(auto j = 0; j < C; ++j) {
            mat[i][j] = j % i;
        }
    }

    elem_t val[R];
    matrix_vector_argmax(&val[0], &mat[0][0], R, C);
    printf("mat = "); print_mat(&mat[0][0], R, C);
    printf("result = "); print_vec(&val[0], R);
}



int main() {
    test_tiled_matrix_vector_max();
    test_matrix_vector_argmax();

    return 0;
}