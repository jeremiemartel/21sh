/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_parameter_tools.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:35:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 17:43:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_expansions_parameter_fill_format(char *head, char *format, int n)
{
	format[n] = 0;
	n--;
	while (n >= 0)
	{
		format[n] = head[n];
		n--;
	}
	return ;
}

int			sh_expansions_parameter_format(t_expansion *exp, char *format)
{
	char	*head;
	int		i;

	head = exp->expansion;
	i = 0;
	if (*head == '#')
	{
		format[i] = '#';
		i++;
		head++;
	}
	if (!ft_isalpha(*head) && *head != '_')
		return (ft_perror_err(exp->original, "bad substitution"));
	head++;
	while (ft_isalnum((int)*head) || *head == '_')
		head++;
	if (ft_chpbrk(head[0], "-=?+") == 1)
		sh_expansions_parameter_fill_format(head, format + i, 1);
	else if (ft_chpbrk(head[0], ":") == 1 && ft_chpbrk(head[1], "-=?+") == 1)
		sh_expansions_parameter_fill_format(head, format + i, 2);
	else if (ft_strnstr(head, "##", 2) || ft_strnstr(head, "%%", 2))
		sh_expansions_parameter_fill_format(head, format + i, 2);
	else
		return (ft_perror_err(exp->original, "bad substitution"));
	return (SUCCESS);
}

char		*sh_expansions_parameter_get_param(t_context *context, t_expansion *exp)
{
	char	*value;
	char	*end;
	char	buf;

	if (!(end = ft_strpbrk(exp->expansion, ":-=?+%#")))
		end = exp->expansion + ft_strlen(exp->expansion);
	buf = *end;
	*end = 0;
	value = sh_vars_get_value(context->env, context->vars, exp->expansion);
	*end = buf;
	return (value);
}

char		*sh_expansions_parameter_get_word(t_context *context, t_expansion *exp, char *format)
{
	char	*start;

	start = ft_strstr(exp->expansion, format);
	if (*format == '#')
		format++;
	start += ft_strlen(format);
	return (start);
	(void)context;
}
