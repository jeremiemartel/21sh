/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:28:55 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/14 15:30:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strdelchar:
**	Delete the char in position specified by index in the str string.
*/
void	ft_strdelchar(char *str, int index)
{
	ft_strcpy(str + index, str + index + 1);
}

/*
** ft_strdelchar:
**	Delete the len chars in position specified by index in the str string.
*/
void	ft_strdelchars(char *str, int index, int len)
{
	ft_strcpy(str + index, str + index + len);
}
