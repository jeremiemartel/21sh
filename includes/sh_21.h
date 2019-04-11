/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/11 17:44:15 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

# include <stdarg.h>

# include "libft.h"

typedef enum	e_token_id
{
	LEX_TOK_UNKNOWN = 0,
	//simple operators
	LEX_TOK_PIPE = '|',
	LEX_TOK_AND = '&',
	LEX_TOK_SEMICOL = ';',
	LEX_TOK_LESS = '<',
	LEX_TOK_GREAT = '>',
	LEX_TOK_OPN_PAR = '(',
	LEX_TOK_CLS_PAR = ')',
	LEX_TOK_DOLLAR = '$',
	//Quoting tokens
	LEX_TOK_BACK_SLASH = '\\',
	LEX_TOK_QUOTE_BACK = '`',
	LEX_TOK_QUOTE_SPL = '\'',
	LEX_TOK_QUOTE_DBL = '"',
	LEX_TOK_SPACE = ' ',
	LEX_TOK_TAB = '\t',
	LEX_TOK_NEWLINE = '\n',
	//Special chars
	LEX_TOK_STAR = '*',
	LEX_TOK_QUEST = '?',
	LEX_TOK_HASH = '#',
	LEX_TOK_TILD = '~',
	LEX_TOK_EQUAL = '=',
	LEX_TOK_PERCENT = '%',
	//Composed operators
	LEX_TOK_AND_IF = '&' + 0xff00 * '&',				//&&
	LEX_TOK_OR_IF = '|' + 0xff00 * '|',				//||
	LEX_TOK_DSEMI = ';' + 0xff00 * ';',				//;;
	LEX_TOK_DLESS = '<' + 0xff00 * '<',				//<<
	LEX_TOK_DGREAT = '>' + 0xff00 * '>',				//>>
	LEX_TOK_LESSAND = '<' + 0xff00 * '&',				//<&
	LEX_TOK_GREATAND = '>' + 0xff00 * '&',				//>&
	LEX_TOK_LESSGREAT = '<' + 0xff00 * '>',				//<>
	LEX_TOK_DLESSDASH = '<' + 0xff00 * '<' + 0xff0000 * '-',	//<<-
	LEX_TOK_CLOBBER = '>' + 0xff00 * '|',				//>|
	//Other
	LEX_TOK_TOKEN = 130,
	LEX_TOK_WORD,
	LEX_TOK_ASSIGMENT_NAME,
	LEX_TOK_NAME,
	LEX_TOK_IO_NUMBER,
}				t_token_id;

typedef struct	s_lexer
{
	char	c;
	char	*input;
	int		tok_start;
	int		tok_len;
	int		current_id;
	int		quoted;
	t_list	*list;
}				t_lexer;

/*
** Expansion header
*/
typedef enum	e_exp_type
{
	LEX_EXP_ERR = -1,
	LEX_EXP_OK = 0,
	LEX_EXP_VAR,
	LEX_EXP_PARAM,
	LEX_EXP_CMD,
	LEX_EXP_ARITH,
	LEX_EXP_TILDE,
}				t_exp_type;

/*
** pattern used to stock the expansions types
**		start : stock the first chars (ex : `, $, $(, .. )
**		end : stock the last chars (ex: `, ), )), }, ...)
*/

typedef struct	s_pattern
{
	char	start[4];
	char	end[4];
	int		len_s;
	int		len_e;
}				t_pattern;

typedef struct s_expansion
{
	t_dystr		*res;
	char		*original;
	char		*expansion;
	t_exp_type	type;
	t_pattern	pattern;
}				t_expansion;


# define LEX_TOKEN_VALUE_LEN	250

# define LEX_END		3
# define LEX_ERR		2
# define LEX_CONTINUE	1
# define LEX_OK			0

typedef struct	s_token
{
	t_token_id	id;
	char		value[LEX_TOKEN_VALUE_LEN + 1];
}				t_token;

/*
** lexer.c
*/
int			lexer(char *input);
void		ft_putstr_len(char *str, int len);

/*
** lexer_expansions.c
*/
int			lexer_expansion(t_lexer *lexer, char **input);
int			lexer_expansion_replace(t_expansion *expansion, char **input);

/*
** lexer_expansion_detect.c
**		Used to detect and fill a t_expansion struct, used to process
**		later to recursively process the expansion
*/
int			lexer_expansion_detect(char *input, t_expansion *exp);
void		lexer_expansion_detect_fill_pattern(t_expansion *expansion, char *start, char *end, int len);
int			lexer_expansion_detect_fill_expansion(char *input, t_expansion *exp);

/*
** lexer_expansion_process.c
*/
int			lexer_expansion_process(t_lexer *lexer, t_expansion *expansion);
int			lexer_expansion_process_command(t_lexer *lexer, t_expansion *expansion);
int			lexer_expansion_process_arithmetic(t_lexer *lexer, t_expansion *expansion);
int			lexer_expansion_process_parameter(t_lexer *lexer, t_expansion *expansion);
int			lexer_expansion_process_variable(t_lexer *lexer, t_expansion *expansion);

/*
** lexer_expansion_process_tilde.c
*/
int			lexer_expansion_process_tilde(t_lexer *lexer, t_expansion *expansion);

/*
** t_lexer.c
*/
void		lexer_init(t_lexer *lexer, int tok_start);
int			lexer_add_token(t_lexer *lexer);
void		lexer_show(t_lexer *lexer);
void		t_lexer_free(t_lexer *lexer);

/*
** lexer_rules.c
*/
int			lexer_rule1(t_lexer *lexer);
int			lexer_rule2(t_lexer *lexer);
int			lexer_rule3(t_lexer *lexer);
int			lexer_rule4(t_lexer *lexer);
int			lexer_rule5(t_lexer *lexer);
int			lexer_rule6(t_lexer *lexer);
int			lexer_rule7(t_lexer *lexer);
int			lexer_rule8(t_lexer *lexer);
int			lexer_rule9(t_lexer *lexer);
int			lexer_rule10(t_lexer *lexer);
int			lexer_rule11(t_lexer *lexer);

/*
** t_token.c
*/
t_token		*t_token_new(int id, char *value);
void		t_token_show(t_token *token);
void		t_token_show_id(int i);

/*
** t_expansion.c
*/
void		t_expansion_free(t_expansion *expansion);
void		t_expansion_show(t_expansion *exp);

#endif
