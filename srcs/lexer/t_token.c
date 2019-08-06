/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:29:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/31 19:03:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** t_token_update_id:
**	Update a token id by changing it's id, and looking for it's new index.
*/

void	t_token_update_id(int id, t_token *token)
{
	token->id = id;
	token->index = sh_index(id);
}

t_token *sh_new_token(int id, char *value)
{
	t_token		*token;

	if (!(token = malloc(sizeof(*token))))
		return (NULL);
	token->value = NULL;
	if (value)
	{
		if (!(token->value = ft_strdup(value)))
		{
			free(token);
			return (NULL);
		}
	}
	token->id = id;
	token->index = sh_index(id);
	token->token_type = TYPE_STR;
	token->quoted = 0;
	token->expansion = 0;
	return (token);
}

/*
** t_token_new:
**	Malloc a new t_token struct, and initialize all fields.
*/

t_list	*t_token_new(int id, char *value)
{
	t_list		*link;
	t_token		*token;

	if (!(token = sh_new_token(id, value)))
		return (NULL);
	if (!(link = ft_lstnew(token, sizeof(token))))
	{
		t_token_free(token);
		return (NULL);
	}
	return (link);
}

/*
** t_token_free:
**	Free a t_token and it's value, if it had been filled.
*/

void	t_token_free(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}

/*
** t_token_free:
**	Free a t_token encpsuled in a t_list.
*/

void	t_token_free_list(t_list *head)
{
	t_list	*buf;

	while (head)
	{
		buf = head;
		head = head->next;
		t_token_free(buf->content);
		free(buf);
	}
}

/*
** sh_free_token_lst:
**		Function added to be used with ft_lst_del.
*/

void	sh_free_token_lst(void *t, size_t dummy)
{
	(void)dummy;
	t_token_free((t_token *)t);
}
