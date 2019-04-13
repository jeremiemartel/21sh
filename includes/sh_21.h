/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/13 11:10:10 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

# include <stdarg.h>
#include "libft.h"

# include "libft.h"

# define DEBUG_BUFFER	50
# define NB_PRODUCTIONS	112
# define NB_SYMBOLS 102

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

typedef struct		s_lexer
{
	char	c;
	char	*input;
	int		tok_start;
	int		tok_len;
	int		current_id;
	int		quoted;
	t_list	*list;
}					t_lexer;

/*
** Expansion header
*/
typedef enum	e_exp_type
{
	LEX_EXP_ERR = -1,
	LEX_EXP_OK = 0,
	LEX_EXP_VAR,
	LEX_EXP_PARAM,
	LEX_EXP_CMD,
	LEX_EXP_ARITH,
}				t_exp_type;

typedef struct	s_pattern
{
	char	start[4];
	char	end[4];
	int		len_s;
	int		len_e;
}				t_pattern;

typedef struct s_expansion
{
	t_dystr		*res;
	char		*original;
	char		*expansion;
	t_exp_type	type;
	t_pattern	pattern;
}				t_expansion;


# define LEX_TOKEN_VALUE_LEN	250

# define LEX_END		3
# define LEX_ERR		2
# define LEX_CONTINUE	1
# define LEX_OK			0

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
	t_symbol_id		id;
	int				index;
	char			value[LEX_TOKEN_VALUE_LEN + 1];
}					t_token;

# define NB_TERMS	55
# define NB_NOTERMS	NB_SYMBOLS - NB_TERMS

typedef struct		s_symbol
{
	t_list			*productions;
	int				id;
	char			first_sets[NB_TERMS];
	char			follow_sets[NB_TERMS];
	char			debug[DEBUG_BUFFER];
	char			relevant;
	char			replacing;
}					t_symbol;

typedef struct		s_production
{
	int				index;
	t_symbol		*from;
	t_list			*symbols;
}					t_production;

typedef struct		s_state
{
	t_list			*transitions;
	t_list			*items;
	t_list			*items_by_production[NB_PRODUCTIONS];
	int				index;
	int				parsed;
}					t_state;

typedef struct		s_transition
{
	t_symbol		*symbol;
	t_state			*state;
}					t_transition;

typedef struct		s_item
{
	t_production	*production;
	t_list			*progress;
	char			lookaheads[NB_TERMS];
	char			parsed;
}					t_item;

typedef struct s_cfg
{
	t_symbol		start_symbol;
	t_symbol		symbols[NB_SYMBOLS];
	t_production	productions[NB_PRODUCTIONS];
}					t_cfg;

/*
** lexer.c
*/

int			lexer(char *input, t_list **tokens);

void		ft_putstr_len(char *str, int len);


int			sh_parser(t_list *tokens);

typedef enum		e_action_enum
{
	ERROR,
	ACCEPT,
	SHIFT,
	REDUCE
}					t_action_enum;

typedef union		u_action_union
{
	t_state			*state;
	t_production	*production;
}					t_action_union;

typedef struct		s_action
{
	t_action_enum	action_enum;
	t_action_union	action_union;
}					t_action;

typedef struct			s_ast_node
{
	t_token				*token;
	struct s_ast_node	*parent;
	t_list				*children;
}						t_ast_node;

typedef struct			s_ast_builder
{
	t_ast_node			*node;
	t_symbol			*symbol;
}						t_ast_builder;

typedef struct		s_lr_parser
{
	t_list			*states;
	t_action		**lr_tables;
	t_cfg			cfg;
	t_list			*tokens;
	t_list			*stack;
	t_ast_node		*root;
}					t_lr_parser;

typedef struct		s_grammar_holder
{
	char			*debug;
	char			relevant;
	char			replacing;
	int 			(*init_prod)(t_cfg *, t_symbol *);
}					t_grammar_holder;

t_grammar_holder	g_grammar[NB_SYMBOLS];


/*
** lexer_expansions.c
*/
int			lexer_expansion(t_lexer *lexer, char **input);

/*
** lexer_expansion_detect.c
*/
int			lexer_expansion_detect(char *input, t_expansion *expansion);
int			lexer_expansion_detect_command(char *input, t_expansion *expansion);
int			lexer_expansion_detect_arithmetic(char *input, t_expansion *expansion);
int			lexer_expansion_detect_parameter(char *input, t_expansion *expansion);
int			lexer_expansion_detect_variable(char *input, t_expansion *expansion);

/*
** lexer_expansion_process.c
*/
int			lexer_expansion_process(t_lexer *lexer, t_expansion *expansion);
int			lexer_expansion_process_command(t_lexer *lexer, t_expansion *expansion);
int			lexer_expansion_process_arithmetic(t_lexer *lexer, t_expansion *expansion);
int			lexer_expansion_process_parameter(t_lexer *lexer, t_expansion *expansion);
int			lexer_expansion_process_variable(t_lexer *lexer, t_expansion *expansion);


/*
** t_lexer.c
*/
void		lexer_init(t_lexer *lexer, int tok_start);
int			lexer_add_token(t_lexer *lexer);
void		lexer_show(t_lexer *lexer);
void		t_lexer_free(t_lexer *lexer);

/*
** lexer_rules.c
*/
int			lexer_rule1(t_lexer *lexer);
int			lexer_rule2(t_lexer *lexer);
int			lexer_rule3(t_lexer *lexer);
int			lexer_rule4(t_lexer *lexer);
int			lexer_rule5(t_lexer *lexer);
int			lexer_rule6(t_lexer *lexer);
int			lexer_rule7(t_lexer *lexer);
int			lexer_rule8(t_lexer *lexer);
int			lexer_rule9(t_lexer *lexer);
int			lexer_rule10(t_lexer *lexer);
int			lexer_rule11(t_lexer *lexer);

/*
** t_token.c
*/
t_token		*t_token_new(int id, char *value);
void		t_token_show(t_token *token);
void		t_token_show_id(int i);
int			sh_process_test(void);
int			sh_parse_token_list(t_lr_parser *parser);
int			sh_is_term(t_symbol *symbol);
/*
** first_sets.c
*/
void		sh_init_first_sets(char first_sets[NB_TERMS]);
int			sh_compute_first_sets(t_cfg *cfg);
int			sh_compute_first_sets_str(t_cfg *cfg, char first_sets[NB_TERMS], t_list *w);
void		sh_process_transitive_first_set_2(char first_sets[NB_TERMS], int index);
void		sh_process_transitive_first_sets_2(char first_sets[NB_TERMS], t_symbol *prod_symbol);
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
void	sh_print_token_list(t_list *list, t_cfg *cfg);
void	sh_print_non_terminals_productions(t_cfg *cfg);
void	sh_print_non_terminal_production(t_symbol *symbol);
void	print_first_sets(t_cfg *cfg);
void	print_follow_sets(t_cfg *cfg);
void	sh_process_print_set(t_cfg *cfg, char sets[NB_TERMS]);
void	sh_print_cfg(t_cfg *cfg);
void	sh_print_lr_table(t_lr_parser *parser);
void	sh_print_automata(t_lr_parser *parser, int depth);
void	sh_print_parser(t_lr_parser *parser, int depth);
void	sh_print_state(t_state *state, int depth);
void    sh_print_parser_state(t_lr_parser *parser);
void	sh_print_token(t_token *token, t_cfg *cfg);
void	sh_print_production(t_production *production);
void	sh_print_ast_builder(t_ast_builder *ast_builder);
void	sh_print_ast_parser(t_lr_parser *parser);

/*
** lr_parse.c
*/
int		sh_lr_parse(t_lr_parser *parser);

/*
** compute_lr_automata.c
*/
int     sh_compute_lr_automata(t_lr_parser *parser);
t_state	*sh_compute_first_state(t_lr_parser *parser);
int		sh_compute_closure(t_state *state, t_lr_parser *parser);
int		sh_compute_transitions(t_state *state, t_lr_parser *parser);

/*
** state.c
*/
t_state		*sh_new_state(void);
void		sh_free_state(t_state *state);
t_item		*sh_new_item(t_production *production, char lookaheads[NB_TERMS]);

/*
** compute_lr_tables.c
*/
int     sh_compute_lr_tables(t_lr_parser *parser);

/*
** init_cfg.c
*/
int		init_context_free_grammar(t_cfg *cfg);


int		init_parsing(t_lr_parser *parser);

/*
** traverse.c
*/
int		sh_traverse(t_ast_node *node);

int     sh_add_prod(t_symbol *symbol, t_cfg *cfg,
			int nb_symbols, ...);

t_cfg		*g_cfg;

int		sh_index(t_symbol_id id);

int		sh_init_prod_program(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_complete_commands(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_complete_command(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_list(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_and_or(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_pipeline(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_pipe_sequence(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_command(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_compound_command(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_subshell(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_compound_list(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_term(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_for_clause(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_name(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_in(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_wordlist(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_case_clause(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_case_list_ns(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_case_list(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_case_item_ns(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_case_item(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_pattern(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_if_clause(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_else_part(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_while_clause(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_until_clause(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_function_definition(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_function_body(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_fname(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_brace_group(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_do_group(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_simple_command(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_cmd_name(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_cmd_word(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_cmd_prefix(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_cmd_suffix(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_redirect_list(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_io_redirect(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_io_file(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_filename(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_io_here(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_here_end(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_newline_list(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_linebreak(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_separator_op(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_separator(t_cfg *cfg, t_symbol *symbol);
int		sh_init_prod_sequential_sep(t_cfg *cfg, t_symbol *symbol);
#endif
