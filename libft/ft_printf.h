/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:47:38 by jmartel           #+#    #+#             */
/*   Updated: 2019/01/16 21:37:55 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** NB : types priority in files : di, xo, u, f, p,  s, c
** When needed you will find di, x, o, u, f in the first file
** p, s, c and % are in the printf_XXXX2.c
*/

/*
** Definition of a char used to represent non conversion type (text only)
*/
# define TYPE_TEXT '$'

/*
**Definition of values used when precision or size are not precised
*/
# define NO_PREC -1
# define NO_SIZE -1

/*
** Bitewises associated to different flags
*/
# define CAST_H		0x0001
# define CAST_HH	0x0002
# define CAST_L		0x0004
# define CAST_LL	0x0008

# define FLAG_PLUS	0x0010
# define FLAG_MINUS	0x0020
# define FLAG_ZERO	0x0040
# define FLAG_HASH	0x0080
# define FLAG_SPACE	0x0100

/*
** Including libft header
*/
# include "libft.h"

/*
** malloc, free, exit
*/
# include <stdlib.h>

/*
** write (2)
*/
# include <unistd.h>

/*
** stdarg : va_start, va_arg, va_copy, va_end
*/
# include <stdarg.h>

/*
** s_conv struct is used to represent any part of the format input string
** - type is used to stock the type of conversion
** - conv : stock the flags given as bytes,  defined by sub-macros
** - size : stock the size given, NO_SIZE if not given
** - prec : stock the precision given, NO_PREC if not given
** - res : stock the result of the conversion as a string
** - next : stock the adress of next link
*/
typedef struct		s_conv
{
	char		type;
	int			conv;
	int			size;
	int			prec;
	char		*res;
	void		*next;
}					t_conv;

/*
** ./ft_printf.c
*/
int					ft_printf(const char *format, ...);
int					ft_printf_args(t_conv *head, va_list va);

/*
** ./ft_dprintf.c
*/
int					ft_dprintf(int fd, const char *format, ...);

/*
** ./ft_asprintf.c
*/
char				*ft_asprintf(const char *format, ...);
char				*ft_asprintf_result(t_conv *start);

/*
** ./ft_printf_split.c
*/
t_conv				*ft_printf_split(const char *format);
t_conv				*ft_printf_split_push_conv(t_conv **start,
						t_conv *new);
t_conv				*ft_printf_split_new_txt(char *str);
t_conv				*ft_printf_split_new_conv(char *str);
void				ft_printf_split_free_list(t_conv *start);

/*
** ./ft_printf_fill.c ./ft_printf_fill2.c
*/
void				fill_di(va_list va, t_conv *conv);
void				fill_x(va_list va, t_conv *conv);
void				fill_o(va_list va, t_conv *conv);
void				fill_u(va_list va, t_conv *conv);
void				fill_f(va_list va, t_conv *conv);

void				fill_p(va_list va, t_conv *conv);
void				fill_s(va_list va, t_conv *conv);
void				fill_c(va_list va, t_conv *conv);
void				fill_perc(t_conv *conv);
void				fill_b(va_list va, t_conv *conv);

/*
** ./ft_printf_cast.c
*/
void				cast_di(va_list va, t_conv *conv);
unsigned long long	cast_xo(va_list va, t_conv *conv);
unsigned long long	cast_u(va_list va, t_conv *conv);
void				cast_f(va_list va, t_conv *conv);

/*
** ./ft_printf_flag.c
*/
void				flag_plus(t_conv *conv, int sign);
void				flag_space(t_conv *conv, int sign);

/*
** ./ft_printf_flag_hash.c
*/
void				flag_hash_x(t_conv *conv);
void				flag_hash_o(t_conv *conv);
void				flag_hash_f(t_conv *conv);

/*
** ./ft_printf_flag_prec.c ./ft_printf_flag_prec2.c
*/
void				flag_prec_di(t_conv *conv);
void				flag_prec_x(t_conv *conv);
void				flag_prec_o(t_conv *conv);
void				flag_prec_u(t_conv *conv);

void				flag_prec_s(t_conv *cont);

/*
** ./ft_printf_flag_size.c ./ft_printf_flag_size2.c
*/
void				flag_size_di(t_conv *conv);
void				flag_size_x(t_conv *conv);
void				flag_size_o(t_conv *conv);
void				flag_size_u(t_conv *conv);
void				flag_size_f(t_conv *conv);

void				flag_size_p(t_conv *conv);
void				flag_size_s(t_conv *conv);
void				flag_size_c(t_conv *conv);
void				flag_size_perc(t_conv *conv);

/*
** ./ft_printf_conv.c
*/
int					t_conv_len(const char *restrict format);
int					t_conv_new(t_conv *conv, const char *str);
void				t_conv_size_prec(char *str, t_conv *conv);
int					t_conv_detect_zero(char *str);
void				t_conv_free_lst(t_conv *start);

/*
** ./ft_printf_put.c
*/
int					ft_printf_put_result(t_conv *head);
int					ft_dprintf_put_result(int fd, t_conv *head);

/*
** ./ft_printf_conv_is.c
*/
int					conv_isconv(char c);

#endif
