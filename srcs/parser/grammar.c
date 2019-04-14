/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:19:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/08 14:19:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** describes posix grammar symbols
**
** 1: debug string
** 2: ability to replace the parent node in the ast
** 3: relevance in the grammar
** 4: productions init function
*/

t_grammar_holder g_grammar[NB_SYMBOLS] = {
	{"UNKNOWN", 0, 1, NULL},
	{"|", 0, 1, NULL},
	{"&", 0, 1, NULL},
	{";", 0, 1, NULL},
	{"<", 0, 1, NULL},
	{">", 0, 1, NULL},
	{"(", 0, 1, NULL},
	{")", 0, 1, NULL},
	{"{", 0, 1, NULL},
	{"}", 0, 1, NULL},
	{"!", 0, 1, NULL},
	{"$", 0, 1, NULL},
	{"\\", 0, 1, NULL},
	{"`", 0, 1, NULL},
	{"'", 0, 1, NULL},
	{"\"", 0, 1, NULL},
	{"TERM_SPACE", 0, 1, NULL},
	{"TERM_TAB", 0, 1, NULL},
	{"TERM_NEW_LINE", 0, 1, NULL},
	{"*", 0, 1, NULL},
	{"?", 0, 1, NULL},
	{"#", 0, 1, NULL},
	{"~", 0, 1, NULL},
	{"=", 0, 1, NULL},
	{"%", 0, 1, NULL},
	{"&&", 0, 1, NULL},
	{"||", 0, 1, NULL},
	{";;", 0, 1, NULL},
	{"<<", 0, 1, NULL},
	{">>", 0, 1, NULL},
	{"<&", 0, 1, NULL},
	{">&", 0, 1, NULL},
	{"<>", 0, 1, NULL},
	{"<<-", 0, 1, NULL},
	{">|", 0, 1, NULL},
	{"if", 0, 1, NULL},
	{"then", 0, 1, NULL},
	{"else", 0, 1, NULL},
	{"elif", 0, 1, NULL},
	{"fi", 0, 1, NULL},
	{"do", 0, 1, NULL},
	{"done", 0, 1, NULL},
	{"case", 0, 1, NULL},
	{"esac", 0, 1, NULL},
	{"while", 0, 1, NULL},
	{"until", 0, 1, NULL},
	{"for", 0, 1, NULL},
	{"in", 0, 1, NULL},
	{"TERM_TOKEN", 0, 1, NULL},
	{"TERM_WORD", 0, 1, NULL},
	{"TERM_ASSIGNMENT_WORD", 0, 1, NULL},
	{"TERM_NAME", 0, 1, NULL},
	{"TERM_IO_NUMBER", 0, 1, NULL},
	{"_EOI_", 0, 1, NULL},
	{"ε", 0, 1, NULL},
	{"PROGRAM", 0, 1, &sh_init_prod_program},
	{"COMPLETE_COMMANDS", 0, 1, &sh_init_prod_complete_commands},
	{"COMPLETE_COMMAND", 0, 1, &sh_init_prod_complete_command},
	{"LIST", 0, 1, &sh_init_prod_list},
	{"AND_OR", 0, 1, &sh_init_prod_and_or},
	{"PIPELINE", 0, 1, &sh_init_prod_pipeline},
	{"PIPE_SEQUENCE", 0, 1, &sh_init_prod_pipe_sequence},
	{"COMMAND", 0, 1, &sh_init_prod_command},
	{"COMPOUND_COMMAND", 0, 1, &sh_init_prod_compound_command},
	{"SUBSHELL", 0, 1, &sh_init_prod_subshell},
	{"COMPOUND_LIST", 0, 1, &sh_init_prod_compound_list},
	{"TERM", 0, 1, &sh_init_prod_term},
	{"FOR_CLAUSE", 0, 1, &sh_init_prod_for_clause},
	{"NAME", 0, 1, &sh_init_prod_name},
	{"IN", 0, 1, &sh_init_prod_in},
	{"WORDLIST", 0, 1, &sh_init_prod_wordlist},
	{"CASE_CLAUSE", 0, 1, &sh_init_prod_case_clause},
	{"CASE_LIST_NS", 0, 1, &sh_init_prod_case_list_ns},
	{"CASE_LIST", 0, 1, &sh_init_prod_case_list},
	{"CASE_ITEM_NS", 0, 1, &sh_init_prod_case_item_ns},
	{"CASE_ITEM", 0, 1, &sh_init_prod_case_item},
	{"PATTERN", 0, 1, &sh_init_prod_pattern},
	{"IF_CLAUSE", 0, 1, &sh_init_prod_if_clause},
	{"ELSE_PART", 0, 1, &sh_init_prod_else_part},
	{"WHILE_CLAUSE", 0, 1, &sh_init_prod_while_clause},
	{"UNTIL_CLAUSE", 0, 1, &sh_init_prod_until_clause},
	{"FUNCTION_DEFINITION", 0, 1, &sh_init_prod_function_definition},
	{"FUNCTION_BODY", 0, 1, &sh_init_prod_function_body},
	{"FNAME", 0, 1, &sh_init_prod_fname},
	{"BRACE_GROUP", 0, 1, &sh_init_prod_brace_group},
	{"DO_GROUP", 0, 1, &sh_init_prod_do_group},
	{"SIMPLE_COMMAND", 0, 1, &sh_init_prod_simple_command},
	{"CMD_NAME", 0, 1, &sh_init_prod_cmd_name},
	{"CMD_WORD", 0, 1, &sh_init_prod_cmd_word},
	{"CMD_PREFIX", 0, 1, &sh_init_prod_cmd_prefix},
	{"CMD_SUFFIX", 1, 1, &sh_init_prod_cmd_suffix},
	{"REDIRECT_LIST", 0, 1, &sh_init_prod_redirect_list},
	{"IO_REDIRECT", 0, 1, &sh_init_prod_io_redirect},
	{"IO_FILE", 0, 1, &sh_init_prod_io_file},
	{"FILENAME", 0, 1, &sh_init_prod_filename},
	{"IO_HERE", 0, 1, &sh_init_prod_io_here},
	{"HERE_END", 0, 1, &sh_init_prod_here_end},
	{"NEWLINE_LIST", 0, 1, &sh_init_prod_newline_list},
	{"LINEBREAK", 0, 0, &sh_init_prod_linebreak},
	{"SEPARATOR_OP", 0, 1, &sh_init_prod_separator_op},
	{"SEPARATOR", 0, 1, &sh_init_prod_separator},
	{"SEQUENTIAL_SEP", 0, 1, &sh_init_prod_sequential_sep}
};
