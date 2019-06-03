#include <assembler.h>

void	debug_print_instructions(t_vector *v)
{
	int		i;
	t_instruction	*item;

	i = 0;
	while (i < v->size)
	{
		item = (t_instruction *)vector_get(v, i);
		ft_printf("v->items[%d] = %d\n", i, item->opcode);
		i++;
	}
}

void	debug_print_labels(t_vector *v)
{
	int		i;
	t_label		*item;

	i = 0;
	while (i < v->size)
	{
		item = (t_label *)vector_get(v, i);
		ft_printf("label: %s / %d\n", item->name, item->offset);
		i++;
	}
}