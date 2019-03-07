/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/07 18:35:24 by jmartel          ###   ########.fr       */
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
	LEX_TOK_AND_IF = 130,
	LEX_TOK_OR_IF,
	LEX_TOK_DSEMI,
	LEX_TOK_DLESS,
	LEX_TOK_DGREAT,
	LEX_TOK_LESSAND,
	LEX_TOK_GREATAND,
	LEX_TOK_LESSGREAT,
	LEX_TOK_DLESSDASH,
	LEX_TOK_CLOBBER,
	//Other
	LEX_TOK_WORD,
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

#endif
