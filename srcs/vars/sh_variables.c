/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:26:55 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/20 17:36:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_variables_assignment(t_dy_tab *vars, char *assignment)
{
	if (!(ft_strchr(assignment, '=')))
		return (FAILURE);
	if (!(ft_dy_tab_add_str(vars, assignment)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_variable_assignment"));
	return (SUCCESS);
}
