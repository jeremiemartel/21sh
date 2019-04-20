/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:08:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/20 11:00:20 by jmartel          ###   ########.fr       */
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
** If set to True, lexer will print additionnal informations
*/
# define LEX_DEBUG	0

/*
** Max len for the token value
*/
# define LEX_TOKEN_VALUE_LEN	250

/*
** Possible states for the lexer, returned by lexer functions
*/
# define LEX_END		FAILURE + SUCCESS + 2
# define LEX_ERR		FAILURE
# define LEX_CONTINUE	FAILURE + SUCCESS + 1
# define LEX_OK			SUCCESS

typedef struct		s_lexer
{
	char			c;
	char			*input;
	int				tok_start;
	int				tok_len;
	int				current_id;
	int				quoted;
	t_list			*list;
	t_dy_tab 		*env;
}					t_lexer;

/*
** Expansion header
*/
typedef enum		e_exp_type
{
	LEX_EXP_VAR = 1,
	LEX_EXP_PARAM,
	LEX_EXP_CMD,
	LEX_EXP_ARITH,
	LEX_EXP_TILDE,
}					t_exp_type;

typedef struct		s_pattern
{
	char			start[4];
	char			end[4];
	int				len_s;
	int				len_e;
}					t_pattern;

typedef struct		s_expansion
{
	t_dy_str			*res;
	char			*original;
	t_exp_type		type;
	t_pattern		pattern;
}					t_expansion;

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
	char			value[LEX_TOKEN_VALUE_LEN + 1];
}					t_token;

/*
** lexer.c
*/
int					lexer(char *input, t_list **tokens, t_dy_tab *env);

/*
** sh_lexer_quoting.c
*/
int					lexer_quoting_backslash(t_lexer *lexer);
int					lexer_quoting_double_quote(t_lexer *lexer);
int					lexer_quoting_simple_quote(t_lexer *lexer);

/*
** lexer_expansions.c
*/
int					lexer_expansion(t_lexer *lexer, char **input);
int					lexer_expansion_replace(
						t_expansion *expansion, char **input);

/*
** lexer_expansion_detect.c
*/
int					lexer_expansion_detect(
						char *input, t_expansion *exp);
void				lexer_expansion_detect_fill_pattern(
						t_expansion *expansion, char *start, char *end, int len);
int					lexer_expansion_detect_fill_expansion(
						char *input, t_expansion *exp);

/*
** lexer_expansion_process.c
*/
int					lexer_expansion_process(
						t_lexer *lexer, t_expansion *expansion);
int					lexer_expansion_process_command(
						t_lexer *lexer, t_expansion *expansion);
int					lexer_expansion_process_arithmetic(
						t_lexer *lexer, t_expansion *expansion);
int					lexer_expansion_process_parameter(
						t_lexer *lexer, t_expansion *expansion);
int					lexer_expansion_process_variable(
						t_lexer *lexer, t_expansion *expansion);

/*
** lexer_expansion_process_tilde.c
*/
int					lexer_expansion_process_tilde(
						t_lexer *lexer, t_expansion *expansion);

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
void				t_token_show(t_token *token);
void				t_token_show_id(int i);
void				t_token_update_id(int id, t_token *token);

/*
** t_expansion.c
*/
void				t_expansion_free(t_expansion *expansion);

#endif
