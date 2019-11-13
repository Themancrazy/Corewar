# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:57:22 by anjansse          #+#    #+#              #
#    Updated: 2019/11/12 13:21:54 by anjansse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C libft/ re
	@make -C asm/
	@make -C vm/
	@cp asm/asm asm_exec
	@cp vm/corewar .
	@sleep 0.1
	@clear
	@echo "\x1b[36m\x1b[1m**********************************************************\
**********************"
	@echo "*  .oooooo.                                                                    *\n* d8P'  \`Y8b                                                                   *\n*888           .ooooo.  oooo d8b  .ooooo.  oooo oooo    ooo  .oooo.   oooo d8b *\n*888          d88' \`88b \`888""8P   d88' \`88b  \`88. \`88.  .8'  \`P  )88b  \`888""8P   *\n*888          888   888  888     888ooo888   \`88..]88..8'    .oP\"888   888     *\n*\`88b    ooo  888   888  888     888    .o    \`888'\`888'    d8(  888   888     *\n* \`Y8bood8P'  \`Y8bod8P' d888b    \`Y8bod8P'     \`8'  \`8'     \`Y888""8o    d888b   *\n*                                                                              *\n*                                                                              *\n********************************************************************************\x1b[0m\n"
	@echo "\x1b[1m\x1b[93mCorewar usage: ./asm_exec <assembly file (.s)> | ./corewar <flag (-gdn)> <champs>\n\x1b[0m"

vm:
	@make -C vm/
	@cp vm/corewar .

fclean:
	@make -C asm/ fclean
	@make -C vm/ fclean
	@rm asm_exec
	@rm corewar

re: fclean all
