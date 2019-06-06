/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_process_tilde.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:07:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/06 14:00:06 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_tilde_1:
**	Treat classic case of a ~ or ~/, replacing it with content of HOME
**	env variable
**
**	return : SUCCESS or FAILURE
*/
int			sh_expansions_tilde_1(t_context *context, t_expansion *exp)
{
	char	*home;

	if (!(home = get_env_value((char**)context->env->tbl, "HOME")))
		return ft_perror(SH_ERR1_ENV_NOT_SET, "HOME");
	if (!(exp->res = (t_dy_str *)malloc(sizeof(t_dy_str))))
		return (ft_perror(SH_ERR1_MALLOC, "sh_expansions_tilde_1 (1)"));
	if (!(exp->res->str = ft_strrep_free(exp->original, home, "~", 0)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_expansions_tilde_1 (2)"));
	return (SUCCESS);
}

/*
** sh_expansions_tilde_2:
**	Bonnus function to treat tilde expansion, replacing ~user/ by it's
**	home absolute path
**
**	return SUCESS or FAILURE
*/
int			sh_expansions_tilde_2(t_context *context, t_expansion *exp)
{
	char			*buf;
	struct passwd	*passwd;

	if (!(buf = ft_strndup(exp->original + 1, ft_strlen(exp->original) - 2)))
		return (ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde_2"));
	if (!(passwd = getpwnam(buf))) // bonuse LEAKS, and invalid read 
	{
		free(buf);
		return (FAILURE);
	}
	if (!(exp->res = ft_dy_str_new_str(passwd->pw_dir)))
	{
		free(buf);
		return ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde");
	}
	free(buf);
	return (SUCCESS);
	(void)context;
}
