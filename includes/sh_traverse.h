/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:35:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/19 20:26:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TRAVERSE_H
# define SH_TRAVERSE_H

# include "sh_21.h"

int			sh_process_traverse(t_shell *shell);
int			sh_traverse_default(t_ast_node *this, t_context *context);

/*
** COMPLETE_COMMAND and sons
*/
int			sh_traverse_complete_command(t_ast_node *this, t_context *context);
int			sh_traverse_command(t_ast_node *node, t_context *context);
int			sh_traverse_semicol(t_ast_node *node, t_context *context);
int			sh_traverse_and_if(t_ast_node *node, t_context *context);
int			sh_traverse_or_if(t_ast_node *node, t_context *context);
int			sh_traverse_simple_command(t_ast_node *node, t_context *context);
int			sh_traverse_cmd_name(t_ast_node *this, t_context *context);
int			sh_traverse_cmd_word(t_ast_node *this, t_context *context);
int			sh_traverse_cmd_suffix(t_ast_node *this, t_context *context);

/*
** PIPELINE and sons
*/
int			sh_traverse_pipeline(t_ast_node *this, t_context *context);
int			sh_traverse_pipe_sequence(t_ast_node *node, t_context *context);
int			sh_traverse_tok_pipe(t_ast_node *node, t_context *context);

/*
** IO_REDIRECT and sons
*/
int			sh_traverse_io_redirect(t_ast_node *node, t_context *context);
int			sh_traverse_filename(t_ast_node *node, t_context *context);

int			sh_traverse_io_here(t_ast_node *node, t_context *context);

int			sh_traverse_io_file(t_ast_node *node, t_context *context);
int			sh_traverse_less(t_ast_node *node, t_context *context);
int			sh_traverse_lessand(t_ast_node *node, t_context *context);
int			sh_traverse_great(t_ast_node *node, t_context *context);
int			sh_traverse_greatand(t_ast_node *node, t_context *context);
int			sh_traverse_dgreat(t_ast_node *node, t_context *context);

#endif
