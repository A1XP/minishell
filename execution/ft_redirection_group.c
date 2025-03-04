/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_group.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:13:19 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/03 13:56:40 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void ft_redirection_out_files(t_redirect *redirects)
{
	int	fd_out;
	
	while (redirects)
	{
		if (redirects->redir_type == REDIR_OUT)
			{
				fd_out = open(redirects->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				close(fd_out);
			}
		else if (redirects->redir_type == APPEND)
			{
				fd_out = open(redirects->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				close(fd_out);
			}
		redirects = redirects->next;
	}
}

static int	ft_redirection_out(t_executer *exec, t_ast_node *node)
{
	int	fd_out;
	
	fd_out = open(node->group_redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(exec->out_fd);
	exec->out_fd = fd_out;
	if (node->group_redirs->next != NULL)
		ft_redirection_out_files(node->group_redirs->next);
	return (exec->status);
}

static int	ft_redirection_append(t_executer *exec, t_ast_node *node)
{
	int	fd_out;
	
	fd_out = open(node->group_redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	close(exec->out_fd);
	exec->out_fd = fd_out;
	if (node->group_redirs->next != NULL)
		ft_redirection_out_files(node->group_redirs->next);
	return (exec->status);
}

static int	ft_redirection_in(t_executer *exec, t_ast_node *node)
{
	int	fd_in;

	fd_in = open(node->group_redirs->filename, O_RDONLY);
	close(exec->in_fd);
	exec->in_fd = fd_in;
	return (exec->status);
}

int ft_redirection_group(t_executer *exec, t_ast_node *node)
{
	if (node->group_redirs->redir_type == REDIR_OUT)
		ft_redirection_out(exec, node);
	if (node->group_redirs->redir_type == APPEND)
		ft_redirection_append(exec, node);
	if (node->group_redirs->redir_type == REDIR_IN)
		ft_redirection_in(exec, node);
	if (node->group_redirs->redir_type == HEREDOC)
		ft_redirection_heredoc(exec, node);
	return (exec->status);
}
