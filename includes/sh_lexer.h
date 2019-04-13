/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:08:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/13 11:31:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXER_H
# define SH_LEXER_H

# include "libft.h"
# include "sh_tokens.h"

typedef struct		s_lexer
{
	char	c;
	char	*input;
	int		tok_start;
	int		tok_len;
	int		current_id;
	int		quoted;
	t_list	*list;
}					t_lexer;

/*
** Expansion header
*/
typedef enum		e_exp_type
{
	LEX_EXP_ERR = -1,
	LEX_EXP_OK = 0,
	LEX_EXP_VAR,
	LEX_EXP_PARAM,
	LEX_EXP_CMD,
	LEX_EXP_ARITH,
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
	t_dystr			*res;
	char			*original;
	char			*expansion;
	t_exp_type		type;
	t_pattern		pattern;
}					t_expansion;

# define LEX_TOKEN_VALUE_LEN	250

# define LEX_END		3
# define LEX_ERR		2
# define LEX_CONTINUE	1
# define LEX_OK			0

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
int					lexer(char *input, t_list **tokens);
void				ft_putstr_len(char *str, int len);
int					sh_parser(t_list *tokens);

/*
** lexer_expansions.c
*/
int					lexer_expansion(t_lexer *lexer, char **input);

/*
** lexer_expansion_detect.c
*/
int					lexer_expansion_detect(char *input, t_expansion *expansion);
int					lexer_expansion_detect_command(
						char *input, t_expansion *expansion);
int					lexer_expansion_detect_arithmetic(
						char *input, t_expansion *expansion);
int					lexer_expansion_detect_parameter(
						char *input, t_expansion *expansion);
int					lexer_expansion_detect_variable(
						char *input, t_expansion *expansion);

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
** t_lexer.c
*/
void				lexer_init(t_lexer *lexer, int tok_start);
int					lexer_add_token(t_lexer *lexer);
void				lexer_show(t_lexer *lexer);
void				t_lexer_free(t_lexer *lexer);

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

/*
** t_token.c
*/
t_token				*t_token_new(int id, char *value);
void				t_token_show(t_token *token);
void				t_token_show_id(int i);

#endif
