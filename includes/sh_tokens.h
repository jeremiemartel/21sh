/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tokens.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:18:14 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/13 11:20:40 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TOKENS_H
# define SH_TOKENS_H

# define NB_PRODUCTIONS	112
# define NB_SYMBOLS 102
# define NB_TERMS	55
# define NB_NOTERMS	NB_SYMBOLS - NB_TERMS

typedef enum		e_tokenlist
{
	UNKNOWN = -1,
	SPACE,
	WHILE,
	GREAT,
	LESS,
	WORD,
}					t_tokenlist;

typedef enum		e_symbol_id
{
	LEX_TOK_UNKNOWN = 0, //1
	//simple operators
	LEX_TOK_PIPE = '|', //2
	LEX_TOK_AND = '&', //3
	LEX_TOK_SEMICOL = ';', //4
	LEX_TOK_LESS = '<', //5
	LEX_TOK_GREAT = '>', //6
	LEX_TOK_OPN_PAR = '(', //7
	LEX_TOK_CLS_PAR = ')', //8 
	LEX_TOK_LBRACE = '{', //9 
	LEX_TOK_RBRACE = '}', //10
	LEX_TOK_BANG = '!', //11
	LEX_TOK_DOLLAR = '$', //12
	//Quoting tokens
	LEX_TOK_BACK_SLASH = '\\', //13
	LEX_TOK_QUOTE_BACK = '`', //14
	LEX_TOK_QUOTE_SPL = '\'', //15
	LEX_TOK_QUOTE_DBL = '"', //16
	LEX_TOK_SPACE = ' ', //17
	LEX_TOK_TAB = '\t', //18
	LEX_TOK_NEWLINE = '\n', //19
	//Special chars
	LEX_TOK_STAR = '*', //20
	LEX_TOK_QUEST = '?', //21
	LEX_TOK_HASH = '#', //22
	LEX_TOK_TILD = '~', //23
	LEX_TOK_EQUAL = '=', //24
	LEX_TOK_PERCENT = '%', //25
	//Composed operators
	LEX_TOK_AND_IF = '&' + 0xff00 * '&', //26				//&&
	LEX_TOK_OR_IF = '|' + 0xff00 * '|',	//27			//||
	LEX_TOK_DSEMI = ';' + 0xff00 * ';',	//28			//;;
	LEX_TOK_DLESS = '<' + 0xff00 * '<',	//29			//<<
	LEX_TOK_DGREAT = '>' + 0xff00 * '>', //30				//>>
	LEX_TOK_LESSAND = '<' + 0xff00 * '&', //31				//<&
	LEX_TOK_GREATAND = '>' + 0xff00 * '&', //32				//>&
	LEX_TOK_LESSGREAT = '<' + 0xff00 * '>',	//33			//<>
	LEX_TOK_DLESSDASH = '<' + 0xff00 * '<' + 0xff0000 * '-',//34	//<<-
	LEX_TOK_CLOBBER = '>' + 0xff00 * '|',	//35			//>| // index 34
	
	LEX_TOK_IF,
	LEX_TOK_THEN,
	LEX_TOK_ELSE,
	LEX_TOK_ELIF,
	LEX_TOK_FI,
	LEX_TOK_DO,
	LEX_TOK_DONE,
	LEX_TOK_CASE,
	LEX_TOK_ESAC,
	LEX_TOK_WHILE,
	LEX_TOK_UNTIL,
	LEX_TOK_FOR,
	LEX_TOK_IN, //index 47

	//Other
	LEX_TOK_TOKEN = 130,
	LEX_TOK_WORD,
	LEX_TOK_ASSIGNMENT_WORD, //index 50
	LEX_TOK_NAME,
	LEX_TOK_IO_NUMBER,

		//Specials
	END_OF_INPUT,
	EPS, //index 54 (NB_TERMS = 55)

	//Non Terminals

	PROGRAM,
	COMPLETE_COMMANDS,
	COMPLETE_COMMAND,
	LIST,
	AND_OR,
	PIPELINE,
	PIPE_SEQUENCE,
	COMMAND,
	COMPOUND_COMMAND,
	SUBSHELL,
	COMPOUND_LIST,
	TERM,
	FOR_CLAUSE,
	NAME,
	IN,
	WORDLIST,
	CASE_CLAUSE,
	CASE_LIST_NS,
	CASE_LIST,
	CASE_ITEM_NS,
	CASE_ITEM,
	PATTERN,
	IF_CLAUSE,
	ELSE_PART,
	WHILE_CLAUSE,
	UNTIL_CLAUSE,
	FUNCTION_DEFINITION,
	FUNCTION_BODY,
	FNAME,
	BRACE_GROUP,
	DO_GROUP,
	SIMPLE_COMMAND,
	CMD_NAME,
	CMD_WORD,
	CMD_PREFIX,
	CMD_SUFFIX,
	REDIRECT_LIST,
	IO_REDIRECT,
	IO_FILE,
	FILENAME,
	IO_HERE,
	HERE_END,
	NEWLINE_LIST,
	LINEBREAK,
	SEPARATOR_OP,
	SEPARATOR,
	SEQUENTIAL_SEP, // + 47
}					t_symbol_id;

#endif
