/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:55:08 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/25 15:59:10 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int env_print(t_executer *exec)
{
	int	i;
	
	dup2(exec->in_fd, STDIN_FILENO);
	dup2(exec->out_fd, STDOUT_FILENO);
	close(exec->in_fd);
	close(exec->out_fd);
	i = 0;
	if (exec->env == NULL)
		return (EXIT_FAILURE);
	while (exec->env[i] != NULL)
	{
		ft_putendl_fd(exec->env[i], STDOUT_FILENO);
		i++;		
	}
	exit (EXIT_SUCCESS);
}

int ft_builtin_env(t_executer *exec)
{
	pid_t		pid;
	int			status;
	
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		env_print(exec);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}