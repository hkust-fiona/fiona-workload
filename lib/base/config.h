#ifndef FIONA_CONFIG_H
#define FIONA_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <assert.h>
#include <math.h>

// PU: photonic unit
#define PU_MZI_PORT 4
#define PU_MZI_TILE 2
#define PU_MRR_RING 8
#define PU_MRR_TILE 1

// EU: electronic unit
#define EU_VEC_ELEM 32

// basic data-type for elements
typedef int16_t elem_t;

const elem_t elem_t_min = SHRT_MIN;
const elem_t elem_t_max = SHRT_MAX;


#endif /* FIONA_CONFIG_H */