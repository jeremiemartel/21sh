/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:31:41 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/26 10:28:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include <stdarg.h>
# include "libft.h"
# include "sh_tokens.h"
# include "sh_grammar.h"
# include "sh_exec.h"

typedef struct		s_ast_node t_ast_node;
typedef struct		s_shell t_shell;
typedef struct		s_stack_item t_stack_item;

typedef struct		s_state
{
	t_list			*transitions;
	t_list			*items;
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

typedef enum		e_action_enum
{
	ERROR,
	ACCEPT,
	SHIFT,
	REDUCE
}					t_action_enum;

typedef union		u_action_union
{
//	t_state			*state;
	int				state_index;
	t_production	*production;
}					t_action_union;

typedef struct		s_action
{
	t_action_enum	action_enum;
	t_action_union	action_union;
}					t_action;

typedef struct			s_ast_builder
{
	t_ast_node			*cst_node;
	t_ast_node			*ast_node;
	t_symbol			*symbol;
}						t_ast_builder;


struct			s_ast_node
{
	t_token				*token;
	t_symbol			*symbol;
	t_metadata			metadata;
	t_list				*children;
	t_ast_node			*relative;
	t_ast_builder		*builder;
};

typedef enum			e_stack_enum
{
	E_STACK_AST_BUILDER,
	E_STACK_STATE_INDEX
}						t_stack_enum;

typedef union			u_stack_union
{
	int					state_index;
	t_ast_builder		*ast_builder;
}						t_stack_union;

struct					s_stack_item
{
	t_stack_union		stack_union;
	t_stack_enum		stack_enum;
	char				transfered_ast_builder;
};

typedef struct		s_lr_parser
{
	t_list			*states;
	t_action		**lr_tables;
	t_cfg			cfg;
	t_list			*tokens;
	t_list			*stack;
	t_ast_node		*ast_root;
	t_ast_node		*cst_root;
	int				nb_states;
}					t_lr_parser;

/*
** transitive_first_sets.c
*/
void	sh_process_transitive_first_sets_2(char first_sets[NB_TERMS],
			t_symbol *prod_symbol);
void	sh_process_transitive_first_sets(t_symbol *symbol,
			t_symbol *prod_symbol, int *changes);
void	sh_process_transitive_first_set(t_symbol *symbol,
			int index, int *changes);

/*
** first_sets_tools.c
*/

int		has_eps_prod(t_symbol *symbol);

/*
** parser.c
*/
int			sh_parser(t_list *tokens, t_shell *shell);

/*
** lr_parse.c
*/
t_stack_item	*new_stack_item(t_ast_builder *ast_builder, int state_index);
int				sh_lr_parse(t_lr_parser *parser);
int				sh_process_test(void);
int				sh_parse_token_list(t_lr_parser *parser);
int				sh_is_term(t_symbol *symbol);

/*
** compute_lr_automata.c
*/
int     sh_compute_lr_automata(t_lr_parser *parser);
t_state	*sh_compute_first_state(t_lr_parser *parser);
int		sh_compute_closure(t_state *state, t_lr_parser *parser);
int		sh_compute_transitions(t_state *state, t_lr_parser *parser);


/*
** closure_tools.c
*/
t_item		*sh_get_state_item(t_production *production,
				t_state *state);
t_item		*sh_new_item(t_production *production, char lookaheads[NB_TERMS]);
int			sh_process_add_to_closure(t_production *production,
				t_state *state, char lookaheads[NB_TERMS]);
t_symbol	*sh_get_next_non_terminal(t_item *item, t_list **w_ptr);
int			sh_update_lookaheads(t_item *item, char lookaheads[NB_TERMS]);

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
int		sh_init_parsing(t_lr_parser *parser);

/*
** transition_tools.c
*/

int				sh_is_eligible_for_transition(t_state *state, t_item *item);
t_state			*sh_get_state_by_symbol(t_item *item, t_lr_parser *parser);
t_state			*sh_get_state_by_transition(t_state *state, t_symbol *symbol);
t_transition	*sh_new_transition(t_state *to, t_symbol *symbol);
t_item			*sh_new_item_advance(t_item *item);

/*
** traverse.c
*/
int		sh_traverse(t_ast_node *node);
int     sh_add_prod(t_symbol *symbol, t_cfg *cfg, int nb_symbols, ...);

/*
** reduce.c
*/
int		sh_process_reduce(t_production *production, t_lr_parser *parser);

/*
** lr_parse.c
*/
int     sh_process_shift_adds(t_lr_parser *parser,
			t_ast_builder *ast_builder, int state_index);

/*
** reduce_tools.c
*/
t_ast_builder	*sh_new_ast_builder_no_node(t_symbol *symbol);
t_ast_builder	*sh_new_ast_builder_no_token(t_symbol *symbol);
t_ast_builder   *sh_new_ast_builder(t_token *token, t_symbol *symbol);
int				sh_is_replacing(t_ast_builder *ast_builder);

/*
** debug.c
*/
void    sh_print_lr_table(t_lr_parser *parser);
void	sh_print_automata(t_lr_parser *parser, int depth);
void	sh_print_parser(t_lr_parser *parser, int depth);
void	sh_print_state(t_state *state, int depth);
void	sh_print_parser_state(t_lr_parser *parser);
void	sh_print_token(t_token *token, t_cfg *cfg);
void    sh_print_ast_builder(t_ast_builder *ast_builder);
void    sh_print_ast_parser(t_lr_parser *parser);
void	sh_print_ast(t_ast_node *node, int depth);

/*
** free_parser.c
*/

void	sh_free_parser(t_lr_parser *parser);
void	sh_free_stack_item(t_stack_item *stack_item);
void	sh_free_stack_item_lst(void *stack_item, size_t dummy);
void	sh_free_production(void *p, size_t dummy);

/*
** fill_lr_tables.c
*/
void	sh_fill_tables(t_lr_parser *parser);

/*
** shift.c
*/
int		sh_process_shift(int state_index, t_lr_parser *parser);
#endif
