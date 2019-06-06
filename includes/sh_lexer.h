/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:08:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/06 13:49:50 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXER_H
# define SH_LEXER_H

# include "libft.h"
# include "sh_tokens.h"

/*
** getpwnam: used in lexer_expansion_process_tilde.c
*/
# include <pwd.h>

/*
** Possible states for the lexer, returned by lexer functions
*/
# define LEX_OK			SUCCESS
# define LEX_ERR		ERROR
# define LEX_FAIL		FAILURE
# define LEX_CONTINUE	FAILURE + SUCCESS + 1
# define LEX_END		FAILURE + SUCCESS + 2
# define LEX_CANCEL		FAILURE + SUCCESS + 3

typedef struct s_shell		t_shell;

typedef struct		s_lexer
{
	char			c;
	char			*input;
	int				tok_start;
	int				tok_len;
	int				current_id;
	char			quoted;
	char			expansion;
	t_list			*list;
	t_dy_tab 		*env;
	t_dy_tab		*vars;
	t_shell			*shell;
}					t_lexer;

typedef struct		s_token_union
{
	int				ival;
	double			fval;
	char			*str;
}					t_token_union;

typedef enum		e_token_type
{
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_STR
}					t_token_type;

typedef struct		s_token
{
	t_token_type	token_type;
	t_token_union	token_union;
	t_symbol_id		id;
	int				index;
	char			*value;
	char			quoted;
	char			expansion;
}					t_token;

/*
** lexer.c
*/
int					sh_lexer(char *input, t_list **tokens, t_shell *shell);

/*
** sh_lexer_quoting.c
*/
int					lexer_quoting_backslash(t_lexer *lexer);
int					lexer_quoting_start_quote(t_lexer *lexer);
int					lexer_quoting_double_quote(t_lexer *lexer);
int					lexer_quoting_simple_quote(t_lexer *lexer);

/*
** lexer_rules.c
*/
int					lexer_rule1(t_lexer *lexer);
int					lexer_rule2(t_lexer *lexer);
int					lexer_rule3(t_lexer *lexer);
int					lexer_rule4(t_lexer *lexer);
int					lexer_rule5(t_lexer *lexer);
int					lexer_rule6(t_lexer *lexer);
int					lexer_rule7(t_lexer *lexer);
int					lexer_rule8(t_lexer *lexer);
int					lexer_rule9(t_lexer *lexer);
int					lexer_rule10(t_lexer *lexer);
int					lexer_rule11(t_lexer *lexer);
int					lexer_is_operator(int op);

/*
** sh_lexer_exp.c
*/
int					sh_lexer_exp(t_lexer *lexer);

/*
** t_lexer.c
*/
void				lexer_init(t_lexer *lexer, int tok_start);
int					lexer_add_token(t_lexer *lexer);
void				lexer_show(t_lexer *lexer);
void				t_lexer_free_token_list(t_list *list);

/*
** t_token.c
*/
t_token				*t_token_new(int id, char *value);
void				t_token_free(t_token *token);
void				t_token_free_list(t_list *head);
void				t_token_show(t_token *token);
void				t_token_show_id(int i);
void				t_token_update_id(int id, t_token *token);

#endif
