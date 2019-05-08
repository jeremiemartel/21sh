/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp_process_tilde.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:07:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/08 13:08:15 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp_tilde(t_lexer *lexer, t_expansion *exp)
{
	if (lexer->current_id == LEX_TOK_UNKNOWN)
		lexer->current_id = LEX_TOK_WORD;
	if (!exp->original[1] || ft_iswhite(exp->original[1]) || exp->original[1] == '/')
		return (sh_lexer_exp_tilde_1(lexer, exp));
	else
		return (sh_lexer_exp_tilde_2(lexer, exp));
}

int			sh_lexer_exp_tilde_1(t_lexer *lexer, t_expansion *exp)
{
	char	*home;

	if (!(home = get_env_value((char**)lexer->env->tbl, "HOME")))
		return ft_perror(SH_ERR1_ENV_NOT_SET, "HOME");
	if (!(exp->res = (t_dy_str *)malloc(sizeof(t_dy_str))))
		return (ft_perror(SH_ERR1_MALLOC, "sh_lexer_exp_tilde_1 (1)"));
	if (!(exp->res->str = ft_strrep_free(exp->original, home, "~", 0)))
		return (ft_perror(SH_ERR1_MALLOC, "sh_lexer_exp_tilde_1 (2)"));
	return (LEX_OK);
}

int			sh_lexer_exp_tilde_2(t_lexer *lexer, t_expansion *exp)
{
	char			*buf;
	struct passwd	*passwd;

	if (!(buf = ft_strndup(exp->original + 1, ft_strlen(exp->original) - 2)))
		return (ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde_2"));
	if (!(passwd = getpwnam(buf)))
	{
		free(buf);
		return (ft_perror("no such user", buf));//
	}
	if (!(exp->res = ft_dy_str_new_from(passwd->pw_dir)))
	{
		free(buf);
		return ft_perror(SH_ERR1_MALLOC, "expansion_process_tilde");
	}
	free(buf);
	return (LEX_OK);
	(void)lexer;
}
