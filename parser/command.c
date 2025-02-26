/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:40:48 by nkhamich          #+#    #+#             */
/*   Updated: 2025/02/25 09:47:57 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_command_name(t_ast_node *node, t_token *token)
{
	node->cmd->cmd_name = ft_strdup(token->value);
	if (node->cmd->cmd_name == NULL)
		return (PARSER_CRITICAL_ERROR);
	add_argument(node->cmd, token->value);
	if (node->cmd->args == NULL)
		return (PARSER_CRITICAL_ERROR);
	return (PARSER_DEFAULT);
}

t_ast_node	*process_command(t_token *token, t_token *end, int *status)
{
	t_ast_node	*node;

	node = create_ast_node(NODE_COMMAND);
	if (node == NULL)
	{
		*status = PARSER_CRITICAL_ERROR;
		return (NULL);
	}
	while (token != end && *status == PARSER_DEFAULT)
	{
		if (token->type == SPACE)
			;
		else if (is_valid_assignment(token))
			*status = add_assignment(node, &token, end);
		else if (is_valid_redirection(token, status) && !(*status))
			*status = add_redirection(node, &token, false);
		else if (node->cmd->cmd_name == NULL && !(*status))
			*status = add_command_name(node, token);
		else if (!(*status))
			*status = add_argument(node->cmd, token->value);
		token = token->next;
	}
	return (node);
}
