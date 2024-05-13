# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daortega <daortega@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 13:43:24 by daortega          #+#    #+#              #
#    Updated: 2024/05/13 14:58:03 by rpocater         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAMELIB = libs/minishell.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -static-libsan -g

#--------------<SRC>-------------
SRC = src/
CFILES = execute.c main.c
SRCC = $(addprefix $(SRC), $(CFILES))

DIR_O = tmp/
OBJC = $(addprefix $(DIR_O), $(SRCC:.c=.o))

# RULES
all: makelibft $(DIR_O) $(NAME)

makelibft: 
	$(MAKE) -C libft 
	
$(DIR_O):
	mkdir -p $(DIR_O)

$(DIR_O)%.o: %.c $(NAMELIB) Makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJC) libft/libft.a 
	$(CC) $(CFLAGS) $(OBJC) -Llibft -lft -o $(NAME)

cleanlibft:
	$(MAKE) -C libft clean

fcleanlibft:
	$(MAKE) -C libft fclean

clean: cleanlibft
	rm -rf $(DIR_O)
	rm -f $(OBJC)

fclean: clean fcleanlibft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
