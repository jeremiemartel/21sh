/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 06:43:14 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/04 06:43:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char buff[4096];
	int ret;

	printf("call to test!\n");
	while ((ret = read(0, buff, 4096)))
	{
		printf("ret = %d\n", ret);
		write(1, buff, ret);
	}
	printf("end of test\n");
}
