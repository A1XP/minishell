/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:31:33 by natallia          #+#    #+#             */
/*   Updated: 2025/02/10 14:23:09 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->value = NULL;
	new->next = NULL;
	if (value == NULL)
		return (new);
	new->value = ft_strdup(value);
	if (new->value == NULL)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

t_token	*get_last_token(t_token *token_lst)
{
	while (token_lst != NULL && token_lst->next != NULL)
		token_lst = token_lst->next;
	return (token_lst);
}

void	append_token(t_token **token_lst, t_token *new)
{
	t_token	*last;

	last = NULL;
	if (*token_lst == NULL)
		*token_lst = new;
	else
	{
		last = get_last_token(*token_lst);
		last->next = new;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token		*current;
	t_token		*next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}
