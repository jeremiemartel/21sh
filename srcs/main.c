/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/25 18:58:50 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	main_exit_value(t_shell *shell, int ret)
{
	if (shell->ret_value_set || shell->ret_value)
	{
		if (sh_verbose_exec())
			ft_dprintf(2, "Using ret_value\n", ret);
		ret = shell->ret_value;
	}
	if (sh_verbose_exec())
		ft_dprintf(2, "Final returned value : %d\n", ret);
	ft_dprintf(0, "exit\n");
	return (ret);
}

int			main(int argc, char **argv, char **env)
{
	t_shell		shell;
	int			ret;

	(void)argc;
	(void)argv;
	init_signals();
	if (!isatty(0))
		ret = sh_process_canonical_mode(&shell, env);
	else
	{
		if (sh_init_terminal(&shell, env) != SUCCESS)
			return (FAILURE);
		if (sh_init_shell(&shell, env) != SUCCESS)
		{
			sh_free_all(&shell);
			return (sh_reset_shell(FAILURE));
		}
		ret = sh_process_noncanonical_mode(&shell);
	}
	return (main_exit_value(&shell, ret));
}
