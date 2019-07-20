/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 14:52:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/20 09:40:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_env_update_ret_value_fork_result(t_context *context, int res)
{
	if (!context->ret_value_set)
	{
		context->ret_value = EXIT_STATUS(res);
		context->ret_value_set = 1;
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

void	sh_env_update_ret_value(t_context *context, int res)
{
	if (!context->ret_value_set)
	{
		context->ret_value = res;
		context->ret_value_set = 1;
		context->shell->ret_value = res;
		if (sh_verbose_exec())
			ft_dprintf(2, COLOR_CYAN"context exit status set : %d\n"COLOR_END,
			context->ret_value);
	}
	return ;
}

void	sh_env_update_ret_value_shell(t_shell *shell, int res)
{
	if (!shell->ret_value_set)
	{
		shell->ret_value = res;
		shell->ret_value_set = 1;
		if (sh_verbose_exec())
			ft_dprintf(2, COLOR_CYAN"shell returned value set : %d\n"COLOR_END,
				shell->ret_value);
	}
	return ;
}

int		sh_env_update_status_and_question(t_context *context, int res)
{
	sh_env_update_ret_value(context, res);
	return (sh_env_update_question_mark(context));
}

int		sh_env_update_question_mark_shell(t_shell *shell)
{
	char	*str;
	int		ret;

	if (!shell->ret_value_set)
		return (ERROR);
	if (sh_verbose_exec())
	{
		ft_dprintf(2, COLOR_CYAN"Updating ? from shell <=> %d\n"COLOR_END,
		shell->ret_value);
	}
	if (!(str = ft_itoa(shell->ret_value)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark_shell"));
	ret = sh_vars_assign_key_val(shell->env, NULL, "?", str);
	free(str);
	shell->ret_value_set = 0;
	return (ret);
}

int		sh_env_update_question_mark(t_context *context)
{
	char	*str;
	int		res;

	if (!context->ret_value_set)
		return (ERROR);
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"Updating ? from context <=> %d\n"COLOR_END,
		context->ret_value);
	if (!(str = ft_itoa(context->ret_value)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark"));
	res = sh_vars_assign_key_val(context->env, NULL, "?", str);
	free(str);
	context->ret_value_set = 0;
	return (res);
}
