/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/19 07:39:44 by jmartel          ###   ########.fr       */
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
	LEX_TOK_BACK_SLASH ='\\',
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
	LEX_TOK_AND_IF		= '&' + 0xff00 * '&',				//&&
	LEX_TOK_OR_IF		= '|' + 0xff00 * '|',				//||
	LEX_TOK_DSEMI		= ';' + 0xff00 * ';',				//;;
	LEX_TOK_DLESS		= '<' + 0xff00 * '<',				//<<
	LEX_TOK_DGREAT		= '>' + 0xff00 * '>',				//>>
	LEX_TOK_LESSAND		= '<' + 0xff00 * '&',				//<&
	LEX_TOK_GREATAND	= '>' + 0xff00 * '&',				//>&
	LEX_TOK_LESSGREAT	= '<' + 0xff00 * '>',				//<>
	LEX_TOK_DLESSDASH	= '<' + 0xff00 * '<' + 0xff0000 * '-',	//<<-
	LEX_TOK_CLOBBER		= '>' + 0xff00 * '|',				//>|
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

# define LEX_TOKEN_VALUE_LEN	250

# define LEX_END		3
# define LEX_ERR		2
# define LEX_CONTINUE	1
# define LEX_OK			0

# define LEX_EOF	-1		//char used to stop lexer

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
int         lexer_expansion(t_lexer *lexer);
int			lexer_parameter_expansion(t_lexer *lexer);
int			lexer_arithmetic_expression(t_lexer *lexer);
int			lexer_command_substitution(t_lexer *lexer);

/*
** t_lexer.c
*/
void		lexer_init(t_lexer *lexer, int tok_start, char *input);
int			lexer_add_token(t_lexer *lexer);
void		lexer_show(t_lexer *lexer);

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

#endif
