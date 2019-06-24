/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:48:57 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/17 11:37:55 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_env_vars_update_question_mark(t_context *context, int res)
{
	char	*str;

	context->ret_value = res;
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"Updating ? <=> "COLOR_END);
	if (!(str = ft_itoa(res)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_update_question_mark"));
	if (sh_verbose_exec())
		ft_dprintf(2, COLOR_CYAN"%s\n"COLOR_END, str);
	res = sh_vars_assign_key_val(context->env, NULL, "?", str);
	free(str);
	return (res);
}
