/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_parameter_process.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:41:00 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/30 17:52:03 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_parameter_minus
**					parameter Not Null		parameter Null		parameter Unset
**parameter:-word	substitute parameter	substitute word		substitute word
**parameter-word	substitute parameter	substitute null		substitute word
**
**	return Value:
**		SUCCESS : exp->res sucessfully filled
**		FAILURE : malloc error
*/

int			sh_expansions_parameter_minus(t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_expansions_parameter_get_param(context, exp);
	word = sh_expansions_parameter_get_word(context, exp, format);
	if (!param)
		exp->res = ft_dy_str_new_str(word);
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
			exp->res = ft_dy_str_new_str(word);
		else
			exp->res = ft_dy_str_new_str("");
	}
	else
		exp->res = ft_dy_str_new_str(param);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_minus"));
	return (SUCCESS);
}

/*
** sh_expansions_parameter_equal
**					parameter Not Null		parameter Null		parameter Unset
**parameter:=word	substitute parameter	assign word			assign word
**parameter=word	substitute parameter	substitute null		assign word
**
**	return Value:
**		SUCCESS : exp->res sucessfully filled
**		FAILURE : malloc error
*/

int			sh_expansions_parameter_equal(t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;
	char	buff;

	param = sh_expansions_parameter_get_param(context, exp);
	word = sh_expansions_parameter_get_word(context, exp, format);
	if (!param || (!(*param) && ft_strchr(format, ':')))
	{
		param = ft_strstr(exp->expansion, format);
		buff = *param;
		*param = 0;
		sh_vars_assign_key_val(
			context->env, context->vars, exp->expansion, word);
		*param = buff;
		exp->res = ft_dy_str_new_str(word);
	}
	else if (!*param)
		exp->res = ft_dy_str_new_str("");
	else
		exp->res = ft_dy_str_new_str(param);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_equal"));
	return (SUCCESS);
}

/*
** sh_expansions_parameter_quest_msg
**		function used to create correct error message in ? and :?
**		parameter expansion
**
**	return Value:
**		ERROR
*/

static int	sh_expansions_parameter_quest_msg(
	t_context *context, char *expansion, char *word)
{
	char	*buf;

	buf = ft_strpbrk(expansion, ":?");
	*buf = 0;
	sh_perror_err_fd(context->fd[FD_ERR], expansion, word);
	if (isatty(0))
		return (FAILURE);
	else
		return (ERROR);
}

/*
** sh_expansions_parameter_quest:
**					parameter Not Null		parameter Null		parameter Unset
**parameter:?word	substitute parameter	error, exit			error, exit
**parameter?word	substitute parameter	substitute null		error, exit
**
**	return Value:
**		SUCCESS : exp->res sucessfully filled
**		ERROR : One of the previous condition happend
**		FAILURE : malloc error, one of previos condition happend
*/

int			sh_expansions_parameter_quest(t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_expansions_parameter_get_param(context, exp);
	word = sh_expansions_parameter_get_word(context, exp, format);
	if (!param)
		return (sh_expansions_parameter_quest_msg(context, exp->expansion, word));
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
			return (sh_expansions_parameter_quest_msg(context, exp->expansion, word));
		else
			exp->res = ft_dy_str_new_str("");
	}
	else
		exp->res = ft_dy_str_new_str(param);
	if (!exp->res)
		return (FAILURE);
	return (SUCCESS);
}

/*
** sh_expansions_parameter_plus:
**					parameter Not Null		parameter Null		parameter Unset
**parameter:+word	substitute word			substitute null		substitute null
**parameter+word	substitute word			substitute word		substitute null
**
**	return Value:
**		SUCCESS : exp->res sucessfully filled
**		FAILURE : malloc error
*/

int			sh_expansions_parameter_plus(t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_expansions_parameter_get_param(context, exp);
	word = sh_expansions_parameter_get_word(context, exp, format);
	if (!param)
		exp->res = ft_dy_str_new_str("");
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
			exp->res = ft_dy_str_new_str("");
		else
			exp->res = ft_dy_str_new_str(word);
	}
	else
		exp->res = ft_dy_str_new_str(word);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_"));
	return (SUCCESS);
}
