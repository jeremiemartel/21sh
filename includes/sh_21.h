/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/26 16:45:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

#include "libft.h"
#include <stdio.h> //todel

# define SH_LEXER_AUTO_LEN	5

# define end	-1
# define error	-2
# define DEBUG_BUFFER_SIZE	50

typedef struct		s_automate
{
	int				status;
	int				(*automate)(int status, char c);
}					t_automate;

typedef enum		e_tokenlist
{
	UNKNOWN = -1,
	SPACE,
	WHILE,
	GREAT,
	LESS,
	WORD,
}					t_tokenlist;

typedef enum		e_token_id
{
	LEX_TOK_PIPE ,// '|',
	LEX_TOK_AND ,// '&',
	LEX_TOK_SEMICOL ,// ';',
	LEX_TOK_LESS ,// '<',
	LEX_TOK_GREAT ,// '>',
	LEX_TOK_OPN_PAR ,// '(',
	LEX_TOK_CLS_PAR ,// ')',
	LEX_TOK_LBRACE ,// '{',
	LEX_TOK_RBRACE ,// '}',
	LEX_TOK_BANG ,// '!',
	LEX_TOK_DOLLAR ,// '$',
	//Quoting tokens
	LEX_TOK_BACK_SLASH ,//'\\',
	LEX_TOK_QUOTE_BACK ,// '`',
	LEX_TOK_QUOTE_SPL ,// '\'',
	LEX_TOK_QUOTE_DBL ,// '"',
	LEX_TOK_SPACE ,// ' ',
	LEX_TOK_TAB ,// '\t',
	LEX_TOK_NEWLINE ,// '\n',
	//Special chars
	LEX_TOK_STAR ,// '*',
	LEX_TOK_QUEST ,// '?',
	LEX_TOK_HASH ,// '#',
	LEX_TOK_TILD ,// '~',
	LEX_TOK_EQUAL,// '='
	LEX_TOK_PERCENT ,// '%',
	//Composed operators
	LEX_TOK_AND_IF      ,// '&' + 0xff00 * '&',               //&&
	LEX_TOK_OR_IF       ,// '|' + 0xff00 * '|',               //||
	LEX_TOK_DSEMI       ,// ';' + 0xff00 * ';',               //;;
	LEX_TOK_DLESS       ,// '<' + 0xff00 * '<',               //<<
	LEX_TOK_DGREAT      ,// '>' + 0xff00 * '>',               //>>
	LEX_TOK_LESSAND     ,// '<' + 0xff00 * '&',               //<&
	LEX_TOK_GREATAND    ,// '>' + 0xff00 * '&',               //>&
	LEX_TOK_LESSGREAT   ,// '<' + 0xff00 * '>',               //<>
	LEX_TOK_DLESSDASH   ,// '<' + 0xff00 * '<' + 0xff0000 * '-',  //<<-
	LEX_TOK_CLOBBER     ,// '>' + 0xff00 * '|',               //>|
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
	LEX_TOK_IN,
	//Other
	LEX_TOK_TOKEN,
	LEX_TOK_WORD,
	LEX_TOK_ASSIGNMENT_WORD,
	LEX_TOK_NAME,
	LEX_TOK_IO_NUMBER,
	//Specials
	END_OF_INPUT,
	EPS,

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
	SEQUENTIAL_SEP,
	NB_SYMBOLS
}					t_token_id;

typedef struct		u_token_union
{
	int				ival;
	double			fval;
	char			*str;
}					t_token_union;

typedef enum		e_token_type
{
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_STR
}					t_token_type;

typedef struct		s_token
{
	t_token_type	token_type;
	t_token_union	token_union;
	t_token_id		token_id;
}					t_token;

typedef struct		s_production
{
	t_list			*symbols;
	//function ?
}					t_production;

# define NB_TERMS	PROGRAM
# define NB_NOTERMS	NB_SYMBOLS - NB_TERMS

typedef struct		s_symbol
{
	t_list			*productions;
	int				id;
	char			first_sets[NB_TERMS];
	char			follow_sets[NB_TERMS];
	char			debug[DEBUG_BUFFER_SIZE];
	int				splits;
}					t_symbol;

typedef struct		s_cfg
{
	t_dy_tab		symbols;
	t_production	***ll_table;
	int				start_index;
}					t_cfg;

typedef struct		s_list_manager
{
	t_list			*head;
	t_list			*previous;
	t_list			*current;
}					t_list_manager;

/*
** ll_table:
**
**
**
**  				_____________________________________________________
**  				|				|				|					|
**  				|				|				|					|
**  				|      Term1	|	Term2		|		Term3		|
**  				|				|				|					|
**   _______________|_______________|_______________|___________________|
**  |				|				|				|					|
**  |				|				|				|					|
**  |	NoTerm1		|		NULL	|	&prod2		|		NULL		|
**  |				|				|				|					|
**	|_______________|_______________|_______________|___________________|
**  |				|				|				|					|
**  |				|				|				|					|
**  |	NoTerm2		|	&prod7		|	&prod2		|		&prod4		|
**  |				|				|				|					|
**  |_______________|_______________|_______________|___________________|
**	
**
** double table (NB_TERMS columns and NB_NO_TERMS lines) 
**
** says which production to choose for a non terminal given a terminal
*/

typedef struct		s_grammar_holder
{
	char			*debug;
	char			relevant;
	char			replacing;
	int 			(*init_prod)(t_cfg *, t_symbol *);
}					t_grammar_holder;

typedef struct		s_parser
{
	t_cfg			cfg;
	t_list			*pda_stack;
	t_list			*tokens;
}					t_parser;

/*
** lexer.c
*/
int			ft_isseparator(char c);
int			sh_lexer(char *input);

/*
** lexer_automates.c
*/
int			sh_lexer_auto_while(int status, char c);
int			sh_lexer_auto_less(int status, char c);
int			sh_lexer_auto_great(int status, char c);
int			sh_lexer_auto_word(int status, char c);
int			sh_lexer_auto_space(int status, char c);

/*
** lexer_automates_tools.c
*/
void		sh_lexer_automate_init(t_automate automates[]);
void		sh_lexer_automate_run(t_automate automates[], char c);
int			sh_lexer_automate_check(t_automate automates[]);
void		sh_lexer_automate_show_status(t_automate automates[], char c);
void		sh_lexer_show_token(int token);


/*
** parser.c
*/
t_symbol		*sh_new_symbol_from(t_symbol *from, t_token_id id);
int				sh_process_test(void);
int				sh_parse_token_list(t_list *tokens);
int				sh_is_term(t_symbol *symbol);
t_production	*sh_production_lst_dup_ptr(t_list *ptr);
int				sh_add_prod(t_symbol *symbol, t_dy_tab symbols,
					int nb_symbols, ...);
int				sh_add_prod_from_symbols(t_symbol *symbol, t_list *symbols);
//int				sh_add_to_prod(void **vcfg_symbols, t_list **symbols,
//					int nb_symbols, ...);
/*
** first_sets.c
*/
void		sh_init_first_sets(char first_sets[NB_TERMS]);
int			sh_compute_first_sets(t_cfg *cfg);
int			sh_compute_first_sets_str(t_cfg *cfg, char first_sets[NB_TERMS], t_list *w);
/*
** follow_sets.c
*/
int				sh_compute_follow_sets(t_cfg *cfg);
t_production	*sh_get_null_production(t_symbol *symbol);
int				sh_intersect_sets(char set1[NB_TERMS], char set2[NB_TERMS]);
int				sh_nullable(t_symbol *symbol);
/*
** debug.c
*/
void  	sh_print_symbol_list(t_list *symbols);
void  	sh_print_pda(t_list *symbols);
void	sh_print_symbol(t_symbol *symbol);
void	sh_print_production(t_production *prod);
void	sh_print_token_list(t_list *list);
void	sh_print_non_terminals_productions(t_cfg *cfg);
void	sh_print_non_terminal_production(t_symbol *symbol);
void	print_first_sets(t_cfg *cfg);
void	print_follow_sets(t_cfg *cfg);
void	sh_process_print_set(t_cfg *cfg, char sets[NB_TERMS]);
void	print_ll_table(t_cfg *cfg);
void	print_cfg(t_cfg *cfg);
/*
** lltable.c
*/
int		sh_compute_ll_table(t_cfg *cfg);

/*
** refine_grammar.c
*/

int		sh_process_production_left_recursion(t_symbol *symbol, t_list *symbols);
int		sh_refine_grammar(t_cfg *cfg);

t_grammar_holder    g_grammar[NB_SYMBOLS];

#endif
