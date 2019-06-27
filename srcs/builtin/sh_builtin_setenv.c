/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:32:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/25 16:07:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** is_bad_assignment:
**	Check that an entry is a correct key=value, where value can be empty.
**
** Return Value : 
**		True if incorrect
**		False if correct
*/

static int	is_bad_assignment(char *entry, int *key_len)
{
	int len;

	if ((len = sh_expansions_variable_detect(entry)) == -1)
		return (-1);
	if (entry[len] == '=')
	{
		*key_len = len;
		return (0);
	}
	return (1);
}

/*
** sh_process_bad_assignment:
**	Print error message no context->fd[FD_ERR].
**	Used for invalid key=value assignation.
**
**	Return Value :
**		ERROR
*/

static int	sh_process_bad_assignment(t_context *context, char *entry)
{
	ft_dprintf(context->fd[FD_ERR], "%s: \'%s\' bad assignment\n",
		SH_NAME, entry);
	return (ERROR);
}

/*
** sh_builtin_setenv_process:
**	Function used to add variabes to env.
**	Entry must have form var=value or an error message will be prompted.
**	Context is only used to know file descriptors and usse hash table.
**
**	Return Value :
**		SUCCESS
**		FAILURE : malloc error
**		ERROR : entry is not on good format
*/

int	sh_builtin_setenv_process
	(char *entry, t_dy_tab *env, t_context *context)
{
	char	*value;
	char	*key;
	int		key_len;

	if (is_bad_assignment(entry, &key_len))
		return (sh_process_bad_assignment(context, entry));
	if (!(key = ft_strndup(entry, key_len)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_setenv_process (1)"));
	if (!(value = ft_strnrest(entry, key_len + 1)))
	{
		free(key);
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_setenv_process (1)"));
	}
	if (sh_vars_assign_key_val(env, NULL, key, value) == FAILURE)
	{
		free(key);
		free(value);
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_setenv_process (1)"));
	}
	if (!ft_strcmp(key, "PATH"))
		process_builtin_hash_suppr_all(context->shell);
	free(key);
	free(value);
	return (SUCCESS) ;
}

int			sh_builtin_setenv(t_context *context)
{
	int i;
	int len;
	int	ret;

	len = context->params->current_size;
	i = 1;
	while (i < len)
	{
		if ((ret = sh_builtin_setenv_process((char *)(context->params->tbl[i]),
				context->env, context)) != SUCCESS)
			return (ret);
		i++;
	}
	return (SUCCESS);
}
