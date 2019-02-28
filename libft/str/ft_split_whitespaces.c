/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 17:53:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/12 17:56:06 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_spws_is_white(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

static int			ft_spws_count_words(char *str)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_spws_is_white(str[i]))
			i++;
		if (str[i] && !ft_spws_is_white(str[i]))
			len++;
		while (str[i] && !ft_spws_is_white(str[i]))
			i++;
	}
	return (len);
}

static char			**ft_spws_fill_tab(char *str, char **tab)
{
	int		istr;
	int		itab;
	int		len;

	istr = 0;
	itab = 0;
	while (str[istr])
	{
		while (str[istr] && ft_spws_is_white(str[istr]))
			istr++;
		len = 0;
		while (str[istr + len] && !ft_spws_is_white(str[istr + len]))
			len++;
		if (len)
			if (!(tab[itab] = ft_strndup(str + istr, len)))
			{
				tab[itab] = NULL;
				ft_strtab_free(tab);
				return (NULL);
			}
		itab++;
		while (str[istr] && !ft_spws_is_white(str[istr]))
			istr++;
	}
	return (tab);
}

char				**ft_split_whitespaces(char *str)
{
	int		len;
	char	**tab;

	if (!str)
		return (NULL);
	if (!(len = ft_spws_count_words(str)))
		return (NULL);
	if (!(tab = malloc(sizeof(*tab) * (len + 1))))
		return (NULL);
	tab[len] = NULL;
	tab = ft_spws_fill_tab(str, tab);
	return (tab);
}
