#ifndef FIONA_INSTR_H
#define FIONA_INSTR_H

#include "rocc.h"
#define DUMP_STAT                 ROCC_INSTRUCTION_I_I_I(0, 0, 0, 0, 0x0F);

#define ADD_V(vd, v1, v2)       { ROCC_INSTRUCTION_I_I_I(0, vd, v1, v2, 0x01); }
#define SUB_V(vd, v1, v2)       { ROCC_INSTRUCTION_I_I_I(0, vd, v1, v2, 0x02); }
#define ADD_VS(vd, r1, v2)      { ROCC_INSTRUCTION_I_R_I(0, vd, r1, v2, 0x03, 10); }
#define SUB_VS(vd, r1, v2)      { ROCC_INSTRUCTION_I_R_I(0, vd, r1, v2, 0x04, 10); }
#define MUL_VS(vd, r1, v2)      { ROCC_INSTRUCTION_I_R_I(0, vd, r1, v2, 0x05, 10); }
#define DIV_VS(vd, r1, v2)      { ROCC_INSTRUCTION_I_R_I(0, vd, r1, v2, 0x06, 10); }

#define SHUFFLE_V(vd, v1, v2)   { ROCC_INSTRUCTION_I_I_I(0, vd, v1, v2, 0x0A); }
#define MAX_V(rd, v1)           { ROCC_INSTRUCTION_R_I_I(0, rd, v1, 0, 0x0B, 10); }
#define MIN_V(rd, v1)           { ROCC_INSTRUCTION_R_I_I(0, rd, v1, 1, 0x0B, 10); }

#define PRELU_V(vd, r1, v2)     { ROCC_INSTRUCTION_I_R_I(0, vd, r1, v2, 0x0F, 10); }
#define TANH_V(vd, v1)          { ROCC_INSTRUCTION_I_I_I(0, vd, v1, 1, 0x0F); }
#define SIGMOID_V(vd, v1)       { ROCC_INSTRUCTION_I_I_I(0, vd, v1, 2, 0x0F); }

#define LOAD_V(vregnum, src)    { ROCC_INSTRUCTION_I_R_I(0, vregnum, src, 0, 8, 10); }
#define STORE_V(vregnum, dst)   { ROCC_INSTRUCTION_I_R_I(0, 0, dst, vregnum, 9, 10); }

#define SET_VLEN(r1)            { ROCC_INSTRUCTION_I_R_I(0, 0, r1, 0, 12, 10); }
#define SET_VMASK(r1, r2)       { ROCC_INSTRUCTION_I_R_R(0, 1, r1, r2, 12, 11, 12); }
#define SET_MAT(r1)             { ROCC_INSTRUCTION_I_R_I(0, 2, r1, 0, 12, 10); }
#define SET_STRIDE(r1)          { ROCC_INSTRUCTION_I_R_I(0, 3, r1, 0, 12, 10); }

#define DOTP(rd, v1, v2)        { ROCC_INSTRUCTION_R_I_I(0, rd, v1, v2, 13, 10); }
#define MVM(vd, v1)             { ROCC_INSTRUCTION_I_I_I(0, vd, v1, 0, 14); }

#endif /* FIONA_INSTR_H */
