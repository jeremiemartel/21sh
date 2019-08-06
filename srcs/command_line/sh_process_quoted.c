/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process_quoted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:21:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/06 19:37:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_process_quoted(int old_context, t_lexer *lexer)
{
	int ret;

	if ((ret = sh_get_command(lexer->shell, &g_glob.command_line)))
	{
		g_glob.command_line.context = old_context;
		if (ret == CTRL_C)
		{
			g_glob.command_line.interrupted = 1;
			return (LEX_ERR);
		}
		else
			return (LEX_FAIL);
	}
	if (!(lexer->input = ft_strjoin_free(lexer->input,
					g_glob.command_line.dy_str->str, 1)))
		return (LEX_FAIL);
	g_glob.command_line.context = old_context;
	reset_command_line(lexer->shell, &g_glob.command_line);
	if (update_prompt(lexer->shell, &g_glob.command_line) != SUCCESS)
		return (LEX_FAIL);
	return (LEX_OK);
}

int		sh_process_quoted(t_lexer *lexer)
{
	int old_context;

	old_context = g_glob.command_line.context;
	if (update_prompt_from_quote(lexer->shell, &g_glob.command_line,
			lexer->quoted, lexer->backslash) != SUCCESS)
		return (LEX_FAIL);
	if (lexer->quoted == '\"' || lexer->quoted == '\'')
	{
		if (!(lexer->input = ft_strjoin_free(lexer->input, "\n", 1)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_lexer_rule1_process_quoted"));
	}
	else if (lexer->backslash)
		lexer->backslash = 0;
	return (sh_process_process_quoted(old_context, lexer));
}
