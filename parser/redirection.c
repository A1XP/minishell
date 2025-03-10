/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:51:41 by natallia          #+#    #+#             */
/*   Updated: 2025/02/25 12:35:58 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_valid_redirection(t_token *token, int *status)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == HEREDOC || token->type == APPEND)
	{
		if (token->next && token->next->type == SPACE)
			token = token->next;
		if (token-> next && (token->next->type == WORD
				|| token->next->type == STR_SINGLE_Q
				|| token->next->type == STR_DOUBLE_Q))
			return (true);
		else
		{
			*status = PARSER_ERROR;
			if (token->next)
				ft_printf("minishell: syntax error near unexpected token"
					" '%s'\n", token->next->value);
			else
				ft_printf("minishell: syntax error near unexpected token"
					" 'newline'\n");
			return (false);
		}
	}
	return (false);
}

int	add_redirection(t_ast_node *node, t_token **token, bool group)
{
	t_redirect	*new_redir;

	new_redir = malloc(sizeof(t_redirect));
	if (!new_redir)
		return (PARSER_CRITICAL_ERROR);
	new_redir->redir_type = (*token)->type;
	if ((*token)->next->type == SPACE)
		(*token) = (*token)->next;
	new_redir->filename = ft_strdup((*token)->next->value);
	if (new_redir->filename == NULL)
		return (free(new_redir), PARSER_CRITICAL_ERROR);
	if (group == false)
	{
		new_redir->next = node->cmd->redirects;
		node->cmd->redirects = new_redir;
	}
	else
	{
		new_redir->next = node->group_redirs;
		node->group_redirs = new_redir;
	}
	*token = (*token)->next;
	return (PARSER_DEFAULT);
}
