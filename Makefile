# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 23:08:04 by ldedier           #+#    #+#              #
#    Updated: 2019/05/08 12:10:35 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 21sh

CC		= gcc

PWD = \"$(shell pwd)\"

DEBUG ?= 0

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = includes
LIBFTDIR = libft

PROD_DIR   = productions
LEXER_DIR	= lexer
PARSER_DIR	= parser
TRAV_DIR	= traverse
TRAVT_DIR	= traverse_tools
VARS_DIR	= vars
AUTO_DIR	= autocomplete
EXEC_DIR	= exec
BUILT_DIR	= builtin

SPEED = -j1
LIBFT_INCLUDEDIR = includes
LIBFT = $(LIBFTDIR)/libft.a

OK_COLOR = \x1b[32;01m
EOC = \033[0m

TRAV_SRCS_NO_PREFIX =	sh_traverse_default.c \
						sh_traverse_complete_command.c \
						sh_traverse_and_or.c \
						sh_traverse_semicol.c \
						sh_traverse_and_if.c \
						sh_traverse_or_if.c \
						sh_traverse_pipeline.c \
						sh_traverse_pipe_sequence.c \
						sh_traverse_command.c \
						sh_traverse_assigment_word.c \
						sh_traverse_simple_command.c \
						sh_traverse_tok_pipe.c \
						sh_traverse_cmd_name.c \
						sh_traverse_cmd_word.c \
						sh_traverse_cmd_suffix.c \
						sh_traverse_io_redirect.c \
						sh_traverse_filename.c \
						sh_traverse_io_here.c \
						sh_traverse_io_file.c \
						sh_traverse_less.c \
						sh_traverse_lessand.c \
						sh_traverse_great.c \
						sh_traverse_greatand.c \
						sh_traverse_dgreat.c \
						

TRAVT_SRCS_NO_PREFIX	= sh_traverse_tools_flush.c \
						sh_traverse_tools_browse.c \
						sh_traverse_tools_reset.c \
						sh_traverse_tools_context.c \


SRCS_NO_PREFIX =		main.c index.c ft_perror.c init.c \
						shell_tools.c free_all.c init_term.c signals.c keys.c \
						cursor_motion.c edit_command.c is_printable_utf8.c \
						get_command.c utf8_tools.c \
						tools.c\
						traverse.c

PARSER_SRCS_NO_PREFIX =	parser.c init_cfg.c\
						first_sets.c debug.c follow_sets.c\
						compute_lr_automata.c compute_lr_tables.c\
						lr_parse.c compute_first_state.c state.c\
						compute_closure.c compute_transitions.c traverse.c\
						init_parsing.c grammar.c reduce.c reduce_tools.c

LEXER_SRCS_NO_PREFIX =	sh_lexer.c \
						sh_lexer_rules.c \
						sh_lexer_quoting.c \
						sh_lexer_exp.c sh_lexer_exp_init.c \
						sh_lexer_exp_process.c sh_lexer_exp_process_tilde.c \
						t_expansion.c t_lexer.c t_token.c
						# sh_lexer_expansions.c \
						# sh_lexer_expansions_detect.c \
						# sh_lexer_expansions_process.c \
						# sh_lexer_expansions_process_tilde.c \

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

AUTO_SRCS_NO_PREFIX	=	add_choices_from_dir.c auto_completion.c \
						populate_choices.c populate_word_by_index.c \
						preprocess_choice_add.c

VARS_SRCS_NO_PREFIX	=	env.c set_env.c \
						sh_vars_tools_1.c sh_vars_tools_2.c \

EXEC_SRCS_NO_PREFIX	=	sh_execute.c \
						sh_execute_tools.c \
						sh_process_execute.c \
						sh_process_historic.c \
						sh_process_shift.c \
				t_context.c

BUILT_SRCS_NO_PREFIX=	sh_builtin.c	\
						sh_builtin_pwd.c \
						sh_builtin_echo.c \
						sh_builtin_exit.c \
						t_builtin.c


INCLUDES_NO_PREFIX	= sh_21.h sh_lexer.h sh_tokens.h sh_parser.h sh_grammar.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
LEXER_SOURCES = $(addprefix $(SRCDIR)/$(LEXER_DIR)/, $(LEXER_SRCS_NO_PREFIX))
PARSER_SOURCES = $(addprefix $(SRCDIR)/$(PARSER_DIR)/, $(PARSER_SRCS_NO_PREFIX))
PROD_SOURCES = $(addprefix $(SRCDIR)/$(PARSER_DIR)/$(PROD_DIR)/, $(PROD_SRCS_NO_PREFIX))
AUTO_SOURCES = $(addprefix $(SRCDIR)/$(AUTO_DIR)/, $(AUTO_SRCS_NO_PREFIX))
TRAV_SOURCES = $(addprefix $(SRCDIR)/$(TRAV_DIR)/, $(TRAV_SRCS_NO_PREFIX))
TRAVT_SOURCES = $(addprefix $(SRCDIR)/$(TRAVT_DIR)/, $(TRAVT_SRCS_NO_PREFIX))
VARS_SOURCES = $(addprefix $(SRCDIR)/$(VARS_DIR)/, $(VARS_SRCS_NO_PREFIX))
EXEC_SOURCES = $(addprefix $(SRCDIR)/$(EXEC_DIR)/, $(EXEC_SRCS_NO_PREFIX))
BUILT_SOURCES = $(addprefix $(SRCDIR)/$(BUILT_DIR)/, $(BUILT_SRCS_NO_PREFIX))

OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
LEXER_OBJECTS = $(addprefix $(OBJDIR)/$(LEXER_DIR)/, $(LEXER_SRCS_NO_PREFIX:%.c=%.o))
PARSER_OBJECTS = $(addprefix $(OBJDIR)/$(PARSER_DIR)/, $(PARSER_SRCS_NO_PREFIX:%.c=%.o))
PROD_OBJECTS = $(addprefix $(OBJDIR)/$(PARSER_DIR)/$(PROD_DIR)/, $(PROD_SRCS_NO_PREFIX:%.c=%.o))
TRAV_OBJECTS = $(addprefix $(OBJDIR)/$(TRAV_DIR)/, $(TRAV_SRCS_NO_PREFIX:%.c=%.o))
TRAVT_OBJECTS = $(addprefix $(OBJDIR)/$(TRAVT_DIR)/, $(TRAVT_SRCS_NO_PREFIX:%.c=%.o))
VARS_OBJECTS = $(addprefix $(OBJDIR)/$(VARS_DIR)/, $(VARS_SRCS_NO_PREFIX:%.c=%.o))
EXEC_OBJECTS = $(addprefix $(OBJDIR)/$(EXEC_DIR)/, $(EXEC_SRCS_NO_PREFIX:%.c=%.o))
BUILT_OBJECTS = $(addprefix $(OBJDIR)/$(BUILT_DIR)/, $(BUILT_SRCS_NO_PREFIX:%.c=%.o))


AUTO_OBJECTS = $(addprefix $(OBJDIR)/$(AUTO_DIR)/, $(AUTO_SRCS_NO_PREFIX:%.c=%.o))

INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

OBJECTS += $(PROD_OBJECTS)
OBJECTS += $(LEXER_OBJECTS)
OBJECTS += $(PARSER_OBJECTS)
OBJECTS += $(TRAV_OBJECTS)
OBJECTS += $(TRAVT_OBJECTS)
OBJECTS += $(AUTO_OBJECTS)
OBJECTS += $(VARS_OBJECTS)
OBJECTS += $(EXEC_OBJECTS)
OBJECTS += $(BUILT_OBJECTS)

INC =	-I $(INCLUDESDIR) -I $(LIBFTDIR)

CFLAGS =	-DPATH=$(PWD) -Wall -Wextra -Werror $(INC) -g3
LFLAGS =	-L $(LIBFTDIR) -lft -ltermcap

ifeq ($(DEBUG), 1)
	LFLAGS += -fsanitize=address
	#CFLAGS += -DDEBUG
	CC += -g3
	SPEED = -j8
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

$(OBJDIR)/$(PARSER_DIR)/$(PROD_DIR)/%.o : $(SRCDIR)/$(PARSER_DIR)/$(PROD_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(PARSER_DIR)/$(PROD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/$(AUTO_DIR)/%.o : $(SRCDIR)/$(AUTO_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(AUTO_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/$(LEXER_DIR)/%.o : $(SRCDIR)/$(LEXER_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(LEXER_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/$(TRAV_DIR)/%.o : $(SRCDIR)/$(TRAV_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(TRAV_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/$(TRAVT_DIR)/%.o : $(SRCDIR)/$(TRAVT_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(TRAVT_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/$(PARSER_DIR)/%.o : $(SRCDIR)/$(PARSER_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(PARSER_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/$(VARS_DIR)/%.o : $(SRCDIR)/$(VARS_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(VARS_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/$(EXEC_DIR)/%.o : $(SRCDIR)/$(EXEC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(EXEC_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/$(BUILT_DIR)/%.o : $(SRCDIR)/$(BUILT_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)/$(BUILT_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

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
