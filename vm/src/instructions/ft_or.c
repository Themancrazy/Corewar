#include "vm.h"

void				ft_or(t_cw *cw, t_process **cp)
{
    (void)cw;
    (void)cp;
    t_process *cpc;

    cpc = *cp;
    cpc->init_cycle = cw->cycle.cycle;
    printf("or called\n");
}