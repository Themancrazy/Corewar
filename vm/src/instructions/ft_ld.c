#include "vm.h"

void				ft_ld(t_cw *cw, t_process **cp)
{
    (void)cw;
    t_process   *tcp;

    tcp = *cp;
    tcp->init_cycle = cw->cycle.cycle;
    printf("ld called\n");
}