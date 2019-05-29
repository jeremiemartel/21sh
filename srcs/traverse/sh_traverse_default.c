/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_default.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/26 11:47:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_default(t_ast_node *node, t_context *context)
{
	return (sh_traverse_tools_browse(node, context));
}
