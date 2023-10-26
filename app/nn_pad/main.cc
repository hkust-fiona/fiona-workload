#include "fiona.h"
#include "utils/pprint.h"

static const elem_t mat2d[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
static const elem_t mat4d[2][3][4][4] = {{{{-3, 10, 6, -10}, {11, 6, 9, 3}, {-12, -11, -1, -11}, {-2, 10, 10, 8}}, {{-12, -3, 0, -2}, {8, -14, 13, 3}, {-10, 3, 10, 0}, {-1, -1, -12, -3}}, {{4, -2, -1, 10}, {10, 14, -6, 0}, {-11, -3, -9, -7}, {-2, -1, -3, -2}}}, {{{0, -10, 0, 0}, {4, 11, -8, 9}, {-1, 9, 5, -11}, {-12, -13, -5, -9}}, {{-11, 4, -8, -8}, {9, -12, -5, 1}, {-8, -2, 11, -11}, {3, -10, -13, 1}}, {{-3, 5, -5, -3}, {3, 14, 6, 8}, {2, 8, 5, -6}, {-2, 3, 3, 0}}}};


int main() {
    // display for testbench info
    printf("------------- FIONA NN Test -------------\n");
    printf("  *type: padding (padding2d)\n");

    size_t padded_size, padded_rows, padded_cols;
    size_t padding = 3, rows = 4, cols = 4, channels = 3, batch_size = 2;

    // --------------------------------------------
    padding2d_shape(&padded_size, &padded_rows, &padded_cols, padding, rows, cols);
    elem_t mat2d_padded[padded_rows][padded_cols];
    padding2d(&mat2d_padded[0][0], &mat2d[0][0], padding, 0, rows, cols);

    printf("\nmatrix 2d before padding: \n");
    print_mat(&mat2d[0][0], rows, cols);

    printf("\nmatrix 2d after padding: \n");
    print_mat(&mat2d_padded[0][0], padded_rows, padded_cols);

    printf("\n\n");

    // --------------------------------------------
    padding2d_shape(&padded_size, &padded_rows, &padded_cols, padding, rows, cols, channels, batch_size);
    elem_t mat4d_padded[batch_size][channels][padded_rows][padded_cols];
    padding2d(&mat4d_padded[0][0][0][0], &mat4d[0][0][0][0], padding, 0, rows, cols, channels, batch_size);

    printf("\nmatrix 4d before padding: \n");
    print_mat(&mat4d[0][0][0][0], rows, cols, channels, batch_size);

    printf("\nmatrix 4d after padding: \n");
    print_mat(&mat4d_padded[0][0][0][0], padded_rows, padded_cols, channels, batch_size);
    DUMP_STAT;

    return 0;
}
