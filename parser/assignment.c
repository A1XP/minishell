/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:57:03 by natallia          #+#    #+#             */
/*   Updated: 2025/03/18 11:11:17 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_valid_assignment(t_token *token)
{
	int		i;
	char	*name;

	i = 0;
	name = token->value;
	if (token->type == WORD && ft_strchr(token->value, '='))
	{
		if (ft_isalpha(name[i]) || name[i] == '_')
		{
			i++;
			while (name[i] && name[i] != '=')
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

bool	is_permanent_assign(t_token *token, t_token *last)
{
	token = token->next;
	while (token && token != last)
	{
		if (token->type == SPACE)
			;
		else if (is_valid_assignment(token))
			while (token->next && (token->next->type == STR_DOUBLE_Q
				|| token->next->type == STR_SINGLE_Q))
					token = token->next;
		else if (token->type == REDIR_IN || token->type == REDIR_OUT
				|| token->type == APPEND || token->type == HEREDOC)
			;
		else
			return (false);
		token = token->next;
	}
	return (true);
}

int	add_assignment(t_ast_node *node, t_token **token, t_token *end)
{
	char	*new_assign;
	t_list	*new_assign_lst;

	new_assign = ft_strdup((*token)->value);
	if (new_assign == NULL)
		return (PARSER_CRITICAL_ERROR);
	while ((*token)->next && ((*token)->next->type == STR_DOUBLE_Q
		|| (*token)->next->type == STR_SINGLE_Q))
	{
		new_assign = ft_strjoin_free(new_assign, (*token)->next->value);
		(*token) = (*token)->next;
	}
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
