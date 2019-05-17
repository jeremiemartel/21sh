/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:54:13 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/14 18:54:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_append_to_historic(t_shell *shell, char *command)
{
	int		fd;
	char	*str;

	if (!ft_strcmp(command, "")
		|| (shell->historic.commands
			&& !ft_strcmp((char *)shell->historic.commands->content, command)))
		return (SUCCESS);
	if (!(str = ft_strdup(command)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_append_to_historic"));
	if (ft_add_to_dlist_ptr(&shell->historic.commands, str, sizeof(str)))
	{
		free(str);
		return (ft_perror(SH_ERR1_MALLOC, "sh_append_to_historic"));
	}
	if ((fd = open(PATH"/"HISTORIC_FILE, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU)) == -1)
		return (ft_perror(SH_ERR1_HISTORIC, "sh_append_to_historic"));
	ft_dprintf(fd, "%s\n", command);
	shell->historic.head_start.next = shell->historic.commands;
	close(fd);
	return (SUCCESS);
}
