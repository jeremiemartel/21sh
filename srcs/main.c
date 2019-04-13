/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/13 16:30:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			main(int argc, char **argv)
{
	char		*input;
	t_list		*tokens;

	tokens = NULL;
	if (argc == 1)
		return (0);
	input = ft_strdup(argv[1]);
	if (lexer(input, &tokens))
		return (1);
	if (sh_parser(tokens))
		return (1);
	ft_strdel(&input);
	return (0);
}
