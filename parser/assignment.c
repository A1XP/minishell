/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:57:03 by natallia          #+#    #+#             */
/*   Updated: 2025/02/09 15:24:34 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_valid_assignment(t_token *token)
{
	int		i;
	char	*name;

	i = 0;
	name = token->value;
	if (token->type == WORD && (token->next && token->next->type == ASSIGN))
	{
		if (ft_isalpha(name[i]) || name[i] == '_')
		{
			i++;
			while (name[i])
			{
				if (!(ft_isalnum(name[i]) || name[i] == '_'))
					return (false);
				i++;
			}
			return (true);
		}
	}
	return (false);
}

bool	is_valid_value(t_token *token)
{
	if (!token->next)
		return (false);
	if (token->next->type == WORD
		|| token->next->type == STR_DOUBLE_Q
		|| token->next->type == STR_SINGLE_Q
		|| token->next->type == COMMENT
		|| token->next->type == ASSIGN)
		return (true);
	else
		return (false);
}

bool	is_permanent_assign(t_token *token, t_token *last)
{
	token = token->next;
	if (!token || token->next == NULL || token->next->type == SEMICOLON
		|| token->next->type == NEWLINE)
		return (true);
	while (token != last)
	{
		if (token->type == SPACE)
			;
		else if (is_valid_assignment(token))
		{
			token = token->next;
			if (is_valid_assignment(token))
				token = token->next;
		}
		else if (token->type == REDIR_IN || token->type == REDIR_OUT)
			;
		else
			return (false);
		token = token->next;
	}
	return (true);
}

char	*append_value(t_token **token, char *new_assign)
{
	if (!is_valid_value(*token))
		return (ft_strjoin_free(new_assign, "\"\""));
	while (is_valid_value(*token))
	{
		new_assign = ft_strjoin_free(new_assign, (*token)->next->value);
		if (new_assign == NULL)
			return (NULL);
		(*token) = (*token)->next;
	}
	return (new_assign);
}

int	add_assignment(t_ast_node *node, t_token **token, t_token *end)
{
	char	*new_assign;
	t_list	*new_assign_lst;

	new_assign = ft_strjoin((*token)->value, (*token)->next->value);
	if (new_assign == NULL)
		return (PARSER_CRITICAL_ERROR);
	(*token) = (*token)->next;
	new_assign = append_value(token, new_assign);
	if (new_assign == NULL)
		return (PARSER_CRITICAL_ERROR);
	new_assign_lst = ft_lstnew(new_assign);
	if (new_assign_lst == NULL)
	{
		free(new_assign);
		return (PARSER_CRITICAL_ERROR);
	}
	if (is_permanent_assign(*token, end))
		ft_lstadd_back(&node->cmd->perm_assignments, new_assign_lst);
	else
		ft_lstadd_back(&node->cmd->temp_assignments, new_assign_lst);
	return (PARSER_DEFAULT);
}
