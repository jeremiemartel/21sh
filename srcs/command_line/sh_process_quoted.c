/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process_quoted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:21:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/10 15:52:17 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_quoted(t_lexer *lexer)
{
	int old_context;
	int ret;

	old_context	= g_glob.command_line.context;
	if (update_prompt_from_quote(lexer->shell, &g_glob.command_line,
			lexer->quoted) != SUCCESS)
		return (LEX_FAIL);
	if (lexer->quoted == '\"' || lexer->quoted == '\'')
	{
		if (!(lexer->input = ft_strjoin_free(lexer->input, "\n", 1)))
			return (LEX_FAIL);
	}
	else
		lexer->quoted = 0;
	if ((ret = sh_get_command(lexer->shell, &g_glob.command_line)))
	{
		g_glob.command_line.context = old_context;
		if (ret == CTRL_C)
			return (LEX_ERR);
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
