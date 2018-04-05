#ifndef _SIMULO_H
#define _SIMULO_H
#include "mem.h"
#include "loader.h"
#include "allstdlib.h"
#define SF_MASK 0x80000000
#define TYPE_MASK 0x1e000000
#define INST_IMM_TYPE 0x03800000
#define INST_REG_TYPE 0x1fe00000
#define INST_B_TYPE 0x7e000000

bool ZFLAG;//zeroflag
bool OFLAG;//overflow flag
bool NFLAG;//the negative flag
bool CFLAG;//the carry flag
Loader loader;
reg R[32]; // the register file
mem Memory[4096]; // the memory
reg IR; //the INSTRUCTION REGISTER
reg PC;//the PROGRAM COUNTER 
reg BR;//the BASE REGISTER - keeping the base address
int NIO;//the next instruction offset
bool debug_prompt;
bool skip;
bool breakpt[4096];
int SR[4096];
int subroutine;//subroutine counter

#endif

