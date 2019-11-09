# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:57:22 by anjansse          #+#    #+#              #
#    Updated: 2019/11/08 19:57:42 by anjansse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C asm/ re
	@make -C vm/ re
	@cp asm/asm asm_exec
	@cp vm/corewar .

fclean:
	@make -C asm/ fclean
	@make -C vm/ fclean
	@rm asm_exec
	@rm corewar
