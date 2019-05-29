/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ok.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 09:49:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/26 18:26:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

# define BUFF_SIZE 10000

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char buffer[BUFF_SIZE + 1];
	int readd = 0;

	if (!readd)
	{
		dprintf(4, "fd 4\n");
	}
	else
	{
		int ret = read(0, buffer, BUFF_SIZE);
		printf("ret = %d\n", ret);
		buffer[ret] = 0;
		printf("%s", buffer);
	}
	return (0);
}
