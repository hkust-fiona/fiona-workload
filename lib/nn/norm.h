#ifndef FIONA_NN_NORM_H
#define FIONA_NN_NORM_H

#include "math/all.h"

struct BatchNormParam {
    elem_t *weight;
    elem_t *bias;
    elem_t *running_mean;
    elem_t *running_var;
    float eps;
    float momentum;

    BatchNormParam(size_t channel_size) {
        this->eps = 1e-5;
        this->momentum = 0.1;

        this->weight = new elem_t[channel_size];
        this->bias = new elem_t[channel_size];
        this->running_mean = new elem_t[channel_size];
        this->running_var = new elem_t[channel_size];
    }
};

struct LayerNormParam {
    elem_t *gamma;
    elem_t *beta;
    float eps;

    LayerNormParam(size_t batch_size) {
        this->eps = 1e-10;

        this->gamma = new elem_t[batch_size];
        this->beta = new elem_t[batch_size];
    }
};


void nn_batchnorm2d(elem_t *y, const elem_t *x, size_t batch_size, size_t channel_size, size_t rows, size_t cols,
    BatchNormParam& bn_param, stage_t stage);

void nn_layernorm2d(elem_t *y, const elem_t *x, size_t batch_size, size_t channel_size, size_t rows, size_t cols,
    LayerNormParam& ln_param, stage_t stage);

#endif /* FIONA_NN_NORM_H */