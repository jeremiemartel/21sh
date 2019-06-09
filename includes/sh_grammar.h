/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_grammar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:43:07 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/09 19:09:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_GRAMMAR_H
# define SH_GRAMMAR_H

# include <stdarg.h>
# include "libft.h"
# include "sh_tokens.h"
# include "sh_lexer.h"

# define DEBUG_BUFFER	50

typedef struct		s_ast_node	t_ast_node;
typedef struct		s_context	t_context;
typedef struct		s_shell		t_shell;

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

typedef struct		s_cfg
{
	t_symbol		start_symbol;
	t_symbol		symbols[NB_SYMBOLS];
	t_production	productions[NB_PRODUCTIONS];
}					t_cfg;

typedef struct		s_grammar_holder
{
	char			*debug;
	char			replacing;
	char			relevant;
	int 			(*init_prod)(t_cfg *, t_symbol *);
	int				(*traverse)(t_ast_node *this, t_context *context);
}					t_grammar_holder;

t_grammar_holder	g_grammar[NB_SYMBOLS];

/*
** first_sets.c
*/
void		sh_init_first_sets(char first_sets[NB_TERMS]);
int			sh_compute_first_sets(t_cfg *cfg);
int			sh_compute_first_sets_str(char first_sets[NB_TERMS], t_list *w);
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
void	sh_print_token(t_token *token, t_cfg *cfg);
void	sh_print_production(t_production *production);

/*
** init_cfg.c
*/
int		init_context_free_grammar(t_cfg *cfg);

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
