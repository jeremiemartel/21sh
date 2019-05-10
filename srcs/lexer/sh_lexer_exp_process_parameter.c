/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp_process_parameter.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:41:00 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/10 15:50:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp_parameter_format(t_expansion *exp, char *format)
{
	char	*head;
	int		i;

	head = exp->expansion;
	i = 0;
	if (*head == '#')
	{
		format[i] = '#';
		i++;
		head++;
	}
	if (!ft_isalpha(*head) && *head != '_' && *head != '#')
	{
		if (!ft_chpbrk(head[1], ":-=?+%"))
			return (ft_perror("bad substitution", NULL));
	}
	head++;
	while (ft_isalnum((int)*head) || *head == '_')
		head++;
	format[i] = *head;
	i++;
	if (ft_chpbrk(*head, ":#%") && ft_chpbrk(head[1], "-=?+#%"))
	{
		format[i] = head[1];
		head[1] = 0;
		i++;
	}
	*head = 0;
	format[i] = 0;
	return (LEX_OK);
}

char	*sh_lexer_exp_parameter_get_param(t_lexer *lexer, t_expansion *exp)
{
	char	*value;
	char	*end;
	char	buf;

	end = ft_strpbrk(exp->expansion, ":-=?+%#");
	buf = *end;
	*end = 0;
	value = sh_vars_get_value(lexer->env, lexer->vars, exp->expansion);
	*end = buf;
	return (value);
}

char	*sh_lexer_exp_parameter_get_word(t_lexer *lexer, t_expansion *exp, char *format)
{
	char	*start;

	start = ft_strstr(exp->expansion, format);
	if (*format == '#')
		format++;
	start += ft_strlen(format);
	return (start);
	(void)lexer;
}

int		sh_lexer_exp_parameter(t_lexer *lexer, t_expansion *exp)
{
	char	format[4];

	if (!ft_strpbrk(exp->expansion, ":-=?+%"))
		if (!ft_strchr(exp->expansion + 1, '#'))
			return (sh_lexer_exp_variable(lexer, exp));
	sh_lexer_exp_parameter_format(exp, format);
	if (ft_strstr(":-", format) || ft_strstr("-", format))
		return (sh_lexer_exp_minus(lexer, exp, format));
	else if (ft_strstr(":=", format) || ft_strstr("=", format))
		return (sh_lexer_exp_equal(lexer, exp, format));
	else if (ft_strstr(":?", format) || ft_strstr("?", format))
		return (sh_lexer_exp_quest(lexer, exp, format));
	else if (ft_strstr(":+", format) || ft_strstr("+", format))
		return (sh_lexer_exp_plus(lexer, exp, format));
	else if (ft_strstr("%", format) || ft_strstr("%%", format))
		return (sh_lexer_exp_percent(lexer, exp, format));
	else if (ft_strstr("#", format) || ft_strstr("##", format))
		return (sh_lexer_exp_hash(lexer, exp, format));
	else
		return (ft_perror("unrecognized modifier", NULL));
	return (LEX_OK);
}

int		sh_lexer_exp_minus(t_lexer *lexer, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_lexer_exp_parameter_get_param(lexer, exp);
	word = sh_lexer_exp_parameter_get_word(lexer, exp, format);
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
		return (ft_perror(SH_ERR1_MALLOC, "sh_lexer_exp_minus"));
	return (LEX_OK);
}

int		sh_lexer_exp_equal(t_lexer *lexer, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_lexer_exp_parameter_get_param(lexer, exp);
	word = sh_lexer_exp_parameter_get_word(lexer, exp, format);
	if (!param)
	{
		// need to assign word with the key param (not expanded)
		// sh_vars_add_key(exp->vars, , word);
		exp->res = ft_dy_str_new_str(word);
	}
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
		{
			// need to assign word with the key param (not expanded)
			// sh_vars_add_key(exp->vars, , word);
			exp->res = ft_dy_str_new_str(word);
		}
		else
			exp->res = ft_dy_str_new_str("");
	}
	else
		exp->res = ft_dy_str_new_str(param);
	if (!exp->res)
		return (ft_perror(SH_ERR1_MALLOC, "sh_lexer_exp_"));
	return (LEX_OK);
}

int		sh_lexer_exp_quest(t_lexer *lexer, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_lexer_exp_parameter_get_param(lexer, exp);
	word = sh_lexer_exp_parameter_get_word(lexer, exp, format);
	if (!param)
		exp->res = ft_dy_str_new_str(word);
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
			return (LEX_ERR);
		else
			exp->res = ft_dy_str_new_str("");
	}
	else
		return (LEX_ERR);
	if (!exp->res)
		return (ft_perror(SH_ERR1_MALLOC, "sh_lexer_exp_"));
	return (LEX_OK);
}

int		sh_lexer_exp_plus(t_lexer *lexer, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_lexer_exp_parameter_get_param(lexer, exp);
	word = sh_lexer_exp_parameter_get_word(lexer, exp, format);
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
		return (ft_perror(SH_ERR1_MALLOC, "sh_lexer_exp_"));
	return (LEX_OK);
}

// Need to implement Percent !
int		sh_lexer_exp_percent(t_lexer *lexer, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_lexer_exp_parameter_get_param(lexer, exp);
	word = sh_lexer_exp_parameter_get_word(lexer, exp, format);
	exp->res = ft_dy_str_new_str("");
	return (LEX_OK);
}

// Need to implement Hash !
int		sh_lexer_exp_hash(t_lexer *lexer, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_lexer_exp_parameter_get_param(lexer, exp);
	word = sh_lexer_exp_parameter_get_word(lexer, exp, format);
	exp->res = ft_dy_str_new_str("");
	return (LEX_OK);
}
