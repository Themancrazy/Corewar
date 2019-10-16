#include "vm.h"

void				ft_ld(t_cw *cw, t_process **cp)
{
    (void)cw;
    t_process   *tcp;
    uint32_t    offset;
    uint8_t     n_reg;

    tcp = *cp;
    offset = *(uint32_t *)(tcp->pc + 1);
    n_reg = *(uint32_t *)(tcp->pc + 2);
    tcp->registers[n_reg] = *(uint32_t *)(tcp->pc + offset);
    printf("ld called\n");
}