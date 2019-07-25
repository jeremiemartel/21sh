/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 14:52:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/25 23:05:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_env_update_ret_value_wait_result:
**	If not already set update the value of shell->ret_value.
**	res is considered as the value stored by a wait (2) function.
*/

void	sh_env_update_ret_value_wait_result(t_shell *shell, int res)
{
	if (!shell->ret_value_set)
	{
		if ((res & 0xff) == 2)
			shell->ret_value = SH_RET_CTRL_C;
		else
			shell->ret_value = EXIT_STATUS(res);
		shell->ret_value_set = 1;
		if (sh_verbose_exec())
		{
			ft_dprintf(2, COLOR_CYAN"ret value set : %d\n"COLOR_END,
			EXIT_STATUS(res));
			ft_dprintf(2, COLOR_CYAN"Process signal sent : %d\n"COLOR_END,
			res & 0xff);
		}
	}
	return ;
}

/*
** sh_env_update_ret_value:
**	If not already set update the value of shell->ret_value.
*/

void	sh_env_update_ret_value(t_shell *shell, int res)
{
	if (!shell->ret_value_set)
	{
		shell->ret_value = res;
		shell->ret_value_set = 1;
		if (sh_verbose_exec())
			ft_dprintf(2, COLOR_CYAN"ret value set : %d\n"COLOR_END, res);
	}
	return ;
}

/*
** sh_env_update_status_and_question:
**	Update $? env variable. It use shell->ret_value, if it had been set.
**
**	Returned Values:
**		ERROR : ret_value unset
**		FAILURE : malloc error
**		SUCCESS
*/

int		sh_env_update_question_mark(t_shell *shell)
{
	char	*str;
	int		res;

	if (!shell->ret_value_set)
		return (ERROR);
	shell->ret_value_set = 0;
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"Updating ? <=> %d\n"COLOR_END,
		shell->ret_value);
	if (!(str = ft_itoa(shell->ret_value)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark"));
	res = sh_vars_assign_key_val(shell->env, NULL, "?", str);
	free(str);
	return (res);
}

/*
** sh_env_update_ret_value_and_question:
**	Update status and $? in one function.
**
**	Returned Values:
**		ERROR : ret_value unset
**		FAILURE : malloc error
**		SUCCESS
*/

int		sh_env_update_ret_value_and_question(t_shell *shell, int res)
{
	sh_env_update_ret_value(shell, res);
	return (sh_env_update_question_mark(shell));
}
