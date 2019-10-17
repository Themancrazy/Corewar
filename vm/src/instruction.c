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

static void		decode_ocp(uint8_t **cpc)
{
	static uint8_t	arg_length[4] = {0, T_REG, T_DIR, T_IND};
	uint8_t acb;

	acb = **cpc;
	while (acb)
	{
		*cpc += arg_length[acb & 0b00000011];
		acb >>= 2;		
	}
}

static void		pc_next(t_process **cp, uint8_t op)
{
	//uint8_t		jump_size;
	t_process 	*tcp;

	tcp = *cp;
	//jump_size = 0;
	if (g_op_tab[op].n_param > 1)
	{
		++tcp->pc;
		decode_ocp(&tcp->pc);
	}
	else
		tcp->pc = (tcp->pc + g_op_tab[op].param[0]);
}

void			instruction_init(t_cw *cw, t_process **cp, uint8_t op)
{
	instruction[op](cw, cp);
	pc_next(cp, op);
}