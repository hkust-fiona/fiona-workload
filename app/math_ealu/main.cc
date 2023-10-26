#include "fiona.h"
#include "utils/pprint.h"
#include <iostream>

/************************ TEST [vector_add] ***********************/
void test_tiled_matrix_vector_add() {
    print_sep();
    std::cout << __func__ << std::endl;

    int R = 7, C = 61;
    elem_t mat[R][C], vec[C];
    for(auto i = 0; i < R; ++i) {
        for(auto j = 0; j < C; ++j) {
            mat[i][j] = i * C + j;
        }
    }
    for(auto i = 0; i < C; ++i) {
        vec[i] = i + 1;
    }


    elem_t val[R][C];
    tiled_matrix_vector_add(&val[0][0], &mat[0][0], &vec[0], R, C);
    printf("mat = "); print_mat(&mat[0][0], R, C);
    printf("vec = "); print_vec(&vec[0], C);
    printf("result = "); print_mat(&val[0][0], R, C);
}


void test_tiled_matrix_vector_sub() {
    print_sep();
    std::cout << __func__ << std::endl;

    int R = 7, C = 61;
    elem_t mat[R][C], vec[C];
    for(auto i = 0; i < R; ++i) {
        for(auto j = 0; j < C; ++j) {
            mat[i][j] = i * C + j;
        }
    }
    for(auto i = 0; i < C; ++i) {
        vec[i] = i * 2;
    }


    elem_t val[R][C];
    tiled_matrix_vector_sub(&val[0][0], &mat[0][0], &vec[0], R, C);
    printf("mat = "); print_mat(&mat[0][0], R, C);
    printf("vec = "); print_vec(&vec[0], C);
    printf("result = "); print_mat(&val[0][0], R, C);
}



int main() {
    test_tiled_matrix_vector_add();
    test_tiled_matrix_vector_sub();

    return 0;
}