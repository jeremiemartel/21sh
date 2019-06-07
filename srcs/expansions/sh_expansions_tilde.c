/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_tilde.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:56:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/07 18:06:13 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_expansions_tilde_detect(char *start)
{
	int		i;

	i = 0;
	if (start[i] != '~')
		return (-1);
	while (start[i] && !(ft_iswhite(start[i]) || start[i] == '/'))
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
		return (ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde_2 (1)"));
	if (!(passwd = getpwnam(buf))) // bonuse LEAKS, and invalid read 
		exp->res = ft_dy_str_new_str(exp->original);
	else
		exp->res = ft_dy_str_new_str(passwd->pw_dir);
	free(buf);
	if (!(exp->res))
		return ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde_2 (2)");
	return (SUCCESS);
	(void)context;
}
