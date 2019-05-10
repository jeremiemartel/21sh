/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_printable_utf8.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:33:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/14 16:46:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		is_utf8_len_header(unsigned char first_byte, int length)
{
	int i;

	i = 0;
	while (i < length)
	{
		if (!(first_byte & ((0b10000000) >> i)))
			return (0);
		i++;
	}
	return (!(first_byte & ((0b10000000) >> i)));
}

int		is_utf8_next_byte(unsigned char next_byte)
{
	return (next_byte & 0b10000000 && !(next_byte & 0b01000000));
}

int		is_utf8_len_3(unsigned char *buffer)
{
	if (!is_utf8_len_header(buffer[0], 3) ||
			!is_utf8_next_byte(buffer[1]) || !is_utf8_next_byte(buffer[2]))
		return (0);
	else if (buffer[0] == 224)
		return (buffer[1] & 0b00100000);
	else if (buffer[0] == 225 || buffer[0] == 226 || buffer[0] == 227)
		return (1);
	else if (!(buffer[0] & 0b00001000) && buffer[0] & 0b00000100)
		return (1);
	else if (buffer[0] & 0b00001000 && !(buffer[0] & 0b00000100))
		return (1);
	else if (buffer[0] == 236)
		return (1);
	else if (buffer[0] == 237)
		return (!(buffer[1] & 0b00100000));
	else if (buffer[0] == 238 || buffer[0] == 239)
		return (1);
	else
		return (0);
}

int		is_utf8_len_4(unsigned char *buffer)
{
	if (!is_utf8_len_header(buffer[0], 4) || !is_utf8_next_byte(buffer[1])
			|| !is_utf8_next_byte(buffer[2]) || !is_utf8_next_byte(buffer[3]))
		return (0);
	else if (buffer[0] == 240)
	{
		return ((buffer[1] & 0b00100000) ||
			(!(buffer[1] & 0b00100000) && buffer[1] & 0b00010000));
	}
	else if (buffer[0] == 241)
		return (1);
	else if (!(buffer[0] & 0b00000100) && buffer[0] & 0b00000010)
		return (1);
	else if (buffer[0] == 244)
		return (!(buffer[1] & 0b00100000) && !(buffer[1] & 0b00010000));
	return (0);
}

int		is_printable_utf8(unsigned char *buffer, int nb_bytes)
{
	if (nb_bytes == 1)
		return (buffer[0] >= 32 && buffer[0] <= 126 &&
			!(buffer[0] & 0b10000000));
	else if (nb_bytes == 2)
		return (is_utf8_len_header(buffer[0], 2)
			&& is_utf8_next_byte(buffer[1]));
	else if (nb_bytes == 3)
		return (is_utf8_len_3(buffer));
	else if (nb_bytes == 4)
		return (is_utf8_len_4(buffer));
	else
		return (0);
}
