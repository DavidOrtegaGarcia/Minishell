# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daortega <daortega@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 13:43:24 by daortega          #+#    #+#              #
#    Updated: 2024/05/15 16:33:20 by daortega         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GREEN	=	\033[38;5;154m
RED		=	\033[38;5;197m
NC		=	\033[0m
YELLOW	=	\033[38;5;190m

#-------------<COMMANDS>------------
CC 		= 		gcc
CFLAGS 	= 	-Wall -Wextra -Werror #-fsanitize=address
INCLUDE =	-I./libs -I./readline -I./libft

#--------------<SRC>-------------
NAME	=	minishell
SRC		=	src/
CFILES	=	main.c utilsd.c
SRCC	=	$(addprefix $(SRC), $(CFILES))

DIR_O	= 	tmp/
OBJC	=	$(addprefix $(DIR_O), $(SRCC:.c=.o))


LIB_A		:=	readline/libreadline.a readline/libhistory.a libft/libft.a
LIB_ADD_DIR	:=	-Lreadline -Llibft
LIB_SEARCH	:=	-lreadline -lhistory -ltermcap -lft

#-------------<RULES>-------------
all: makelibs rdline $(DIR_O) $(NAME)

makelibs: 
	@$(MAKE) -C libft/ --no-print-directory
	@$(MAKE) readline --no-print-directory
	
$(DIR_O):
	@mkdir -p $(DIR_O)

$(NAME): $(OBJC)
	@$(CC) $(CFLAGS) $(OBJC) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $(NAME)
	@echo "${GREEN}Minishell Compiled${NC}"

rdline :
	@echo "${YELLOW}Compiling Readline...${NC}"
	@cd ./readline/ &> /dev/null && ./configure &> /dev/null
	@make -C ./readline/ &> /dev/null
	@echo "${GREEN}Readline Compiled${NC}"
	
$(DIR_O)%.o: %.c $(LIB_A) Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "${YELLOW}Compiling obj $@...${NC}"

clean: 
	@$(MAKE) -C libft clean --no-print-directory
	@rm -rf $(DIR_O)
	@printf "${RED}Objs deleted\n${NC}"

fclean: clean 
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean --no-print-directory
	@$(MAKE) -C readline clean --no-print-directory
	@printf "${RED}Minishell deleted\n${NC}"

re: fclean all

.PHONY: all clean fclean re
