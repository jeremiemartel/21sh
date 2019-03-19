# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/12 13:39:53 by ldedier           #+#    #+#              #
#    Updated: 2019/03/19 19:00:17 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 21sh

CC      = gcc -g3

PWD = \"$(shell pwd)\"

DEBUG ?= 0

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = includes
LIBFTDIR = libft
SPEED = -j1
LIBFT_INCLUDEDIR = includes
LIBFT = $(LIBFTDIR)/libft.a

OK_COLOR = \x1b[32;01m
EOC = \033[0m

SRCS_NO_PREFIX		=	main.c lexer.c t_lexer.c t_token.c lexer_rules.c \
						lexer_expansions.c lexer_expansions_detect.c \
						lexer_expansions_process.c


INCLUDES_NO_PREFIX	= sh_21.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror $(INC) -g3
LFLAGS = -L $(LIBFTDIR) -lft -ltermcap

ifeq ($(DEBUG), 1)
	LFLAGS += -fsanitize=address
	CFLAGS += -DDEBUG
	CC += -g3
else
	SPEED = -j8
endif

all:
	@make -C $(LIBFTDIR) $(SPEED)
	@make $(BINDIR)/$(NAME) $(SPEED)

debug:
	@make all DEBUG=1

$(LIBFT):
	@make -C $(LIBFTDIR)

$(BINDIR)/$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS) 
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@make clean -C $(LIBFTDIR)
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@rm -f $(BINDIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
