/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/13 11:26:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

# include <stdarg.h>
# include "libft.h"
# include "sh_tokens.h"
# include "sh_lexer.h"

# define DEBUG_BUFFER	50

typedef struct		s_symbol
{
	t_list			*productions;
	int				id;
	char			first_sets[NB_TERMS];
	char			follow_sets[NB_TERMS];
	char			debug[DEBUG_BUFFER];
	char			relevant;
	char			replacing;
}					t_symbol;

typedef struct		s_production
{
	int				index;
	t_symbol		*from;
	t_list			*symbols;
}					t_production;

typedef struct		s_state
{
	t_list			*transitions;
	t_list			*items;
	t_list			*items_by_production[NB_PRODUCTIONS];
	int				index;
	int				parsed;
}					t_state;

typedef struct		s_transition
{
	t_symbol		*symbol;
	t_state			*state;
}					t_transition;

typedef struct		s_item
{
	t_production	*production;
	t_list			*progress;
	char			lookaheads[NB_TERMS];
	char			parsed;
}					t_item;

typedef struct s_cfg
{
	t_symbol		start_symbol;
	t_symbol		symbols[NB_SYMBOLS];
	t_production	productions[NB_PRODUCTIONS];
}					t_cfg;

typedef enum		e_action_enum
{
	ERROR,
	ACCEPT,
	SHIFT,
	REDUCE
}					t_action_enum;

typedef union		u_action_union
{
	t_state			*state;
	t_production	*production;
}					t_action_union;

typedef struct		s_action
{
	t_action_enum	action_enum;
	t_action_union	action_union;
}					t_action;

typedef struct			s_ast_node
{
	t_token				*token;
	struct s_ast_node	*parent;
	t_list				*children;
}						t_ast_node;

typedef struct			s_ast_builder
{
	t_ast_node			*node;
	t_symbol			*symbol;
}						t_ast_builder;

typedef struct		s_lr_parser
{
	t_list			*states;
	t_action		**lr_tables;
	t_cfg			cfg;
	t_list			*tokens;
	t_list			*stack;
	t_ast_node		*root;
}					t_lr_parser;

typedef struct		s_grammar_holder
{
	char			*debug;
	char			relevant;
	char			replacing;
	int 			(*init_prod)(t_cfg *, t_symbol *);
}					t_grammar_holder;

t_grammar_holder	g_grammar[NB_SYMBOLS];

/*
** first_sets.c
*/
void		sh_init_first_sets(char first_sets[NB_TERMS]);
int			sh_compute_first_sets(t_cfg *cfg);
int			sh_compute_first_sets_str(t_cfg *cfg, char first_sets[NB_TERMS], t_list *w);
void		sh_process_transitive_first_set_2(char first_sets[NB_TERMS], int index);
void		sh_process_transitive_first_sets_2(char first_sets[NB_TERMS], t_symbol *prod_symbol);
/*
** follow_sets.c
*/
int     sh_compute_follow_sets(t_cfg *cfg);

/*
** debug.c
*/
void  	sh_print_symbol_list(t_list *symbols);
void  	sh_print_pda(t_list *symbols);
void	sh_print_symbol(t_symbol *symbol);
void	sh_print_token_list(t_list *list, t_cfg *cfg);
void	sh_print_non_terminals_productions(t_cfg *cfg);
void	sh_print_non_terminal_production(t_symbol *symbol);
void	print_first_sets(t_cfg *cfg);
void	print_follow_sets(t_cfg *cfg);
void	sh_process_print_set(t_cfg *cfg, char sets[NB_TERMS]);
void	sh_print_cfg(t_cfg *cfg);
void	sh_print_lr_table(t_lr_parser *parser);
void	sh_print_automata(t_lr_parser *parser, int depth);
void	sh_print_parser(t_lr_parser *parser, int depth);
void	sh_print_state(t_state *state, int depth);
void    sh_print_parser_state(t_lr_parser *parser);
void	sh_print_token(t_token *token, t_cfg *cfg);
void	sh_print_production(t_production *production);
void	sh_print_ast_builder(t_ast_builder *ast_builder);
void	sh_print_ast_parser(t_lr_parser *parser);

/*
** lr_parse.c
*/
int		sh_lr_parse(t_lr_parser *parser);
int			sh_process_test(void);
int			sh_parse_token_list(t_lr_parser *parser);
int			sh_is_term(t_symbol *symbol);

/*
** compute_lr_automata.c
*/
int     sh_compute_lr_automata(t_lr_parser *parser);
t_state	*sh_compute_first_state(t_lr_parser *parser);
int		sh_compute_closure(t_state *state, t_lr_parser *parser);
int		sh_compute_transitions(t_state *state, t_lr_parser *parser);

/*
** state.c
*/
t_state		*sh_new_state(void);
void		sh_free_state(t_state *state);
t_item		*sh_new_item(t_production *production, char lookaheads[NB_TERMS]);

/*
** compute_lr_tables.c
*/
int     sh_compute_lr_tables(t_lr_parser *parser);

/*
** init_cfg.c
*/
int		init_context_free_grammar(t_cfg *cfg);


int		init_parsing(t_lr_parser *parser);

/*
** traverse.c
*/
int		sh_traverse(t_ast_node *node);

int     sh_add_prod(t_symbol *symbol, t_cfg *cfg,
			int nb_symbols, ...);

t_cfg		*g_cfg;

int		sh_index(t_symbol_id id);

int		sh_init_prod_program(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_complete_commands(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_complete_command(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_list(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_and_or(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_pipeline(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_pipe_sequence(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_command(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_compound_command(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_subshell(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_compound_list(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_term(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_for_clause(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_name(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_in(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_wordlist(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_case_clause(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_case_list_ns(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_case_list(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_case_item_ns(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_case_item(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_pattern(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_if_clause(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_else_part(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_while_clause(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_until_clause(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_function_definition(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_function_body(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_fname(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_brace_group(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_do_group(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_simple_command(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_cmd_name(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_cmd_word(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_cmd_prefix(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_cmd_suffix(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_redirect_list(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_io_redirect(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_io_file(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_filename(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_io_here(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_here_end(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_newline_list(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_linebreak(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_separator_op(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_separator(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_sequential_sep(t_cfg *cfg, t_symbol *symbol);

#endif
