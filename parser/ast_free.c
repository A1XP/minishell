/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:40:39 by natallia          #+#    #+#             */
/*   Updated: 2025/02/09 10:54:33 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_args(char ***args)
{
	int		i;

	if (!args || !*args)
		return ;
	i = 0;
	while ((*args)[i])
	{
		free((*args)[i]);
		i++;
	}
	free(*args);
	*args = NULL;
}

static void	free_redirects(t_redirect **redir)
{
	t_redirect	*temp;

	while (*redir)
	{
		temp = (*redir)->next;
		free((*redir)->filename);
		free(*redir);
		*redir = temp;
	}
	*redir = NULL;
}

static void	free_command(t_command **cmd)
{
	if (!cmd || !*cmd)
		return ;
	free((*cmd)->cmd_name);
	free_args(&(*cmd)->args);
	ft_lstclear(&(*cmd)->temp_assignments, free);
	ft_lstclear(&(*cmd)->perm_assignments, free);
	free_redirects(&(*cmd)->redirects);
	free(*cmd);
	*cmd = NULL;
}

void	free_ast(t_ast_node **node)
{
	if (!node || !*node)
		return ;
	free_ast(&(*node)->left);
	free_ast(&(*node)->right);
	free_ast(&(*node)->subtree);
	free_command(&(*node)->cmd);
	free(*node);
	*node = NULL;
}
