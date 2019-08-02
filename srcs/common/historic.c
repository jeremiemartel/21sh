/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:54:13 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/29 17:42:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_too_big_to_append_to_historic(char *command)
{
	int i;

	i = 0;
	while (command[i] && i < MAX_LEN_HISTORIC_ENTRY)
		i++;
	return (command[i]);
}

int			sh_append_to_historic(t_shell *shell, char *command)
{
	int		fd;
	char	*str;

	if (sh_too_big_to_append_to_historic(command) || !ft_strcmp(command, "")
		|| (shell->historic.commands
			&& !ft_strcmp((char *)shell->historic.commands->content, command)))
		return (SUCCESS);
	if (!(str = ft_strdup(command)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_append_to_historic 1"));
	if (ft_add_to_dlist_ptr(&shell->historic.commands, str, sizeof(str)))
	{
		free(str);
		return (sh_perror(SH_ERR1_MALLOC, "sh_append_to_historic 2"));
	}
	if ((fd = open(PATH"/"HISTORIC_FILE,
			O_WRONLY | O_CREAT | O_APPEND | O_NOFOLLOW, S_IRWXU)) == -1)
		return (sh_perror(SH_ERR1_HISTORIC, "sh_append_to_historic 3"));
	ft_dprintf(fd, "%s\n", command);
	shell->historic.head_start.next = shell->historic.commands;
	close(fd);
	return (SUCCESS);
}
