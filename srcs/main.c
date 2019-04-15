/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/15 13:53:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_dy_tab	*main_init_env(char **env)
{
	int			len;
	int			i;
	t_dy_tab	*tbl;

	len = ft_strtab_len(env);
	if (!(tbl = ft_dy_tab_new(len + 1)))
		return (ft_perrorn(SH_ERR1_MALLOC, "main_init_env"));
	i = 0;
	while (i < len)
	{
		if (ft_dy_tab_add_str(tbl, env[i]))
		{
			ft_dy_tab_del(tbl);
			return (ft_perrorn(SH_ERR1_MALLOC, "main_init_env"));
		}
		i++;
	}
	return (tbl);
}

int			main(int argc, char **argv, char **original_env)
{
	char		*input;
	t_list		*tokens;
	t_dy_tab	*env;

	tokens = NULL;
	if (!(env = main_init_env(original_env)))
		return (FAILURE);
	if (argc == 1)
		return (SUCCESS);
	input = ft_strdup(argv[1]);
	if (lexer(input, &tokens, env) != SUCCESS)
	{
		ft_dy_tab_del(env);
		ft_strdel(&input);
		return (FAILURE);
	}
	if (sh_parser(tokens))
		return (FAILURE);
//	t_lexer_free_token_list(tokens);
	ft_dy_tab_del(env);
	ft_strdel(&input);
	return (SUCCESS);
}
