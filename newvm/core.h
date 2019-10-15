#ifndef CORE_H

# define CORE_H
#include <stdint.h>

#define MEM_SIZE (4*1024)

typedef struct s_cpu
{
    uint8_t     registers[16];
    uint8_t      rip;
    uint32_t     rflags;
    uint8_t      *mar;
    uint8_t      mdr[16];
}               t_cpu;

typedef struct s_process
{
    uint8_t     registers[16];
    uint8_t     rip;
    int8_t      pid;
    int8_t      parent_pid;
}               t_process;

t_cpu           g_cpu;

uint8_t			g_ram[MEM_SIZE];
uint8_t         g_gram[MEM_SIZE];

# define R0 g_cpu.registers[0];
# define R1 g_cpu.registers[1];
# define R2 g_cpu.registers[2];
# define R3 g_cpu.registers[3];
# define R4 g_cpu.registers[4];
# define R5 g_cpu.registers[5];
# define R6 g_cpu.registers[6];
# define R7 g_cpu.registers[7];
# define R8 g_cpu.registers[8];
# define R9 g_cpu.registers[9];
# define R10 g_cpu.registers[10];
# define R11 g_cpu.registers[11];
# define R12 g_cpu.registers[12];
# define R13 g_cpu.registers[13];
# define R14 g_cpu.registers[14];
# define R15 g_cpu.registers[15];


# define MDR g_cpu.mdr
# define MAR g_cpu.mar

# define MEM g_ram;
# define MEM_END (MEM + MEM_SIZE)

# define XOR(reg_a, reg_b) (reg_a ^= reg_b)
# define ADD(reg_a, reg_b) (reg_a += reg_b)
# define SUB(reg_a, reg_b) (reg_a -= reg_b)


/*
TODO:
using acb as key to dispatch work to different handlers
multiple mov macro
ram memory access


*/


#endif