/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_parameter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:52:11 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/05 16:21:28 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_parameter_detect:
**	Function used to detect valid parameter expansion.
**
** return :
**		-1 : String given is invalid
**		<0 : Lenght of the valid expansion detecteda
*/

int		sh_expansions_parameter_detect(char *start)
{
	int		i;
	int		quoted;

	i = 0;
	quoted = 0;
	while (start[i] && !(!quoted && start[i] == '}'))
	{
		if (start[i] == '\\' && start[i + 1])
			i += 2;
		else if (!quoted && (start[i] == '\'' || start[i] == '"'))
		{
			quoted = start[i];
			i++;
		}
		else if (quoted && start[i] == quoted)
		{
			quoted = 0;
			i++;
		}
		else
			i++;
	}
	if (!start[i])
		return (-1);
	return (i);
}

/*
** sh_expansions_parameter_fill:
**	Try to fill type, expansion, original and process fields of a t_expansion
**	structure.
**
**	Return Value:
**		FAILURE : malloc error
**		ERROR : expansion is invalid
**		SUCCESS : successfully filled expansion
*/

int		sh_expansions_parameter_fill(t_expansion *exp, char *start)
{
	int		i;

	if ((i = sh_expansions_parameter_detect(start)) == -1)
		return (ERROR);
	if (!(exp->original = ft_strndup(start, i + 1)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_exp_init_detect_pattern (1)"));
	if (!(exp->expansion = ft_strndup(start + 2, i - 2)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_exp_init_detect_pattern (2)"));
	exp->type = EXP_PARAM;
	exp->process = &sh_expansions_parameter_process;
	return (SUCCESS);
}

/*
** sh_expansions_parameter_detect_special_var:
**	Detect if expansion is a special variable expansion for expample:
**		${$} or ${?}
**	This function is directly linked to sh_expansions_variable_detect_special,
**	You need to modify them together, cause they detect the same special vars,
**	not using the same method.
**
**	Returned Values:
**		True : special var had been detected
**		Else : continue normal parameter process
*/

static int	sh_expansions_parameter_detect_special_var(t_expansion *exp)
{
	char	*expansion;

	expansion = exp->expansion;
	if (*expansion == '#')
		expansion++;
	if (ft_strequ(expansion, "$") || ft_strequ(expansion, "?"))
		return (1);
	return (0);
}

/*
** sh_expansions_variable_process:
**	Function called to fill the expansion's res field using informations given
**	in the t_expansion structure.
**
**	return Value:
**		FAILURE : malloc error
**		SUCCESS : Successfullly filled exp->res
*/

int		sh_expansions_parameter_process(t_context *context, t_expansion *exp)
{
	char	format[4];

	if (sh_expansions_parameter_detect_special_var(exp))
		return (sh_expansions_variable_process(context, exp));
	if (!ft_strpbrk(exp->expansion, ":-=?+%"))
	{
		if (exp->expansion[0] == '#')
			return (sh_expansions_variable_process(context, exp));
		if (sh_expansions_variable_detect(exp->expansion) == -1)
			return (sh_perror_err(exp->original, "bad substitution (1)"));
		return (sh_expansions_variable_process(context, exp));
	}
	if (sh_expansions_parameter_format(exp, format) != SUCCESS)
		return (ERROR);
	if (ft_strstr(":-", format) || ft_strstr("-", format))
		return (sh_expansions_parameter_minus(context, exp, format));
	else if (ft_strstr(":=", format) || ft_strstr("=", format))
		return (sh_expansions_parameter_equal(context, exp, format));
	else if (ft_strstr(":?", format) || ft_strstr("?", format))
		return (sh_expansions_parameter_quest(context, exp, format));
	else if (ft_strstr(":+", format) || ft_strstr("+", format))
		return (sh_expansions_parameter_plus(context, exp, format));
	else
		return (sh_perror_err(exp->original, "bad substitution"));
	return (SUCCESS);
}
