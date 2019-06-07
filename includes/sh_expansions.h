/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   sh_expansions.h									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jmartel <jmartel@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/06/05 11:55:55 by jmartel		   #+#	#+#			 */
/*   Updated: 2019/06/05 14:24:12 by jmartel		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef SH_EXPANSIONS_H
# define SH_EXPANSIONS_H

/*
** Expansion header
*/
typedef enum		e_exp_type
{
	EXP_VAR = 1,
	EXP_PARAM,
	EXP_CMD,
	EXP_ARITH,
	EXP_TILDE,
}					t_exp_type;

typedef struct s_expansion	t_expansion;

struct				s_expansion
{
	t_dy_str			*res;
	char			*original;
	char			*expansion;
	t_exp_type		type;
	int				(*process)(t_context *, t_expansion *);
};

/*
**sh_expansions_parameter.c
*/
int			sh_expansions_parameter_detect(char *start);
int			sh_expansions_parameter_fill(t_expansion *exp, char *start);
int			sh_expansions_parameter_process(t_context *context, t_expansion *exp);

/*
**sh_expansions_init.c
*/
int			sh_expansions_init(char *original, t_expansion *exp);

/*
**sh_expansions.c
*/
int			sh_expansions(t_context *context, t_ast_node *node);
int			sh_expansion_process(char **input, t_context *context);
int			sh_expansion_process_recursive(char **input, char *original, t_context *context);
int			sh_expansions_replace(t_expansion *expansion, char **input);

/*
**sh_expansions_tilde.c
*/
int			sh_expansions_tilde_detect(char *start);
int			sh_expansions_tilde_fill(t_expansion *exp, char *start);
int			sh_expansions_tilde_process(t_context *context, t_expansion *exp);

/*
**sh_expansions_process_parameter.c
*/
int			 sh_expansions_parameter_format(t_expansion *exp, char *format);
char	*sh_expansions_parameter_get_param(t_context *context, t_expansion *exp);
char	*sh_expansions_parameter_get_word(t_context *context, t_expansion *exp, char *format);
int			 sh_expansions_parameter_minus(t_context *context, t_expansion *exp, char *format);
int			 sh_expansions_parameter_equal(t_context *context, t_expansion *exp, char *format);
int			 sh_expansions_parameter_quest(t_context *context, t_expansion *exp, char *format);
int			 sh_expansions_parameter_plus(t_context *context, t_expansion *exp, char *format);
int			 sh_expansions_percent(t_context *context, t_expansion *exp, char *format);
int			 sh_expansions_hash(t_context *context, t_expansion *exp, char *format);

/*
**t_expansion.c
*/
void			t_expansion_free_content(t_expansion *expansion);
void			t_expansion_show(t_expansion *exp);

/*
**sh_expansions_process_tilde.c
*/
int					 sh_expansions_tilde_1(t_context *context, t_expansion *exp);
int					 sh_expansions_tilde_2(t_context *context, t_expansion *exp);

/*
**sh_expansions_variable.c
*/
int			 sh_expansions_variable_detect(char *start);
int			 sh_expansions_variable_fill(t_expansion *exp, char *start);
int			 sh_expansions_variable_process(t_context *context, t_expansion *exp);

#endif