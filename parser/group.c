/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:47:55 by nkhamich          #+#    #+#             */
/*   Updated: 2025/02/09 10:49:11 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	contains_group(t_token *token, t_token *end)
{
	while (token != end)
	{
		if (token->type == PAREN_OPEN)
			return (true);
		token = token->next;
	}
	return (false);
}

static bool	contains_stray_tokens(t_token *token, t_token *last)
{
	int		balance;
	int		last_paren;

	balance = 0;
	last_paren = 0;
	while (token != last)
	{
		if ((balance == 0 || last_paren == 1)
			&& token->type != SPACE && token->type != PAREN_OPEN)
		{
			ft_printf("minishell: syntax error near unexpected token ");
			ft_printf("'%s'\n", token->value);
			return (true);
		}
		if (token->type == PAREN_OPEN)
			balance++;
		else if (token->type == PAREN_CLOSE)
		{
			balance--;
			if (balance == 0)
				last_paren = 1;
		}
		token = token->next;
	}
	return (false);
}

t_ast_node	*process_group(t_token *start, t_token *end, int *status)
{
	t_token		*group_start;
	t_token		*group_end;
	t_ast_node	*node;

	if (contains_stray_tokens(start, end))
		return (NULL);
	group_start = skip_open_paren(start, end);
	group_end = get_close_paren(start, end);
	node = create_ast_node(NODE_GROUP);
	if (node == NULL)
	{
		*status = PARSER_CRITICAL_ERROR;
		return (NULL);
	}
	node->subtree = build_ast(group_start, group_end, status);
	return (node);
}
