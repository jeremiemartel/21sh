/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:47:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/11 10:32:39 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TRAVERSE_TOOLS_H
# define SH_TRAVERSE_TOOLS_H

/*
********************************************************************************
*/

/*
** sh_traverse_tools_browse.c
*/
int		sh_traverse_tools_browse(t_ast_node *node, t_context *context);
int		sh_traverse_tools_browse_one_child(
	t_ast_node *node, t_context *context);

/*
** sh_traverse_tools_reset.c
*/
void	sh_traverse_tools_reset_context(t_context *context);
void	sh_traverse_tools_reset_params(t_context *context);

#endif
