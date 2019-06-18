/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:13:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/18 17:13:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*sh_color_depth(int i)
{
	if ((i % 5) == 0)
		return (CYAN);
	else if (i % 5 == 1)
		return (YELLOW);
	else if (i % 5 == 2)
		return (BLUE);
	else if (i % 5 == 3)
		return (GREEN);
	else
		return (MAGENTA);
}

void	sh_print_ast_child(int depth, int *j, t_ast_node *child)
{
	int k;
	int i;

	i = depth;
	k = 0;
	while (i--)
		ft_printf("%s| "EOC, sh_color_depth(k++));
	ft_printf("%sɸ %s%schild #%d:%s", sh_color_depth(k), EOC,
			sh_color_depth(k + 1), ++(*j), EOC);
	sh_print_ast(child, depth + 1);
}

void	sh_print_ast(t_ast_node *node, int depth)
{
	t_list	*ptr;
	int		j;

	if (!node)
	{
		ft_printf("LEAF NODE");
		return ;
	}
	if (!node->token)
		sh_print_symbol(node->symbol);
	else
		sh_print_token(node->token, g_glob.cfg);
	ft_printf("\n");
	ptr = node->children;
	j = 0;
	while (ptr != NULL)
	{
		sh_print_ast_child(depth, &j, (t_ast_node *)ptr->content);
		ptr = ptr->next;
	}
}
