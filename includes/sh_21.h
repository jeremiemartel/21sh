/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/04 19:53:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

#include "libft.h"

# define SH_LEXER_AUTO_LEN	5

# define end	-1
# define error	-2

typedef struct		s_automate
{
	int				status;
	int				(*automate)(int status, char c);
}					t_automate;

typedef enum		e_tokenlist
{
	UNKNOWN = -1,
	SPACE,
	WHILE,
	GREAT,
	LESS,
	WORD,
}					t_tokenlist;

/*
** lexer.c
*/
int			ft_isseparator(char c);
int			sh_lexer(char *input);

/*
** lexer_automates.c
*/
int			sh_lexer_auto_while(int status, char c);
int			sh_lexer_auto_less(int status, char c);
int			sh_lexer_auto_great(int status, char c);
int			sh_lexer_auto_word(int status, char c);
int			sh_lexer_auto_space(int status, char c);

/*
** lexer_automates_tools.c
*/
void		sh_lexer_automate_init(t_automate automates[]);
void		sh_lexer_automate_run(t_automate automates[], char c);
int			sh_lexer_automate_check(t_automate automates[]);
void		sh_lexer_automate_show_status(t_automate automates[], char c);
void		sh_lexer_show_token(int token);

/*
typedef enum		e_tokenlist
{
	UNKNOWN,	//May be useless, need to see later
	TOKEN,		//token context dependent, transition state
	WORD,
	NAME,
	ASSIGMENT,
	IO_NUMBER,	//only digits and oneof '<' or '>'
	NEWLINE,	//'\n'
	DELIMITOR,	//';'
	DLESS,		//'<<'
	DGREAT,		//'>>'
	LESSAND,	//'<&'
	GREADAND,	//'>&'
	LESSGREAT,	//'<>'
	DLESSDASH,	//'<<-'
	CLOBBER		//'>|'
}					t_tokenlist;
*/

#endif
