#include "vm.h"

void				ft_zjump(t_cw *cw, t_process *cp)
{
    (void)cw;
    (void)cp;
    uint32_t    jump_size;

    jump_size = 0;
    if (cp->carry == 1)
    {
        ft_memcpy((void *)&jump_size, cp->pc, 4);
        cp->pc = (cp->pc + jump_size);
    }
    printf("zjump called\n");
}