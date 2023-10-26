#include "fiona.h"
#include "utils/pprint.h"

// quantization bit = 5
static const elem_t mlp_fc1_weight[10][4]= {{-1, 7, -8, -5}, {-4, 5, -9, -8}, {9, -7, 7, 2}, {-3, 1, -4, 5}, {3, 8, -6, -2}, {6, -11, 7, -6}, {10, -9, 7, 5}, {-2, -1, 4, 4}, {1, -1, -8, -16}, {2, 3, -2, 5}};
static const elem_t mlp_fc2_weight[3][10]= {{10, 8, -8, 3, 3, -8, -9, -2, 11, 0}, {-8, -7, -1, 2, -5, 12, -5, -3, 11, -2}, {-2, -2, 6, 0, -6, 6, 10, -4, -16, -1}};

static const elem_t iris_test_X[30][4]= {{16, -2, 10, -4}, {10, -1, 9, -4}, {5, -2, -8, -12}, {10, -5, 4, -7}, {8, -2, 3, -8}, {14, -2, 10, -6}, {11, -2, 8, -5}, {10, -3, 5, -6}, {10, -2, 5, -8}, {11, -1, 7, -4}, {5, -1, -7, -12}, {8, 1, -6, -12}, {12, -2, 7, -5}, {16, -3, 13, -4}, {9, -3, 2, -9}, {8, 3, -7, -11}, {8, -2, 4, -7}, {5, 0, -7, -12}, {7, 0, -7, -11}, {6, 1, -6, -11}, {7, 1, -7, -12}, {5, -1, -7, -12}, {6, -1, -8, -12}, {13, -2, 9, -5}, {8, -2, 2, -8}, {10, 0, 7, -4}, {6, -1, -6, -11}, {6, 2, -7, -12}, {12, -4, 9, -6}, {11, -2, 9, -5}};
static const elem_t iris_test_Y[30]= {2, 2, 0, 1, 1, 2, 2, 2, 1, 2, 0, 0, 2, 2, 1, 0, 1, 0, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 2, 2};

int main() {
    // display for testbench info
    printf("------------- FIONA DNN -------------\n");
    printf("  *type: MLP (multi-layer perceptron)\n");
    printf("  *dataset: Iris\n");

    // variable declaration
    const size_t batch_size = 30;
    const size_t num_in = 4, num_hidden = 10, num_out = 3;

    elem_t y_fc1[batch_size][num_hidden];
    nn_linear(&y_fc1[0][0], &mlp_fc1_weight[0][0], &iris_test_X[0][0], num_in, num_hidden, batch_size);

    elem_t y_relu[batch_size][num_hidden];
    tiled_matrix_relu(&y_relu[0][0], &y_fc1[0][0], batch_size, num_hidden);

    elem_t y_fc2[batch_size][num_out];
    nn_linear(&y_fc2[0][0], &mlp_fc2_weight[0][0], &y_relu[0][0], num_hidden, num_out, batch_size);

    elem_t y_pred[batch_size];
    matrix_vector_argmax(y_pred, &y_fc2[0][0], batch_size, num_out);

    printf("[test] y_pred = ");
    print_vec(y_pred, batch_size);

    printf("[test] y_true = ");
    print_vec(iris_test_Y, batch_size);

    elem_t count_correct;
    elem_t bool_equal[batch_size];
    vector_equal(bool_equal, y_pred, iris_test_Y, batch_size);
    vector_sum(&count_correct, bool_equal, batch_size);
    
    printf("[info] test accuracy: %d / %d = %.2f%%\n", count_correct, batch_size, (float)count_correct/batch_size*100.0);

    DUMP_STAT;

    return 0;
}

