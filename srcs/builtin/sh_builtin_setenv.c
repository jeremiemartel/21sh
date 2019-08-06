/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:32:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/21 10:46:57 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_setenv_usage:
**	Print setenv usage on current stderr.
*/

static void	sh_builtin_setenv_usage(int fderr)
{
	ft_dprintf(fderr, "usage : setenv var=value [...]\n");
}

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
	sh_perror_err_fd(context->fd[FD_ERR], "bad assignment", entry);
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

int			sh_builtin_setenv_process
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
		sh_builtin_hash_empty_table(context->shell);
	free(key);
	free(value);
	return (SUCCESS);
}

/*
** sh_builtin_setenv:
**	setenv [key=value] ...
**	Set every key=value couple in environment. If key already exists,
**	it's associated value is modified.
**
**	Return Value :
**		SUCCESS
**		FAILURE : malloc error
**		ERROR : entry is not on good format (invalid assignment)
*/

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
	if (i == 1)
		sh_builtin_setenv_usage(context->fd[FD_ERR]);
	return (SUCCESS);
}
