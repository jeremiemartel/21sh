/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 14:52:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/15 17:47:53 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_env_update_exit_status(t_context *context, int res)
{
	if (!context->exit_status_set)
	{
		context->exit_status = res;// >> 8;
		context->exit_status_set = 1;
		context->shell->exit_value = context->exit_status;
		if (sh_verbose_exec())
			ft_dprintf(2, COLOR_CYAN"exit status set : %d\n"COLOR_END,
			context->exit_status);
	}
	return ;
}

int		sh_env_update_question_mark_shell(t_shell *shell, int res)
{
	char	*str;

	shell->ret_value = res >> 8;
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"Updating ? <=> "COLOR_END);
	if (!(str = ft_itoa(shell->ret_value)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark_shell"));
	res = sh_vars_assign_key_val(shell->env, NULL, "?", str);
	free(str);
	return (res);
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
