/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:19:27 by nkhamich          #+#    #+#             */
/*   Updated: 2025/02/09 10:50:19 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*split_at_operator(t_token *start, t_token *end, int *status)
{
	t_token		*main_operator;
	t_ast_node	*node;

	main_operator = get_main_operator(start, end);
	node = create_ast_node(get_node_type(main_operator->type));
	if (node == NULL)
	{
		*status = PARSER_CRITICAL_ERROR;
		return (NULL);
	}
	node->left = build_ast(start, main_operator, status);
	node->right = build_ast(main_operator->next, end, status);
	return (node);
}

t_ast_node	*split_at_separator(t_token *start, t_token *end, int *status)
{
	t_token		*separator;
	t_ast_node	*node;

	separator = get_separator(start, end);
	node = create_ast_node(NODE_SEQUENCE);
	if (node == NULL)
	{
		*status = PARSER_CRITICAL_ERROR;
		return (NULL);
	}
	node->left = build_ast(start, separator, status);
	node->right = build_ast(separator->next, end, status);
	return (node);
}

t_ast_node	*build_ast(t_token *start, t_token *end, int *status)
{
	if (get_separator(start, end))
		return (split_at_separator(start, end, status));
	else if (get_main_operator(start, end))
		return (split_at_operator(start, end, status));
	else if (contains_group(start, end))
		return (process_group(start, end, status));
	else
		return (process_command(start, end, status));
}
