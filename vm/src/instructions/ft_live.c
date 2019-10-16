#include "vm.h"

void				ft_live(t_cw *cw, t_process **cp)
{
    (void)cw;
    (void)cp;
    t_process   *tcp;
    // cw->winner = *(cp->id);
    tcp = *cp;
    tcp->live_call = cw->cycle.cycle;
    cw->winner = tcp->id;
    printf("live called\n");
}