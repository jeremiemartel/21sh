/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/02 11:17:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_lexer(char *input);

int			main(int argc, char **argv)
{
	int		token;

	if (argc == 1)
		return (0);
	token = sh_lexer(argv[1]);
	return (0);
	(void)argc;
	(void)argv;
}
/*
int			sh_lexer_auto_while(int status, char c)
{
	if (Status == error)
		return (error);
	
}

int			sh_lexer_auto_while(int status, char c)
{
	char	str[] = "while";

	if (status == error)
		return (error);
	if (Status == end)
		return (error);
	if (str[status] == c)
	{
		if (status == 4)
			return (end);
		return (status + 1);
	}
	return (error);
}
*/