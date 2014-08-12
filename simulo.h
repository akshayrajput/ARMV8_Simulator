#ifndef _SIMULO_H
#define _SIMULO_H
#include "mem.h"
#include "loader.h"
#include "allstdlib.h"
#define SF_MASK 0x80000000
#define TYPE_MASK 0x18000000
#define INST_IMM_TYPE 0x03800000
#define INST_REG_TYPE 0x1fe00000

Loader loader;
reg R[32]; // the register file
mem Memory[4096]; // the memory
reg IR; //the instruction module
reg PC;//the instruction 

bool debug_prompt;
bool breakpt[4096];


#endif

