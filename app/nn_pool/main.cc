#include "fiona.h"
#include "utils/pprint.h"

static const elem_t mat2d[4][4] = {{1,2,3,4},{5,6,7,8},{-1,-2,-3,-4},{-5,-6,-7,-8}};
static const elem_t mat4d[2][3][4][4] = {{{{-3, 10, 6, -10}, {11, 6, 9, 3}, {-12, -11, -1, -11}, {-2, 10, 10, 8}}, {{-12, -3, 0, -2}, {8, -14, 13, 3}, {-10, 3, 10, 0}, {-1, -1, -12, -3}}, {{4, -2, -1, 10}, {10, 14, -6, 0}, {-11, -3, -9, -7}, {-2, -1, -3, -2}}}, {{{0, -10, 0, 0}, {4, 11, -8, 9}, {-1, 9, 5, -11}, {-12, -13, -5, -9}}, {{-11, 4, -8, -8}, {9, -12, -5, 1}, {-8, -2, 11, -11}, {3, -10, -13, 1}}, {{-3, 5, -5, -3}, {3, 14, 6, 8}, {2, 8, 5, -6}, {-2, 3, 3, 0}}}};


int main() {
    // display for testbench info
    printf("------------- FIONA NN Test -------------\n");
    printf("  *type: pooling (maxpooling2d)\n");

    size_t pooled_size, pooled_rows, pooled_cols;
    size_t padding = 1, rows = 4, cols = 4, channels = 3, batch_size = 2, kernel_size = 2;

    // --------------------------------------------
    pooling2d_shape(&pooled_size, &pooled_rows, &pooled_cols, rows, cols, 1, 1, kernel_size, padding);
    elem_t mat2d_pooled[pooled_rows][pooled_cols];
    nn_maxpooling2d(&mat2d_pooled[0][0], &mat2d[0][0], rows, cols, 1, 1, kernel_size, padding);

    printf("\nmatrix 2d before pooling: \n");
    print_mat(&mat2d[0][0], rows, cols);

    printf("\nmatrix 2d after pooling: \n");
    print_mat(&mat2d_pooled[0][0], pooled_rows, pooled_cols);

    printf("\n\n");

    // --------------------------------------------
    pooling2d_shape(&pooled_size, &pooled_rows, &pooled_cols, rows, cols, channels, batch_size, kernel_size, padding);
    elem_t mat4d_pooled[batch_size][channels][pooled_rows][pooled_cols];
    nn_maxpooling2d(&mat4d_pooled[0][0][0][0], &mat4d[0][0][0][0], rows, cols, channels, batch_size, kernel_size, padding);

    printf("\nmatrix 4d before padding: \n");
    print_mat(&mat4d[0][0][0][0], rows, cols, channels, batch_size);

    printf("\nmatrix 4d after padding: \n");
    print_mat(&mat4d_pooled[0][0][0][0], pooled_rows, pooled_cols, channels, batch_size);
    DUMP_STAT;

    return 0;
}
