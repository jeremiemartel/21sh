/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:01:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/09 18:30:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr_fd(const char *str, int n, int fd)
{
	int len;

//	ft_printf("%s, fd: %d n: %d\n", str, fd, n);
	len = ft_strlen(str);
	if (n > len)
		write(fd, str, len);
	else
		write(fd, str, n);
}
