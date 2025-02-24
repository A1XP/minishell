/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:04:54 by nkhamich          #+#    #+#             */
/*   Updated: 2025/02/10 14:23:47 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*skip_open_paren(t_token *token, t_token *last)
{
	while (token != last)
	{
		if (token->type == PAREN_OPEN)
			break ;
		token = token->next;
	}
	return (token->next);
}

t_token	*get_close_paren(t_token *token, t_token *end)
{
	int		balance;

	balance = 0;
	while (token != end)
	{
		if (token->type == PAREN_OPEN)
			balance++;
		if (token->type == PAREN_CLOSE)
		{
			balance--;
			if (balance == 0)
				break ;
		}
		token = token->next;
	}
	return (token);
}
