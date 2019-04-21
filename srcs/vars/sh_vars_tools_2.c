/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vars_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 22:21:50 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/21 22:40:53 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vars_mod_key:
**	modify the the value of an assignment in a t_dy_tab
**	If value does not exists it calls sh_vars_add_key
**	return:
**		SUCESS or FAILURE
*/
int		sh_vars_mod_key(t_dy_tab *vars, char *key, char *value)
{
	int		index;
	char	*buff;

	if ((index = sh_vars_get_index(vars, key)) == -1)
		return (sh_vars_add_key(vars, key, value));
	if (!(buff = ft_strjoin_3(key, "=", value)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_vars_mod_key"));
	free(vars->tbl[index]);
	vars->tbl[index] = buff;
	return (SUCCESS);
}

/*
** sh_vars_mod_key:
**	add an assignment in a t_dy_tab, using key, value arguments
**	If value already exists it calls sh_vars_mod_key
**	return:
**		SUCESS or FAILURE
*/
int		sh_vars_add_key(t_dy_tab *vars, char *key, char *value)
{
	char	*buff;

	if (sh_vars_get_index(vars, key) != -1)
		return (sh_vars_mod_key(vars, key, value));
	if (!(buff = ft_strjoin_3(key, "=", value)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_vars_add_key"));
	if (!(ft_dy_tab_add_ptr(vars, buff)))
	{
		free(buff);
		return (ft_perror(SH_ERR1_MALLOC, "sh_vars_add_key"));
	}
	return (SUCCESS);
}

/*
** sh_vars_mod_key:
**	Treat any assignment with form "key=value" and call sh_vars_add_value
**	or sh_vars_mod_value, with well formatted arguments
**	return:
**		SUCESS or FAILURE
*/
int		sh_vars_assignment(t_dy_tab *vars, char *assignment)
{
	char	*buf;
	char	*value;
	int		res;

	if (!(buf = ft_strchr(assignment, '=')))
		return (FAILURE);
	*buf = 0;
	value = buf + 1;
	if (sh_vars_get_index(vars, assignment) == -1)
		res = sh_vars_add_key(vars, assignment, value);
	else
		res = sh_vars_mod_key(vars, assignment, value);
	buf = '=';
	return (res);
}
