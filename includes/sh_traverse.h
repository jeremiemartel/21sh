/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:35:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/29 15:23:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TRAVERSE_H
# define SH_TRAVERSE_H

# include "sh_21.h"

typedef struct dirent	t_dirent;

/*
********************************************************************************
*/

/*
** sh_traverse_greatand.c
*/
int		sh_traverse_greatand(t_ast_node *node, t_context *context);

/*
** sh_traverse_pipe_sequence_execute.c
*/
int		sh_traverse_pipe_sequence_execute(
	t_ast_node *node, t_context *context);

/*
** sh_traverse_io_here.c
*/
char	*heredoc_dash(const char *str);
int		sh_traverse_io_here(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_word.c
*/
int		sh_traverse_cmd_word(t_ast_node *node, t_context *context);

/*
** sh_traverse_lessgreat.c
*/
int		sh_traverse_lessgreat(t_ast_node *node, t_context *context);

/*
** sh_traverse_list.c
*/
int		sh_traverse_list(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_here_canonical.c
*/
void	populate_command_line(t_command_line *command_line, char *str);
int		heredoc_canonical_mode_eof(
	char *eof, t_gnl_info *info, char **res);
char	*heredoc_gnl_error(int *ret, char **res);
char	*heredoc_canonical_mode(
	t_shell *shell, char *eof, char *(*heredoc_func)(const char *), int *ret);

/*
** sh_traverse_simple_command.c
*/
int		sh_process_traverse_simple_command_exec(
	t_context *context, int *ret);
int		sh_traverse_simple_command_exec(
	t_ast_node *node, t_context *context);
int		sh_traverse_simple_command_no_exec(
	t_ast_node *node, t_context *context);
int		sh_traverse_simple_command(t_ast_node *node, t_context *context);
int		sh_traverse_sc_no_slash_cmd(t_context *context);

/*
** sh_traverse_io_file.c
*/
int		get_io_file_return(
	t_ast_node *redir_child, char *filename, t_context *context);
int		sh_traverse_io_file(t_ast_node *node, t_context *context);

/*
** sh_traverse_great.c
*/
int		sh_traverse_great(t_ast_node *node, t_context *context);

/*
** sh_traverse_default.c
*/
int		sh_traverse_default(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_suffix.c
*/
// int		sh_process_traverse_cmd_suffix(
	// t_ast_node *child, t_context *context);
int		sh_traverse_cmd_suffix(t_ast_node *node, t_context *context);

/*
** sh_traverse_simple_command_tools.c
*/
int		sh_found_sc_search_in_hash(
	t_context *context, t_binary *binary, t_hash_finder finder);
int		sh_traverse_sc_search_in_hash(t_context *context);
int		sh_traverse_sc_search_in_dir(
	char *path, DIR *dir, t_context *context);
int		sh_traverse_sc_search_in_path(t_context *context);

/*
** sh_traverse_dgreat.c
*/
int		sh_traverse_dgreat(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_redirect.c
*/
int		sh_traverse_io_redirect(t_ast_node *node, t_context *context);

/*
** sh_traverse_cmd_name.c
*/
int		sh_traverse_cmd_name(t_ast_node *node, t_context *context);

/*
** sh_traverse_io_file_tools.c
*/
void	set_failed_command(t_context *context);
int		sh_process_file_output(
	char *filename, t_context *context, int options);
int		sh_process_file_input(
	char *filename, t_context *context, int options);

/*
** sh_traverse.c
*/
int		sh_process_traverse(t_shell *shell);

/*
** sh_traverse_less.c
*/
int		sh_traverse_less(t_ast_node *node, t_context *context);

/*
** sh_traverse_and_or.c
*/
int		sh_traverse_and_or_launch_phase(
	t_ast_node *node, t_context *context);
int		sh_traverse_and_or(t_ast_node *node, t_context *context);

/*
** sh_traverse_simple_command_check_perm.c
*/
int		sh_traverse_sc_check_perm_quiet(char *path);
int		sh_traverse_sc_check_perm(
	t_context *context, char *path, char *command_name);

/*
** sh_traverse_pipe_sequence.c
*/
int		sh_traverse_pipe_sequence(t_ast_node *node, t_context *context);

/*
** sh_traverse_assigment_word.c
*/
int		sh_traverse_assigment_word(t_ast_node *node, t_context *context);

/*
** sh_traverse_semicol.c
*/
int		sh_traverse_semicol(t_ast_node *node, t_context *context);

/*
** sh_traverse_lessand.c
*/
int		sh_traverse_lessand(t_ast_node *node, t_context *context);

#endif
