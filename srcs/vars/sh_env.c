/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 14:52:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/18 12:36:16 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_env_update_exit_status_process_ret(t_context *context, int res)
{
	if (!context->exit_status_set)
	{
		context->exit_status = EXIT_STATUS(res);
		context->exit_status_set = 1;
		context->shell->ret_value = EXIT_STATUS(res);
		if (sh_verbose_exec())
		{
			ft_dprintf(2, COLOR_CYAN"context exit status set : %d\n"COLOR_END,
			EXIT_STATUS(res));
			ft_dprintf(2, COLOR_CYAN"Process signal sent : %d\n"COLOR_END,
			res);
		}
	}
	return ;
}

void	sh_env_update_exit_status(t_context *context, int res)
{
	if (!context->exit_status_set)
	{
		context->exit_status = res;
		context->exit_status_set = 1;
		context->shell->ret_value = res;
		// context->shell->exit_value = context->exit_status;
		if (sh_verbose_exec())
			ft_dprintf(2, COLOR_CYAN"context exit status set : %d\n"COLOR_END,
			context->exit_status);
	}
	return ;
}

void	sh_env_update_exit_status_shell(t_shell *shell, int res)
{
	shell->ret_value = res;
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"shell returned value set : %d\n"COLOR_END,
			shell->ret_value);
}

int		sh_env_update_status_and_question(t_context *context, int res)
{
	sh_env_update_exit_status(context, res);
	return (sh_env_update_question_mark(context));
}

int		sh_env_update_question_mark_shell(t_shell *shell)
{
	char	*str;
	int		ret;

	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"Updating ? <=> %d\n"COLOR_END,
		shell->ret_value);
	if (!(str = ft_itoa(shell->ret_value)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark_shell"));
	ret = sh_vars_assign_key_val(shell->env, NULL, "?", str);
	free(str);
	return (ret);
}

int		sh_env_update_question_mark(t_context *context)
{
	char	*str;
	int		res;

	if (!context->exit_status_set)
		return (ERROR);
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"Updating ? <=> %d\n"COLOR_END,
		context->exit_status);
	if (!(str = ft_itoa(context->exit_status)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark"));
	res = sh_vars_assign_key_val(context->env, NULL, "?", str);
	free(str);
	context->exit_status_set = 0;
	return (res);
}
