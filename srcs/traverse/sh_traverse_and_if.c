/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:27:20 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/19 22:14:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_and_if(t_ast_node *node, t_context *context)
{
	char	*str;

	if (!(str = get_env_value((char**)context->env->tbl, "?")))
		return (FAILURE);
	if (ft_atoi(str) != 0)
		return (SUCCESS);
	sh_traverse_tools_reset_context(context);
	return (sh_traverse_tools_browse(node, context));
}
