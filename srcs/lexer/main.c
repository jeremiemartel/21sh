/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/19 18:23:13 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			main(int argc, char **argv)
{
	char		*input;

	if (argc == 1)
		return (0);
	input = ft_strdup(argv[1]);
	lexer(input);
	ft_strdel(&input);
	return (0);
	(void)argc;
	(void)argv;
}
