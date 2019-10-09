#include "vm.h"

void        corewar_run(t_cw *cw)
{
    (void)cw;
    int i = -1;
    while (++i < MAX_PLAYERS)
    {
        // printf("%d. OFF: %s\tnum: %d\n", i, cw->champions[i].name, cw->champions[i].prog_number);
        // printf("%d. TMP: %s\n", i, cw->tmp_champ[i].name);
    }
}