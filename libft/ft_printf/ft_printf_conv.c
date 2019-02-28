/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:23:36 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 10:30:40 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Different functions associated to s_conv structure
**	-t_conv_len : lenght a convertion string (return -1 if invalid type)
**	-t_conv_new : used to detect the different flags used in a conversion
**	-conv_size : conv_new subfunction, used for detection of size and precision
**	-t_conv_detect_zero : t_conv_new subfunction, to detect the zero flag
**	-conv_free : free a t_conv linked list
*/

int			t_conv_len(const char *restrict format)
{
	int		i;

	i = 1;
	while (format[i] && conv_isconv(format[i]) == 0)
		i++;
	if (format[i] == 0)
		return (-1);
	return (i + 1);
}

int			t_conv_new(t_conv *conv, const char *str)
{
	char	*sub;

	sub = ft_strsub(str, 0, t_conv_len(str));
	conv->conv = 0;
	if (ft_strstr(sub, "hh"))
		conv->conv += CAST_HH;
	else if (ft_strstr(sub, "h"))
		conv->conv += CAST_H;
	else if (ft_strstr(sub, "ll") || ft_strstr(sub, "L"))
		conv->conv += CAST_LL;
	else if (ft_strstr(sub, "l"))
		conv->conv += CAST_L;
	t_conv_size_prec(sub, conv);
	if (ft_strstr(sub, " "))
		conv->conv += FLAG_SPACE;
	if (ft_strstr(sub, "-"))
		conv->conv += FLAG_MINUS;
	if (ft_strstr(sub, "+"))
		conv->conv += FLAG_PLUS;
	if (ft_strstr(sub, "#"))
		conv->conv += FLAG_HASH;
	if (t_conv_detect_zero(sub) == 1)
		conv->conv += FLAG_ZERO;
	free(sub);
	return (0);
}

void		t_conv_size_prec(char *str, t_conv *conv)
{
	int		i;

	conv->size = NO_SIZE;
	conv->prec = NO_PREC;
	i = 0;
	while ((str[i] && !ft_isdigit(str[i]) && str[i] != '.') || str[i] == '0')
		i++;
	if (str[i] && str[i] != '.')
		conv->size = ft_atoi(str + i);
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
		conv->prec = ft_atoi(str + i + 1);
	return ;
}

int			t_conv_detect_zero(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			if (str[i] == '0')
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}

void		t_conv_free_lst(t_conv *start)
{
	t_conv	*buf;

	while (start)
	{
		buf = start;
		start = start->next;
		free(buf->res);
		free(buf);
	}
}
