/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansions_process_tilde.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:43:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/14 12:05:51 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			lexer_expansion_process_tilde_1(t_lexer *lexer, t_expansion *exp)
{
	char	*home;

	if (!(home = get_env_value((char**)lexer->env->tbl, "HOME")))
		return ft_perror(SH_ERR1_ENV_NOT_SET, "HOME");
	if (!(exp->res = ft_dystr_new(home, ft_strlen(home), ft_strlen(home))))
		return ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde");
	return (LEX_OK);
}

int			lexer_expansion_process_tilde_2(t_lexer *lexer, t_expansion *exp)
{
	char	*home;

	if (!(home = get_env_value((char**)lexer->env->tbl, "HOME")))
	{
		ft_perror(SH_ERR1_ENV_NOT_SET, "HOME");
		return (LEX_ERR);
	}
	if (!(exp->res = ft_dystr_new(home, ft_strlen(home), ft_strlen(home))))
		return ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde");
	return (LEX_OK);
}

int			lexer_expansion_process_tilde(t_lexer *lexer, t_expansion *exp)
{
	if (ft_iswhite(exp->original[1]) || exp->original[1] == '/')
		return (lexer_expansion_process_tilde_1(lexer, exp));
	else 
		return (lexer_expansion_process_tilde_2(lexer, exp));
}