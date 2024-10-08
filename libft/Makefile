# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daortega <daortega@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 14:31:34 by daortega          #+#    #+#              #
#    Updated: 2024/08/29 13:30:28 by daortega         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
NAMELIB = libft.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
LIBCOM = ar rcs

#--------------<SRC>-------------
SRCPRINTF = ft_printf/
SRCPRINTFFD = ft_printf_fd/
SRC_GET_NEXT_LINE = get_next_line/


#----------------<Files>---------------- 
CFILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_strcmp.c

BFILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstadd_back.c \
ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
ft_lstmap.c

PFFILES = ft_printf.c ft_putchar.c ft_puthexa.c ft_putnum.c ft_putpointer.c \

PFDFILES = ft_hex_fd.c ft_printf_fd.c ft_printfnbr_fd.c \

GNLFILES = get_next_line.c get_next_line_utils.c \

SRCPRINT = $(addprefix $(SRCPRINTF), $(PFFILES))
SRCPRINTFD = $(addprefix $(SRCPRINTFFD), $(PFDFILES))
SRCGNL = $(addprefix $(SRC_GET_NEXT_LINE), $(GNLFILES))

OBJ = $(CFILES:.c=.o)
OBJ_PRINT = $(SRCPRINT:.c=.o)
OBJ_PRINT_FD = $(SRCPRINTFD:.c=.o)
OBJ_GNL = $(SRCGNL:.c=.o)
BOBJ = $(BFILES:.c=.o)


#------------Rules-------------
all: $(NAME)

bonus: libbonus

%.o: %.c $(NAMELIB) Makefile
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ) $(OBJ_PRINT) $(OBJ_PRINT_FD) $(OBJ_GNL)
	@$(LIBCOM) $(NAME) $(OBJ) $(OBJ_PRINT) $(OBJ_PRINT_FD) $(OBJ_GNL)

libbonus: $(BOBJ)
	@$(LIBCOM) $(NAME) $(BOBJ)

clean:
	@rm -f $(OBJ) $(BOBJ) $(OBJ_PRINT) $(OBJ_GNL)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
