/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:47:55 by nkhamich          #+#    #+#             */
/*   Updated: 2025/02/25 14:54:58 by nkhamich         ###   ########.fr       */
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

static bool	check_for_strays(t_token *token, t_token *last, t_ast_node *node)
{
	int	balance;
	int	last_paren;
	int	status;

	balance = 0;
	last_paren = 0;
	status = PARSER_DEFAULT;
	while (token != last)
	{
		if (balance == 0 || last_paren == 1)
		{
			if (is_valid_redirection(token, &status))
			{
				if (!last_paren)
				{
					ft_printf("minishell: syntax error near unexpected token");
					ft_printf(" '('\n");
					return (PARSER_ERROR);
				}
				status = add_redirection(node, &token, true);
				token = token->next;
				if (token == last)
					break ;
			}
			if (!status && token && token->type != SPACE
				&& token->type != PAREN_OPEN)
			{
				ft_printf("minishell: syntax error near unexpected token ");
				ft_printf("'%s'\n", token->value);
				return (status);
			}
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
	return (status);
}

t_ast_node	*process_group(t_token *start, t_token *end, int *status)
{
	t_token		*group_start;
	t_token		*group_end;
	t_ast_node	*node;

	node = create_ast_node(NODE_GROUP);
	if (node == NULL)
	{
		*status = PARSER_CRITICAL_ERROR;
		return (NULL);
	}
	*status = check_for_strays(start, end, node);
	if (*status != PARSER_DEFAULT)
		return (NULL);
	group_start = skip_open_paren(start, end);
	group_end = get_close_paren(start, end);
	node->subtree = build_ast(group_start, group_end, status);
	return (node);
}
