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

static void	fn_write_heredoc(char *limeter, int fd)
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

static int	fn_create_heredoc(char *limeter)
{
	int		fd;

	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc");
		exit(EXIT_FAILURE);
	}
	fn_write_heredoc(limeter, fd);
	close(fd);
	return (open("heredoc", O_RDONLY));
}

int	ft_redirection_heredoc(t_executer *exec, t_ast_node *node)
{
	close(exec->in_fd);
	exec->in_fd = fn_create_heredoc(node->cmd->redirects->filename);
	return (exec->status);
}