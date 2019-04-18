/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:47:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/18 12:58:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TRAVERSE_TOOLS_H
# define SH_TRAVERSE_TOOLS_H

/*
** sh_travers_tools_flush.c
*/
int			sh_traverse_tools_flush(t_context *context);

/*
** sh_traverse_tools_browse.c
*/
int			sh_traverse_tools_browse(t_ast_node *node, t_context *context);
int	    	sh_traverse_tools_browse_one_child(t_ast_node *node, t_context *context);

/*
** sh_traverse_tools_reset.c
*/
void	sh_traverse_tools_reset_std(t_context *context);
void	sh_traverse_tools_reset_params(t_context *context);

/*
** sh_traverse_tools_context.c
*/
void		sh_traverse_update_father(t_ast_node *node, t_context *context);


#endif
