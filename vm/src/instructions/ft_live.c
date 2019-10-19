#include "vm.h"

void				ft_live(t_cw *cw, t_process *cp)
{
    (void)cw;
    ++cw->n_live_call;
    if (cw->n_live_call == NBR_LIVE)
    {
        cw->n_live_call = 0;
        cw->cycle.kill_cycle -= CYCLE_DELTA;
    }
    cp->live_call = cw->cycle.cycle;
    cw->winner = cp->id;
    printf("live called\n");
}