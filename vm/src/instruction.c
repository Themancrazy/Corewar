#include "vm.h"

static t_instr_hdlr instruction[] = {
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

static void		pc_next(t_cw *cw, t_process **cp, uint8_t opc)
{
	(void)cw;
	int			jump;
	t_process 	*test;

	test = *cp;
	jump = g_op_tab[opc].param[0];
	jump += g_op_tab[opc].param[1];
	jump += g_op_tab[opc].param[2];
	printf("champ: %s\tpc: %d\tocp: %d\n", test->id->name, *(test->pc), *(test->pc + 1));
}

void			instruction_init(t_cw *cw, t_process **cp, uint8_t opc)
{
	instruction[opc](cw, cp);
	pc_next(cw, cp, opc);
}