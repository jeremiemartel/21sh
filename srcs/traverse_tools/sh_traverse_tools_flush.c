/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_flush.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:40:06 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/20 17:19:23 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_tools_flush(t_context *context)
{
	int		ret;

	if (!context->params->tbl[0])
		return (SUCCESS);
	ret = sh_execute_command(context);
	sh_traverse_tools_reset_params(context);
	return (ret);
}
