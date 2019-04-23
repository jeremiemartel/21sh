/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:14:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/23 12:20:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_builtin_exit(t_dy_tab *argv, t_dy_tab *env)
{
	if (argv->tbl[0] && argv->tbl[1] && argv->tbl[2])
		return (ft_perror(argv->tbl[0], SH_ERR1_TOO_MANY_ARGS));
	else if (argv->tbl[1])
		return (ft_atoi(argv->tbl[1]) + 0xF000); //WTF is that number ??
	else
		return (0xF000);
	(void)env;
}
