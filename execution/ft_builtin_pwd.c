/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:40:12 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/05 16:48:06 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_builtin_pwd(t_executer *exec)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		dup2(exec->in_fd, STDIN_FILENO);
		dup2(exec->out_fd, STDOUT_FILENO);
		close(exec->in_fd);
		close(exec->out_fd);
		ft_putendl_fd(exec->wd, 1);
		exit (EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
