#include "fiona.h"
#include "utils/pprint.h"
#include <iostream>

/************************ TEST [vector_relu] ***********************/
void test_tiled_matrix_relu() {
    print_sep();
    std::cout << __func__ << std::endl;

    int R = 7, C = 61;
    elem_t mat[R][C];
    for(auto i = 0; i < R; ++i) {
        for(auto j = 0; j < C; ++j) {
            mat[i][j] = i - j;
        }
    }

    elem_t val[R][C];
    tiled_matrix_relu(&val[0][0], &mat[0][0], R, C);
    printf("mat = "); print_mat(&mat[0][0], R, C);
    printf("result = "); print_mat(&val[0][0], R, C);
}


int main() {
    test_tiled_matrix_relu();

    return 0;
}