/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:29:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/14 19:04:27 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	t_token_update_id(int id, t_token *token)
{
	token->id = id;
	token->index = sh_index(id);
}

t_list	*t_token_new_link(int id, char *value)
{
	t_token		*token;
	t_list		*link;

	if (!(token = malloc(sizeof(*token))))
		return (NULL);
	token->value = NULL;
	if (value)
		if (!(token->value = ft_strdup(value)))
		{
			free(token);
			return (NULL);
		}
	if (!(link = ft_lstnew(token, sizeof(token))))
	{
		free(token);
		return (NULL);
	}
	token->id = id;
	token->index = sh_index(id);
	token->token_type = TYPE_STR;
	token->quoted = 0;
	token->expansion = 0;
	return (link);
}

void	t_token_free(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}

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
