# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cababou <cababou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 22:06:43 by cababou           #+#    #+#              #
#    Updated: 2018/09/17 21:41:20 by cababou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

NAME = fdf

SRC =	fdf.c \
		graphinit.c \
		graphics.c \
		create.c \
		util.c \
		parser.c \
		hooks.c \
		text.c \
		util_nb.c \
		events.c \
		optimization.c \
		ui/button.c \
		bresenham/drawline.c \
		bresenham/q1.c \
		bresenham/q2.c \
		bresenham/q3.c \
		bresenham/q4.c \
		bresenham/q5.c \
		tabs/tabs.c \
		tabs/tabs_init.c \
		tabs/rendering.c \
		map_rendering/renderer.c \
		map_rendering/formatter.c \
		map_rendering/conversion.c \
		map_rendering/rotations.c \
		map_rendering/image_funcs.c \
		map_rendering/image_funcs_two.c \
		map_rendering/colors.c \
		get_next_line.c \
		get_next_line2.c

OBJ = $(SRC:.c=.o)

SRCDIR = src
OBJDIR = obj

SRCP =		$(addprefix $(SRCDIR)/, $(SRC))
OBJP =		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR =	$(foreach dir, $(OBJP), $(shell echo $(dir) | rev | perl -pe 's/.*?\///' | rev))

LIB = ./libft

FLAG = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(OBJP)
			make -C $(LIB)
			gcc $(FLAG) $(OBJP) ./libft/libft.a -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p $(ONLYDIR)
			gcc -c -Wall -Wextra -Werror $< -o $@

clean :
			rm -rf $(OBJDIR)
			make clean -C $(LIB)

fclean :	clean
			rm -rf $(NAME)
			make fclean -C $(LIB)

re :		fclean all
