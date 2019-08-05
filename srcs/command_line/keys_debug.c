/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 22:43:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/05 15:19:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_print_buffer(t_key_buffer buffer)
{
	int i;

	i = 0;
	ft_printf("\nprogress: %d\n\n", buffer.progress);
	while (i < buffer.progress)
	{
		ft_printf("buffer[%d]: %d (%.8b)\n", i, buffer.buff[i], buffer.buff[i]);
		i++;
	}
	ft_printf("last character input: %d\n", buffer.last_char_input);
	ft_printf("\n\n");
}
