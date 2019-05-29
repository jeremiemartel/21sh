/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 20:33:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/26 09:09:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_pipeline(t_ast_node *node, t_context *context)
{
	return (sh_traverse_tools_browse(node, context));
}
