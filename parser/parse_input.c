/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:14:02 by natallia          #+#    #+#             */
/*   Updated: 2025/03/03 12:58:46 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	valid_parentheses(t_token *tokens)
{
	int		balance;

	balance = 0;
	while (tokens != NULL)
	{
		if (tokens->type == PAREN_OPEN)
			balance++;
		else if (tokens->type == PAREN_CLOSE)
		{
			balance--;
			if (balance < 0)
			{
				ft_putendl_fd("minishell: parse error near ')'", 2);
				return (false);
			}
		}
		tokens = tokens->next;
	}
	if (balance != 0)
	{
		ft_putendl_fd("minishell: parse error near '('", 2);
		return (false);
	}
	else
		return (true);
}

void	parse_input(t_token *tokens, t_ast_node **ast, int *status)
{
	if (tokens == NULL)
	{
		*status = PARSER_ERROR;
		return ;
	}
	if (!valid_parentheses(tokens))
	{
		*status = PARSER_ERROR;
		return ;
	}
	*ast = build_ast(tokens, NULL, status);
}
