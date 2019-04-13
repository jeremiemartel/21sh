# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 23:08:04 by ldedier           #+#    #+#              #
#    Updated: 2019/04/13 11:35:39 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 21sh

CC		= gcc -g3

PWD = \"$(shell pwd)\"

DEBUG ?= 0

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = includes
LIBFTDIR = libft
PROD_DIR   = productions


SPEED = -j1
LIBFT_INCLUDEDIR = includes
LIBFT = $(LIBFTDIR)/libft.a

OK_COLOR = \x1b[32;01m
EOC = \033[0m

SRCS_NO_PREFIX =		parser.c init_cfg.c\
						first_sets.c debug.c follow_sets.c\
						compute_lr_automata.c compute_lr_tables.c\
						lr_parse.c compute_first_state.c state.c\
						compute_closure.c compute_transitions.c traverse.c\
						init_parsing.c grammar.c index.c\
						
## Lexer sources
SRCS_NO_PREFIX +=		lexer/main.c lexer/lexer.c lexer/t_lexer.c \
						lexer/t_token.c lexer/lexer_rules.c \
						lexer/lexer_expansions.c \
						lexer/lexer_expansions_detect.c \
						lexer/lexer_expansions_process.c


PROD_SRCS_NO_PREFIX =	sh_prod_and_or.c sh_prod_brace_group.c\
						sh_prod_case_clause.c sh_prod_case_item.c\
						sh_prod_case_item_ns.c sh_prod_case_list.c\
						sh_prod_case_list_ns.c sh_prod_cmd_name.c\
						sh_prod_cmd_prefix.c sh_prod_cmd_suffix.c\
						sh_prod_cmd_word.c sh_prod_command.c\
						sh_prod_complete_command.c sh_prod_compound_command.c\
						sh_prod_compound_list.c sh_prod_do_group.c\
						sh_prod_else_part.c sh_prod_filename.c\
						sh_prod_fname.c sh_prod_for_clause.c\
						sh_prod_function_body.c sh_prod_function_definition.c\
						sh_prod_here_end.c sh_prod_if_clause.c sh_prod_in.c\
						sh_prod_io_file.c sh_prod_io_here.c\
						sh_prod_io_redirect.c sh_prod_linebreak.c\
						sh_prod_list.c sh_prod_name.c sh_prod_newline_list.c\
						sh_prod_pattern.c sh_prod_pipe_sequence.c\
						sh_prod_pipeline.c sh_prod_program.c\
						sh_prod_redirect_list.c sh_prod_separator.c\
						sh_prod_separator_op.c sh_prod_sequential_sep.c\
						sh_prod_simple_command.c sh_prod_subshell.c\
						sh_prod_term.c sh_prod_until_clause.c\
						sh_prod_while_clause.c sh_prod_wordlist.c\
						sh_prod_complete_commands.c

INCLUDES_NO_PREFIX	= sh_21.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
PROD_SOURCES = $(addprefix $(SRCDIR)/$(PROD_DIR)/, $(PROD_SRCS_NO_PREFIX))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
PROD_OBJECTS = $(addprefix $(OBJDIR)/$(PROD_DIR)/, $(PROD_SRCS_NO_PREFIX:%.c=%.o))
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))
OBJECTS += $(PROD_OBJECTS)

INC =	-I $(INCLUDESDIR) -I $(LIBFTDIR)

CFLAGS =	-DPATH=$(PWD) -Wall -Wextra -Werror $(INC) -g3
LFLAGS =	-L $(LIBFTDIR) -lft -ltermcap

ifeq ($(DEBUG), 1)
	LFLAGS += -fsanitize=address
	#CFLAGS += -DDEBUG
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
	echo $(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)
	@$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/$(PROD_DIR)/%.o : $(SRCDIR)/$(PROD_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(PROD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@make clean -C $(LIBFTDIR)
	@rm -f $(OBJECTS)
	# @rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@rm -f $(BINDIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
