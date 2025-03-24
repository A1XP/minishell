/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:23:03 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/20 17:25:07 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <readline/readline.h>

static void	ft_write_heredoc(char *limeter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc > ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, limeter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static int	ft_create_heredoc(t_ast_node *node)
{
	int			fd;
	t_redirect	*heredocs;
	t_redirect	*temp;

	heredocs = NULL;
	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc");
		exit(EXIT_FAILURE);
	}
	while (node->cmd->redirects)
	{
		if (node->cmd->redirects->redir_type == HEREDOC)
		{
			temp = malloc(sizeof(t_redirect));
			if (temp == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			*temp = *node->cmd->redirects;
			temp->next = heredocs;
			heredocs = temp;
		}
		node->cmd->redirects = node->cmd->redirects->next;
	}
	while (heredocs)
	{
		ft_write_heredoc(heredocs->filename, fd);
		temp = heredocs;
		heredocs = heredocs->next;
		free(temp);
	}
	close(fd);
	return (open("heredoc", O_RDONLY));
}

int	ft_redirection_heredoc(t_executer *exec, t_ast_node *node)
{
	close(exec->in_fd);
	exec->in_fd = ft_create_heredoc(node);
	return (exec->status);
}

// int	ft_redirection_heredoc(t_executer *exec, t_ast_node *node)
// {
// 	close(exec->in_fd);
// 	while (node->cmd->redirects)
// 	{
// 		if (node->cmd->redirects->redir_type == HEREDOC)
// 		{
// 			exec->in_fd = ft_create_heredoc(node->cmd->redirects->filename);
// 		}
// 		node->cmd->redirects = node->cmd->redirects->next;
// 	}
// 	return (exec->status);
// }
