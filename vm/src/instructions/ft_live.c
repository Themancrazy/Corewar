#include "vm.h"

void				ft_live(t_cw *cw, t_process *cp)
{
    (void)cw;
    cp->live_call = cw->cycle.cycle;
    cw->winner = cp->id;
    printf("live called\n");
}