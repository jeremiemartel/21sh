/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:29:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/15 14:23:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	t_token_update_id(int id, t_token *token)
{
	token->id = id;
	token->index = sh_index(id);
}

t_token	*t_token_new(int id, char *value)
{
	t_token		*token;

	if (!(token = malloc(sizeof(*token))))
		return (NULL);
	token->id = id;
	token->index = sh_index(id);
	token->token_type= TYPE_STR;
//	ft_printf("%d => %d\n", id, token->index);
	if (!(value))
		ft_bzero(token->value, LEX_TOKEN_VALUE_LEN);
	return (token);
}

void	t_token_show(t_token *token)
{
	t_token_show_id(token->id);
	ft_printf(":%s", token->value);
}

void	t_token_show_id(int i)
{
	switch (i)
	{
		case (LEX_TOK_UNKNOWN):
		{
			ft_putstr(COLOR_RED"UNKNOWN"COLOR_END);
			break ;
		}
		case (LEX_TOK_PIPE):
		{
			ft_putstr("PIPE");
			break ;
		}
		case (LEX_TOK_AND):
		{
			ft_putstr("AND");
			break ;
		}
		case (LEX_TOK_SEMICOL):
		{
			ft_putstr("SEMICOL");
			break ;
		}
		case (LEX_TOK_LESS):
		{
			ft_putstr("LESS");
			break ;
		}
		case (LEX_TOK_GREAT):
		{
			ft_putstr("GREAT");
			break ;
		}
		case (LEX_TOK_OPN_PAR):
		{
			ft_putstr("OPN_PAR");
			break ;
		}
		case (LEX_TOK_CLS_PAR):
		{
			ft_putstr("CLS_PAR");
			break ;
		}
		case (LEX_TOK_DOLLAR):
		{
			ft_putstr("DOLLAR");
			break ;
		}
		case (LEX_TOK_BACK_SLASH):
		{
			ft_putstr("BACK_SLASH");
			break ;
		}
		case (LEX_TOK_QUOTE_BACK):
		{
			ft_putstr("QUOTE_BACK");
			break ;
		}
		case (LEX_TOK_QUOTE_SPL):
		{
			ft_putstr("QUOTE_SPL");
			break ;
		}
		case (LEX_TOK_QUOTE_DBL):
		{
			ft_putstr("QUOTE_DBL");
			break ;
		}
		case (LEX_TOK_SPACE):
		{
			ft_putstr("SPACE");
			break ;
		}
		case (LEX_TOK_TAB):
		{
			ft_putstr("");
			break ;
		}
		case (LEX_TOK_NEWLINE):
		{
			ft_putstr("NEWLINE");
			break ;
		}
		case (LEX_TOK_STAR):
		{
			ft_putstr("STAR");
			break ;
		}
		case (LEX_TOK_QUEST):
		{
			ft_putstr("QUEST");
			break ;
		}
		case (LEX_TOK_HASH):
		{
			ft_putstr("HASH");
			break ;
		}
		case (LEX_TOK_TILD):
		{
			ft_putstr("TILD");
			break ;
		}
		case (LEX_TOK_EQUAL):
		{
			ft_putstr("EQUAL");
			break ;
		}
		case (LEX_TOK_PERCENT):
		{
			ft_putstr("PERCENT");
			break ;
		}
		case (LEX_TOK_AND_IF):
		{
			ft_putstr("AND_IF");
			break ;
		}
		case (LEX_TOK_OR_IF):
		{
			ft_putstr("OR_IF");
			break ;
		}
		case (LEX_TOK_DSEMI):
		{
			ft_putstr("DSEMI");
			break ;
		}
		case (LEX_TOK_DLESS):
		{
			ft_putstr("DLESS");
			break ;
		}
		case (LEX_TOK_DGREAT):
		{
			ft_putstr("DGREAT");
			break ;
		}
		case (LEX_TOK_LESSAND):
		{
			ft_putstr("LESSAND");
			break ;
		}
		case (LEX_TOK_GREATAND):
		{
			ft_putstr("GREATAND");
			break ;
		}
		case (LEX_TOK_LESSGREAT):
		{
			ft_putstr("LESSGREAT");
			break ;
		}
		case (LEX_TOK_DLESSDASH):
		{
			ft_putstr("DLESSDASH");
			break ;
		}
		case (LEX_TOK_CLOBBER):
		{
			ft_putstr("CLOBBER");
			break ;
		}
		case (LEX_TOK_WORD):
		{
			ft_putstr("WORD");
			break ;
		}
		case (LEX_TOK_TOKEN):
		{
			ft_putstr("TOKEN");
			break ;
		}
		case (LEX_TOK_IO_NUMBER):
		{
			ft_putstr("IO_NUMBER");
			break ;
		}
		default:
			ft_printf(COLOR_RED"Undefined Token (%d)"COLOR_END, i);
	}
}
