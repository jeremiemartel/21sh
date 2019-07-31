/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:17:37 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 17:21:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int     main(int argc, char **argv)
{
	pid_t pid;
	int     status;

	char *str = malloc(100);

	pid = fork();
	if (pid == 0)
	{
		free(str);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(str);
		return (0);
	}
}
