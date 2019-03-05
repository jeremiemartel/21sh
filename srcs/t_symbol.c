/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_symbol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:18:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/03/05 21:13:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_symbol	*t_symbol_new(int id)
{
	t_symbol	*symbol;

	if (!(symbol = malloc(sizeof(*symbol))))
		return (NULL);
	symbol->productions = NULL;
	symbol->first_sets = NULL;
	symbol->id = id;
	ft_strcpy(symbol->value, t_cfg_init_symbol_get_value(id));
	return (symbol);
}

int			t_symbol_add_prod(t_symbol *symbol, int len, ...)
{
	va_list		va;
	t_list		*production;
	int			i;
	int			id;

	va_start(va, len);
	i = 0;
	id = 0;
	while (i < len)
	{
		id = va_arg(va, int);
		if (ft_lstaddnew_last(&production, t_symbol_new(id), sizeof(t_symbol)))
			return (1);
			i++;
	}
	va_end(va);
	ft_lstadd_last(&(symbol)->productions, production);
	return (0);
}

void		t_symbol_show(int id)
{
	if (id == OPN_PARENT)
		ft_putchar('(');
	else if (id == CLS_PARENT)
		ft_putchar(')');
	else if (id == PLUS)
		ft_putchar('+');
	else if (id == MULT)
		ft_putchar('*');
	else if (id == INT)
		ft_putstr("INT");
	else if (id == E)
		ft_putstr("E");
	else if (id == OP)
		ft_putstr("OP");
	else if (id == END_OF_LINE)
		ft_putstr("EOL");
	ft_putchar(' ');
}
