#include "utils/pprint.h"

static uint64_t read_cycles() {
    uint64_t cycles;
    asm volatile ("rdcycle %0" : "=r" (cycles));
    return cycles;
}

/************************ PRINT ***********************/
void print_sep() {
    printf("==========================================\n");
}

void print_vec(const elem_t *array, size_t len) {
    printf("[ ");
    for(auto i = 0; i < len-1; ++i) {
        printf("%d, ", array[i]);
    }
    printf("%d ]\n", array[len-1]);
}

void print_mat(const elem_t *array, size_t rows, size_t cols) {
    for(auto i = 0; i < rows; ++i) {
        printf("[ ");
        for(auto j = 0; j < cols - 1; ++j) {
            printf("%d, ", array[i*cols+j]);
        }
        printf((i==rows-1)?"%d ]":"%d ],\n", array[i*cols+cols-1]);
    }
}

void print_mat(const elem_t *array, size_t rows, size_t cols, size_t chns) {
    const size_t elem_per_channel = rows * cols;
    for(auto i = 0; i < chns; ++i) {
        printf("[ ");
        print_mat(&array[elem_per_channel*i], rows, cols);
        printf((i==chns-1)?" ]\n":" ],\n\n");
    }
}

void print_mat(const elem_t *array, size_t rows, size_t cols, size_t chns, size_t batch_size) {
    const size_t elem_per_batch = rows * cols * chns;
    for(auto i = 0; i < batch_size; ++i) {
        printf("[\n");
        print_mat(&array[elem_per_batch*i], rows, cols, chns);
        printf((i==batch_size-1)?" ]\n":" ],\n\n");
    }
}
