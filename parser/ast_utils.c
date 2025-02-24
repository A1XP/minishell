/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:54:42 by natallia          #+#    #+#             */
/*   Updated: 2025/02/09 11:18:55 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*get_main_operator(t_token *token, t_token *end)
{
	t_token		*op;

	op = NULL;
	while (token != end)
	{
		if (token->type == PAREN_OPEN)
			token = get_close_paren(token, end);
		else if (token->type == PIPE)
			op = token;
		else if (token->type == OR && (op == NULL || op->type != PIPE))
			op = token;
		else if (token->type == AND && (op == NULL || op->type != PIPE))
			op = token;
		token = token->next;
	}
	return (op);
}

t_token	*get_separator(t_token *token, t_token *end)
{
	t_token		*sep;

	sep = NULL;
	while (token != end)
	{
		if (token->type == NEWLINE || token->type == SEMICOLON)
		{
			sep = token;
			break ;
		}
		token = token->next;
	}
	return (sep);
}

t_node_type	get_node_type(t_token_type token_type)
{
	if (token_type == AND)
		return (NODE_AND);
	else if (token_type == OR)
		return (NODE_OR);
	else
		return (NODE_PIPE);
}

static t_command	*new_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->cmd_name = NULL;
	command->args = NULL;
	command->temp_assignments = NULL;
	command->perm_assignments = NULL;
	command->redirects = NULL;
	return (command);
}

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(t_ast_node));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->subtree = NULL;
	new_node->cmd = NULL;
	if (type == NODE_COMMAND)
	{
		new_node->cmd = new_command();
		if (new_node->cmd == NULL)
		{
			free(new_node);
			return (NULL);
		}
	}
	return (new_node);
}
