/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions_process_tilde.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:43:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/14 13:41:00 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			lexer_expansion_process_tilde_1(t_lexer *lexer, t_expansion *exp)
{
	char	*home;

	if (!(home = get_env_value((char**)lexer->env->tbl, "HOME")))
		return ft_perror(SH_ERR1_ENV_NOT_SET, "HOME");
	if (!(exp->res = ft_dystr_new(home, ft_strlen(home), ft_strlen(home))))
		return ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde_1");
	return (LEX_OK);
}

int			lexer_expansion_process_tilde_2(t_lexer *lexer, t_expansion *exp)
{
	char	*buf;
	struct passwd	*passwd;
	int		i;

	if (!(buf = ft_strndup(exp->original + 1, ft_strlen(exp->original) - 2)))
		return (ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde_2"));
	if (!(passwd = getpwnam(buf)))
	{
		free(buf);
		return (ft_perror("no such user", buf));//
	}
	i = ft_strlen(passwd->pw_dir);
	if (!(exp->res = ft_dystr_new(passwd->pw_dir, i, i)))
	{
		free(buf);
		return ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde");
	}
	free(passwd);
	free(buf);
	return (LEX_OK);
	(void)lexer;
}

int			lexer_expansion_process_tilde(t_lexer *lexer, t_expansion *exp)
{
	if (ft_iswhite(exp->original[1]) || exp->original[1] == '/')
		return (lexer_expansion_process_tilde_1(lexer, exp));
	else 
		return (lexer_expansion_process_tilde_2(lexer, exp));
}