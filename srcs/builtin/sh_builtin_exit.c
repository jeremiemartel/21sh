/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:14:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/10 19:01:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_builtin_exit(t_context *context)
{
	if (context->params->tbl[0] && context->params->tbl[1] && context->params->tbl[2])
		return (ft_perror(context->params->tbl[0], SH_ERR1_TOO_MANY_ARGS));
	else if (context->params->tbl[1])
		return (ft_atoi(context->params->tbl[1]) + 0xF000); //WTF is that number ??
	else
		return (0xF000);
}
