/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:02:50 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/18 17:08:16 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	ft_left_child(int *pipefd, t_executer *exec, t_ast_node *node)
{
	close(pipefd[0]);
	close(exec->out_fd);
	exec->out_fd = pipefd[1];
	exec->status = ft_exec_recursive(exec, node->left);
	if (exec->in_fd >= 0)
	{
		close(exec->in_fd);
		exec->in_fd = -1;
	}
	if (exec->out_fd >= 0)
	{
		close(exec->out_fd);
		exec->out_fd = -1;
	}
	ft_exec_clean(exec);
	exit(exec->status);
}

static void	ft_right_child(int *pipefd, t_executer *exec, t_ast_node *node)
{
	close(pipefd[1]);
	close(exec->in_fd);
	exec->in_fd = pipefd[0];
	exec->status = ft_exec_recursive(exec, node->right);
	if (exec->in_fd >= 0)
	{
		close(exec->in_fd);
		exec->in_fd = -1;
	}
	if (exec->out_fd >= 0)
	{
		close(exec->out_fd);
		exec->out_fd = -1;
	}
	ft_exec_clean(exec);
	exit(exec->status);
}

int	ft_exec_pipe(t_executer *exec, t_ast_node *node)
{
	pid_t	pid[2];
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (-1);
	if (pid[0] == 0)
		ft_left_child(pipefd, exec, node);
	pid[1] = fork();
	if (pid[1] == -1)
		return (-1);
	if (pid[1] == 0)
		ft_right_child(pipefd, exec, node);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
