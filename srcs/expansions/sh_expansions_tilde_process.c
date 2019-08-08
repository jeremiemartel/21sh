/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_tilde_process.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:57:07 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/05 21:34:39 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_init_tilde:
**	Try to fill type, expansion, original and process fields of a t_expansion
**	structure for tilde expansion.
**
**	Return Value:
**		FAILURE : malloc error
**		ERROR : expansion is invalid
**		SUCCESS : successfully filled expansion
*/

static int	sh_expansions_init_tilde(char *original, t_expansion *exp)
{
	char	*start;

	ft_bzero(exp, sizeof(t_expansion));
	if (!(start = ft_strpbrk(original, "~")))
		return (ERROR);
	if (ft_strnstr(start, "~", 1))
		return (sh_expansions_tilde_fill(exp, start));
	else
		return (ERROR);
}

int			sh_expansions_process_tilde(
	char **input, char *original, t_context *context)
{
	t_expansion	exp;
	int			ret;

	if (!ft_strpbrk(original, "~"))
		return (SUCCESS);
	if (sh_expansions_init_tilde(original, &exp) != SUCCESS)
	{
		t_expansion_free_content(&exp);
		return (ERROR);
	}
	if (sh_verbose_expansion())
		ft_dprintf(2, "tilde expansion detected\n");
	if (sh_verbose_expansion())
		t_expansion_show(&exp);
	ret = exp.process(context, &exp);
	if (!ret)
		ret = sh_expansions_replace(&exp, input, 0);
	t_expansion_free_content(&exp);
	return (ret);
}
