/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 21:39:14 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/24 16:10:57 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_inf_nan(long double f)
{
	if (f == PINFINITY)
		return (ft_strdup("inf"));
	else if (f == LINFINITY)
		return (ft_strdup("-inf"));
	else if (f != f)
		return (ft_strdup("nan"));
	else
		return (NULL);
}

static void		ft_fill_str(char *str, int len)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	while (i < len)
	{
		str[i] = '0';
		i++;
	}
	str[len] = '\0';
}

static char		*ft_round_char(char *str)
{
	int		len;
	int		i;
	int		out;

	len = ft_strlen(str);
	i = 0;
	out = 0;
	if (ft_isdigit(str[len - 1]) == 1 && str[len - 1] != '9')
		return (str);
	ft_strrev(str);
	while (str[i] && out == 0)
	{
		if (str[i] == '9')
			str[i] = '0';
		else if (ft_isdigit(str[i]) == 1)
		{
			str[i] += 1;
			out = 1;
		}
		i++;
	}
	if (out == 0)
		str = ft_strjoin_free(str, "1", 1);
	ft_strrev(str);
	return (str);
}

static char		*ft_ftoa_body(char *str, long double f, int prec)
{
	int		i;
	char	n;
	char	*dec;
	long	power;

	power = 1;
	while (power * 10 <= f)
		power *= 10;
	i = ft_strlen(str);
	while (power >= 1)
	{
		n = (char)(f / power);
		f -= (n * power);
		power /= 10;
		str[i] = n + '0';
		i++;
	}
	power = ft_pow(10, prec);
	if (prec == 0)
		return (str);
	str = ft_strcat(str, ".");
	dec = ft_ltoa(ft_roundl(f * power), 10);
	str = ft_strcat(str, dec);
	free(dec);
	return (str);
}

char			*ft_ftoa(long double f, int prec)
{
	char	*str;
	int		len;
	int		neg;

	neg = 1;
	if ((str = ft_inf_nan(f)))
		return (str);
	if (f < 0 || (1.0 / f == -1.0 / 0.0))
	{
		neg = -1;
		f = -f;
	}
	len = ft_longlen(f) + prec;
	if (prec != 0)
		len += 1;
	if (prec == 0)
		f = ft_roundl(f);
	if (!(str = ft_strnew(len)))
		return (NULL);
	str = ft_ftoa_body(str, f, prec);
	ft_fill_str(str, len);
	str = ft_round_char(str);
	if (neg == -1)
		str = ft_strjoin_free("-", str, 2);
	return (str);
}
