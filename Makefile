# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cababou <cababou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 22:06:43 by cababou           #+#    #+#              #
#    Updated: 2018/09/28 06:50:14 by cababou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

NAME = fdf

SRC =	fractol.c \
		error.c \
		windows.c \
		colors.c \
		image.c \
		window/handle_event.c \
		renderer/mandelbrot/mandelbrot.c

OBJ = $(SRC:.c=.o)

SRCDIR = src
OBJDIR = obj

SRCP =		$(addprefix $(SRCDIR)/, $(SRC))
OBJP =		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR =	$(foreach dir, $(OBJP), $(shell echo $(dir) | rev | perl -pe 's/.*?\///' | rev))

LIB = ./libft

FLAG = -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(OBJP)
			make -C $(LIB)
			gcc -g $(FLAG) $(OBJP) ./libft/libft.a -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p $(ONLYDIR)
			gcc -g -c $< -o $@

clean :
			rm -rf $(OBJDIR)
			make clean -C $(LIB)

fclean :	clean
			rm -rf $(NAME)
			make fclean -C $(LIB)

re :		fclean all
