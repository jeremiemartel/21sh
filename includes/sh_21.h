/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/01 19:00:36 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

#include "libft.h"

typedef struct		s_io//
{
	int				fdin;
	int				fdout;
	int				fderr;
}					t_io;

typedef struct		s_command//
{
	t_io			io;
	t_list			*args;
}					t_command;

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

typedef struct 		s_token
{
	t_tokenlist		token;
	char			value[250];	//adjust size
}					t_token;

/*
** t_command.c
*/
t_command		*t_command_new(void);
void			t_command_free(t_list *cmd);
void			t_command_free_args(t_list *arg);
void			t_command_free_list(t_list *cmd);

#endif
