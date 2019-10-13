#include "vm.h"

static t_instr_hdlr instr[] = {
	ft_live,
	ft_ld,
	ft_st,
	ft_add,
	ft_sub,
	ft_and,
	ft_or,
	ft_xor,
	ft_zjump,
	ft_ldi,
	ft_sti,
	ft_fork,
	ft_lld,
	ft_lldi,
	ft_lfork,
	ft_aff
};

static void		pc_next(t_cw *cw, t_process **cp)
{
	(void)cw;
	(void)cp;
}

void			instruction_init(t_cw *cw, t_process **cp, uint8_t opc)
{
	instr[opc](cw, cp);
	pc_next(cw, cp);
}