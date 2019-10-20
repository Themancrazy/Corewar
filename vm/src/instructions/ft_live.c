#include "vm.h"

void				ft_live(t_cw *cw, t_process *cp)
{
    (void)cw;
    uint32_t prog_num;

    ++cw->n_live_call;
    if (cw->n_live_call == NBR_LIVE)
    {
        cw->n_live_call = 0;
        cw->cycle.kill_cycle -= CYCLE_DELTA;
    }
    prog_num = cp->id->prog_number * (-1);
    swap_32(&prog_num);
    ft_memcpy(&cw->memory[cp->pc + 1], &prog_num, 4);
    cp->live_call = cw->cycle.cycle;
    cw->winner = cp->id;
    printf("live called\n");
}