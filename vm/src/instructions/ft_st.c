#include "vm.h"

void				ft_st(t_cw *cw, t_process **cp)
{
    (void)cw;
    (void)cp;
    t_process   *tcp;

    tcp = *cp;
    tcp->init_cycle = cw->cycle.cycle;
    printf("st called\n");
}