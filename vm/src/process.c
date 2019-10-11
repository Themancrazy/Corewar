#include "vm.h"



void        process_update(t_cw *cw)
{
    (void)cw;
    t_process   *cp;

    cp = cw->process_list;
    while (cp)
    {
        // printf("Process %s: %x\n", cp->id->name, (uint8_t)cp->pc);
        cp = cp->next;
    }
}

void        process_init(t_cw *cw, t_champ *id, void *pc)
{
    t_process   *cp;
    t_process   **list;

    list = &cw->process_list;
    if (!(cp = (t_process*)malloc(sizeof(t_process))))
        return ;
    cp->carry = 0;
    cp->pc = pc;
    cp->id = id;
    cp->registers[1] = (void*)&id->prog_number;
    cw->n_process++;
    cp->next = *list;
    *list = cp;
}