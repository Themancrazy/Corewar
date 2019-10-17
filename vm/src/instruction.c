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

static void		decode_ocp(uint8_t *cpc, uint8_t *ret, int trunc)
{
	static uint8_t	arg_length[4] = {0, T_REG, T_DIR, T_IND};
	static uint8_t	arg_length2[4] = {0, T_REG, T_IND, T_IND};
	uint8_t acb;
	int		i;

	i = -1;
	acb = *cpc;
	while (++i < 4)
	{
		if (trunc == 1)
			*ret += arg_length[acb & 0b00000011];
		else
			*ret += arg_length2[acb & 0b00000011];
		acb >>= 2;		
	}
}

static void		pc_next(t_process *cp, uint8_t op)
{
	uint8_t		jump_size;

	jump_size = 0;
	if (g_op_tab[op].n_param > 1 && g_op_tab[op].cbyte == 1)
	{
		decode_ocp(++(cp->pc), &jump_size, g_op_tab[op].trunc);
		cp->pc = (cp->pc + 1 + jump_size);
	}
	else
	{
		jump_size = (g_op_tab[op].trunc == 0 && g_op_tab[op].param[0] == T_DIR) ? T_IND : g_op_tab[op].param[0];
		cp->pc = (cp->pc + 1 + jump_size);
	}
}

void			instruction_init(t_cw *cw, t_process **cp, uint8_t op)
{
	t_process *tmp;

	tmp = *cp;
	printf("%s:\t", tmp->id->name);
	instruction[op](cw, cp);
	pc_next(*cp, op);
}