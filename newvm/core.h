#ifndef CORE_H

# define CORE_H
#include <stdint.h>

typedef struct  s_reg 
{
    uint64_t     rax;
    uint64_t     rcx;
    uint64_t     rbx;
    uint64_t     rsp;
    uint64_t     rbp;
    uint64_t     rsi;
    uint64_t     rdi;
}               t_reg;
    
typedef struct s_cpu
{
    t_reg        registers;
    uint8_t      rip;
    uint32_t     rflags;
    uint8_t      *mar;
    uint8_t      mdr[16];

}               t_cpu;

t_cpu           g_cpu;

# define RAX g_cpu.registers.rax
# define RCX g_cpu.registers.rcx
# define RDX g_cpu.registers.rdx
# define RSP g_cpu.registers.rsp
# define RBP g_cpu.registers.rbp
# define RSI g_cpu.registers.rsi
# define RDI g_cpu.registers.rdi

# define MDR g_cpu.mdr
# define MAR g_cpu.mar

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