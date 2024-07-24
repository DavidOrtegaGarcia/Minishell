# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daortega <daortega@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 13:43:24 by daortega          #+#    #+#              #
#    Updated: 2024/07/24 16:07:20 by daortega         ###   ########.fr        #
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
INCLUDE =	-I./libs -I./libft #-I./libs -I./readline -I./libft

#--------------<SRC>----------------
NAME	=	minishell
SRC		=	src/
CFILES	=	main.c execute_dav.c parse.c tokenize.c env.c expansor.c \
		utils_expansor.c signals.c utils_token.c add_tokens.c \
		list_to_matrix.c utils_parse.c utils_execute.c heredoc.c \
		redirections.c find_path.c\

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
