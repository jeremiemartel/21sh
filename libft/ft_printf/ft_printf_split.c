/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:19:09 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 10:36:20 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Functions used to stock the format argument informations as a linked list
**	-split : browse format, detecting types of future t_conv objects
**	-ft_printf_split_new_txt : create a link for non conversion text
**	-ft_printf_split_new_conv : create the link for a conversion
*/

t_conv		*ft_printf_split(const char *format)
{
	int		i;
	t_conv	*start;
	t_conv	*new;

	i = 0;
	start = NULL;
	while (format[i])
	{
		if (format[i] != '%' && format[i])
		{
			new = ft_printf_split_new_txt((char*)(format + i));
			if (new)
				i += ft_strlen(new->res);
		}
		else if (format[i] == '%')
		{
			new = ft_printf_split_new_conv((char*)(format + i));
			i += t_conv_len(format + i);
		}
		if (!(ft_printf_split_push_conv(&start, new)))
			return (NULL);
	}
	return (start);
}

/*
** Push the new link to the end of the list
**		If link is NULL, it free lists and return NULL
*/

t_conv		*ft_printf_split_push_conv(t_conv **start, t_conv *new)
{
	t_conv	*buf;

	if (!new)
	{
		ft_printf_split_free_list(*start);
		return (NULL);
	}
	if (!start || !*start)
	{
		*start = new;
		return (new);
	}
	buf = *start;
	while (buf->next != NULL)
		buf = buf->next;
	buf->next = new;
	new->next = NULL;
	return (new);
}

/*
** Function used to free the list if any error occure during spliting
*/

void		ft_printf_split_free_list(t_conv *start)
{
	t_conv	*buf;

	if (!start)
		return ;
	while (start)
	{
		buf = start;
		start = start->next;
		if (buf->type == TYPE_TEXT)
			free(buf->res);
		free(buf);
	}
}

t_conv		*ft_printf_split_new_txt(char *str)
{
	int			i;
	t_conv		*new;

	if (!(new = (t_conv*)malloc(sizeof(t_conv))))
		return (NULL);
	i = 0;
	while (str[i] != '%' && str[i])
		i++;
	new->type = TYPE_TEXT;
	new->conv = 0;
	new->prec = NO_PREC;
	new->size = NO_SIZE;
	if (!(new->res = ft_strsub(str, 0, i)))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_conv		*ft_printf_split_new_conv(char *str)
{
	int			i;
	t_conv		*new;

	i = t_conv_len(str);
	if (i == -1)
		return (NULL);
	if (!(new = (t_conv*)malloc(sizeof(t_conv))))
		return (NULL);
	new->type = *(str + i - 1);
	t_conv_new(new, str);
	new->next = NULL;
	return (new);
}
