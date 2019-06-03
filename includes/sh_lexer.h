/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:08:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/24 12:26:10 by ldedier          ###   ########.fr       */
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
# define LEX_UNKNOWN	FAILURE + SUCCESS + 4
# define LEX_CANCEL		FAILURE + SUCCESS + 3
# define LEX_END		FAILURE + SUCCESS + 2
# define LEX_ERR		FAILURE
# define LEX_CONTINUE	FAILURE + SUCCESS + 1
# define LEX_OK			SUCCESS

typedef struct s_shell		t_shell;
typedef struct s_expansion	t_expansion;

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
	t_dy_tab		*vars;
	t_shell			*shell;
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

struct				s_expansion
{
	t_dy_str			*res;
	char			*original;
	char			*expansion;
	t_exp_type		type;
	int				(*process)(t_lexer *, t_expansion *);
};

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
** sh_lexer_exp.c
*/
int					sh_lexer_exp(t_lexer *lexer);
int					sh_lexer_exp_recursive(t_lexer *lexer, char **input, char *original);

/*
** sh_lexer_exp_init.c
*/
int					sh_lexer_exp_init(char *original, t_expansion *exp);
int					sh_exp_init_detect_pattern(t_expansion *exp, char *start, char *pattern, int type);
int					sh_exp_init_detect_chars(t_expansion *exp, char *start, char *pattern, int type);
int					sh_lexer_exp_init_process(t_expansion *exp);

/*
** sh_lexer_exp_process.c
*/
int					sh_lexer_exp_variable(t_lexer *lexer, t_expansion *exp);
int					sh_lexer_exp_parameter(t_lexer *lexer, t_expansion *exp);
int					sh_lexer_exp_command(t_lexer *lexer, t_expansion *exp);
int					sh_lexer_exp_arithmetic(t_lexer *lexer, t_expansion *exp);

/*
** sh_lexer_exp_process_tilde.c
*/
int					sh_lexer_exp_tilde(t_lexer *lexer, t_expansion *exp);
int					sh_lexer_exp_tilde_1(t_lexer *lexer, t_expansion *exp);
int					sh_lexer_exp_tilde_2(t_lexer *lexer, t_expansion *exp);

/*
** sh_lexer_exp_process_param.c
*/
int					sh_lexer_exp_parameter_format(t_expansion *exp, char *format);
char				*sh_lexer_exp_parameter_get_param(t_lexer *lexer, t_expansion *exp);
char				*sh_lexer_exp_parameter_get_word(t_lexer *lexer, t_expansion *exp, char *format);
int					sh_lexer_exp_parameter(t_lexer *lexer, t_expansion *exp);
int					sh_lexer_exp_minus(t_lexer *lexer, t_expansion *exp, char *format);
int					sh_lexer_exp_equal(t_lexer *lexer, t_expansion *exp, char *format);
int					sh_lexer_exp_quest(t_lexer *lexer, t_expansion *exp, char *format);
int					sh_lexer_exp_plus(t_lexer *lexer, t_expansion *exp, char *format);
int					sh_lexer_exp_percent(t_lexer *lexer, t_expansion *exp, char *format);
int					sh_lexer_exp_hash(t_lexer *lexer, t_expansion *exp, char *format);


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
void				t_token_free(t_token *token);
void				t_token_free_list(t_list *head);
void				t_token_show(t_token *token);
void				t_token_show_id(int i);
void				t_token_update_id(int id, t_token *token);

/*
** t_expansion.c
*/
void				t_expansion_free_content(t_expansion *expansion);
void				t_expansion_show(t_expansion *exp);

#endif
