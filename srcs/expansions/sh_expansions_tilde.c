/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_tilde.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:56:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/06 15:30:02 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_expansions_tilde_detect(char *start)
{
	int		i;

	i = 0;
	if (start[i] != '~')
		return (-1);
	while (!ft_iswhite(start[i]) && start[i] != '/')
		i++;
	return (i);
}

int		sh_expansions_tilde_fill(t_expansion *exp, char *start)
{
	int		i;

	if ((i = sh_expansions_tilde_detect(start)) == -1)
		return (ERROR);
	if (!(exp->original = ft_strndup(start, i + 1)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_variable_detect_name (1)"));
	exp->expansion = NULL;
	exp->type = EXP_VAR;
	exp->process = &sh_expansions_tilde_process;
	t_expansion_show(exp);
	return (SUCCESS);
}

/*
** sh_expansions_tilde_process:
**	Choose between the two possible format of tilde expansion : 
**		case 1 : ~/ or ~
**		case 2 : ~user/
**
**	return SUCCESS or FAILURE
*/
int		sh_expansions_tilde_process(t_context *context, t_expansion *exp)
{
	if (!exp->original[1] || ft_iswhite(exp->original[1]) || exp->original[1] == '/')
		return (sh_expansions_tilde_1(context, exp));
	else
		return (sh_expansions_tilde_2(context, exp));
}
