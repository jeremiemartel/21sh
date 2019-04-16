/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:35:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/16 14:13:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TRAVERSE_H
# define SH_TRAVERSE_H

# include "sh_21.h"

int			sh_process_traverse(t_shell *shell);
int			sh_traverse_default(t_ast_node *this, t_context *context);

int			sh_traverse_cmd_name(t_ast_node *this, t_context *context);
int			sh_traverse_cmd_suffix(t_ast_node *this, t_context *context);
int			sh_traverse_complete_command(t_ast_node *this, t_context *context);
int			sh_traverse_simple_command(t_ast_node *node, t_context *context);
int			sh_traverse_pipe_sequence(t_ast_node *node, t_context *context);
int			sh_traverse_tok_pipe(t_ast_node *node, t_context *context);

#endif
