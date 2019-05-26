/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ok.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 09:49:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/26 09:50:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>


int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	dprintf(1, "fd 1\n");
	dprintf(2, "fd 2\n");
	dprintf(3, "fd 3\n");
	dprintf(4, "fd 4\n");
	return (0);
}
