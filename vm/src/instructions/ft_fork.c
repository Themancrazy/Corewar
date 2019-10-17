#include "vm.h"

void				ft_fork(t_cw *cw, t_process **cp)
{
    (void)cw;
    (void)cp;
    t_process *cpc;

    cpc = *cp;
    cpc->init_cycle = cw->cycle.cycle;
    printf("fork called\n");
}