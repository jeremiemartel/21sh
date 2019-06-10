/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:38:26 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 17:19:20 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_variable_detect:
**	Function used to detect valid variable expansion.
**
** return :
**		-1 : String given is invalid
**		<0 : Lenght of the valid expansion detecteda
*/

int		sh_expansions_variable_detect(char *start)
{
	int		i;

	i = 1;
	if (*start != '$')
		return (-1);
	if (!(ft_isalpha(start[i]) || start[i] == '_'))
		return (-1);
	i++;
	while (start[i] && (ft_isalnum(start[i]) || start[i] == '_'))
		i++;
	i--;
	return (i);
}

/*
** sh_expansions_variable_fill:
**	Try to fill type, expansion, original and process fields of a t_expansion
**	structure.
**
**	Return Value:
**		FAILURE : malloc error
**		ERROR : expansion is invalid
**		SUCCESS : successfully filled expansion
*/

int		sh_expansions_variable_fill(t_expansion *exp, char *start)
{
	int		i;

	if ((i = sh_expansions_variable_detect(start)) == -1)
		return (ERROR);
	if (!(exp->original = ft_strndup(start, i + 1)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_variable_detect_name (1)"));
	if (!(exp->expansion = ft_strndup(start + 1, i + 1)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_exp_init_detect_pattern (2)"));
	exp->type = EXP_VAR;
	exp->process = &sh_expansions_variable_process;
	return (SUCCESS);
}

/*
** sh_expansions_variable_process:
**	Function called to fill the expansion's res field using informations given
**	in the t_expansion structure.
**	This function is after expansion detection and before field splitting
**	They are two main cases :
**		if first char is a '#' result is lenght of the parameter
**		else result is value of this parameter
**
**	return Value:
**		FAILURE : malloc error
**		SUCCESS : Successfullly filled exp->res
*/

int		sh_expansions_variable_process(t_context *context, t_expansion *exp)
{
	char	*value;

	value = sh_vars_get_value(context->env, context->vars, exp->expansion + 1);
	if (*exp->expansion != '#')
		value = sh_vars_get_value(context->env, context->vars, exp->expansion);
	if (*exp->expansion == '#')
	{
		if (!value)
			exp->res = ft_dy_str_new_str("0");
		else
			exp->res = ft_dy_str_new_ptr(ft_itoa(ft_strlen(value)));
	}
	else
	{
		if (!value)
			exp->res = ft_dy_str_new_str("");
		else
			exp->res = ft_dy_str_new_str(value);
	}
	if (!(exp->res))
		return (ft_perror(SH_ERR1_MALLOC, "sh_expansions_variable (1)"));
	return (SUCCESS);
}
