/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:17:04 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/26 09:09:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_and_or(t_ast_node *node, t_context *context)
{
	return (sh_traverse_tools_browse(node, context));
}
