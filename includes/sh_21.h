/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 14:22:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

#include "libft.h"

# define SH_LEXER_AUTO_LEN	5

# define end	-1
# define error	-2
# define DEBUG_BUFFER	50

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

typedef enum		e_test_token_id
{
	T_A,
	T_B,
	T_C,
	T_D,
	END_OF_INPUT,
	EPS, //end of terminals
	S,
	A,
	B,
	C,
	D,
	CPRIME,
	X,
	Y,
	NB_SYMBOLS
}					t_test_token_id;

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
	t_test_token_id	token_id;
}					t_token;

typedef struct		s_production
{
	t_list			*symbols;
	//function ?
}					t_production;

# define NB_TERMS	S
# define NB_NOTERMS	NB_SYMBOLS - S

typedef struct		s_symbol
{
	t_list			*productions;
	int				id;
	char			first_sets[NB_TERMS];
	char			follow_sets[NB_TERMS];
	char			debug[DEBUG_BUFFER];
}					t_symbol;


typedef struct		s_cfg
{
	t_symbol		symbols[NB_SYMBOLS];
	t_production	*ll_table[NB_NOTERMS][NB_TERMS];
	int				start_index;
}					t_cfg;

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
int			sh_process_test(void);
int			sh_parse_token_list(t_list *tokens);
int			sh_is_term(t_symbol *symbol);
/*
** first_sets.c
*/
void		sh_init_first_sets(char first_sets[NB_TERMS]);
int			sh_compute_first_sets(t_cfg *cfg);
int			sh_compute_first_sets_str(t_cfg *cfg, char first_sets[NB_TERMS], t_list *w);
/*
** follow_sets.c
*/
int     sh_compute_follow_sets(t_cfg *cfg);

/*
** debug.c
*/
void  	sh_print_symbol_list(t_list *symbols);
void  	sh_print_pda(t_list *symbols);
void	sh_print_symbol(t_symbol *symbol);
void	sh_print_token_listwye(t_list *list);
void	sh_print_production(t_production *production);
void	print_non_terminals_productions(t_cfg *cfg);
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
typedef enum		e_tokenlist
{
	UNKNOWN,	//May be useless, need to see later
	TOKEN,		//token context dependent, transition state
	WORD,
	NAME,
	ASSIGMENT,
	IO_NUMBER,	//only digits and oneof '<' or '>'
	NEWLINE,	//'\n'
	DELIMITOR,	//';'
	DLESS,		//'<<'
	DGREAT,		//'>>'
	LESSAND,	//'<&'
	GREADAND,	//'>&'
	LESSGREAT,	//'<>'
	DLESSDASH,	//'<<-'
	CLOBBER		//'>|'
}					t_tokenlist;
*/

#endif
