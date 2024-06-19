# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daortega <daortega@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 13:43:24 by daortega          #+#    #+#              #
#    Updated: 2024/06/19 16:51:39 by rpocater         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------<COLORS>---------------
GREEN	=	\033[38;5;154m
RED		=	\033[38;5;197m
NC		=	\033[0m
YELLOW	=	\033[38;5;190m

#-------------<COMMANDS>------------
CC 		= 	gcc
CFLAGS 	= 	-Wall -Wextra -Werror -fsanitize=address
<<<<<<< HEAD
INCLUDE =	-I./libs -I./libft #-I./libs -I./readline -I./libft
=======
INCLUDE =	-I./libs -I./libft 
>>>>>>> b552deffa6d5e214408dff57579fae2f687aadf1

#--------------<SRC>----------------
NAME	=	minishell
SRC		=	src/
CFILES	=	main.c execute.c parse.c tokenize.c env.c expansor.c utils_expansor.c \
			signals.c
SRCC	=	$(addprefix $(SRC), $(CFILES))

DIR_O	= 	tmp/
OBJC	=	$(addprefix $(DIR_O), $(SRCC:.c=.o))


LIB_A		:=	libft/libft.a 
LIB_ADD_DIR	:=	-Llibft 
LIB_SEARCH	:=	-lreadline -lft #-lhistory -ltermcap -lft

#-------------<RULES>-------------
all: makelibs $(DIR_O) $(NAME)

makelibs: 
	@$(MAKE) -C libft/ --no-print-directory
	
$(DIR_O):
	@mkdir -p $(DIR_O)

$(NAME): $(OBJC)
	@$(CC) $(CFLAGS) $(OBJC) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $(NAME)
	@echo "${GREEN}Minishell Compiled${NC}"
	
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
	@printf "${RED}Minishell deleted\n${NC}"

re: fclean all

.PHONY: all clean fclean re
