/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 10:02:15 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/29 10:02:15 by ldedier          ###   ########.fr       */
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
	{"TERM_LINE", 0, 1, NULL},
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
	{"PROGRAM", 0, 1, NULL},
	{"COMPLETE_COMMANDS", 0, 1, NULL},
	{"COMPLETE_COMMAND", 0, 1, NULL},
	{"LIST", 0, 1, NULL},
	{"AND_OR", 0, 1, NULL},
	{"PIPELINE", 0, 1, NULL},
	{"PIPE_SEQUENCE", 0, 1, NULL},
	{"COMMAND", 0, 1, NULL},
	{"COMPOUND_COMMAND", 0, 1, NULL},
	{"SUBSHELL", 0, 1, NULL},
	{"COUMPOUND_LIST", 0, 1, NULL},
	{"TERM", 0, 1, NULL},
	{"FOR_CLAUSE", 0, 1, NULL},
	{"NAME", 0, 1, NULL},
	{"IN", 0, 1, NULL},
	{"WORDLIST", 0, 1, NULL},
	{"CASE_CLAUSE", 0, 1, NULL},
	{"CASE_LIST_NS", 0, 1, NULL},
	{"CASE_LIST", 0, 1, NULL},
	{"CASE_ITEM_NS", 0, 1, NULL},
	{"CASE_ITEM", 0, 1, NULL},
	{"PATTERN", 0, 1, NULL},
	{"IF_CLAUSE", 0, 1, NULL},
	{"ELSE_PART", 0, 1, NULL},
	{"WHILE_CLAUSE", 0, 1, NULL},
	{"UNTIL_CLAUSE", 0, 1, NULL},
	{"FUNCTION_DEFINITION", 0, 1, NULL},
	{"FUNCTION_BODY", 0, 1, NULL},
	{"FNAME", 0, 1, NULL},
	{"BRACE_GROUP", 0, 1, NULL},
	{"DO_GROUP", 0, 1, NULL},
	{"SIMPLE_COMMAND", 0, 1, NULL},
	{"CMD_NAME", 0, 1, NULL},
	{"CMD_WORD", 0, 1, NULL},
	{"CMD_PREFIX", 0, 1, NULL},
	{"CMD_SUFFIX", 0, 1, NULL},
	{"REDIRECT_LIST", 0, 1, NULL},
	{"IO_REDIRECT", 0, 1, NULL},
	{"IO_FILE", 0, 1, NULL},
	{"FILENAME", 0, 1, NULL},
	{"IO_HERE", 0, 1, NULL},
	{"HERE_END", 0, 1, NULL},
	{"NEWLINE_LIST", 0, 1, NULL},
	{"LINEBREAK", 0, 1, NULL},
	{"SEPARATOR_OP", 0, 1, NULL},
	{"SEPARATOR", 0, 1, NULL},
	{"SEQUENTIAL_SEP", 0, 1, NULL}
};
