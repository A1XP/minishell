/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:26:28 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/05 16:40:51 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static	int	is_n_key(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] != '\0' && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

static void	echo_print(t_executer *exec, char **args, int n_key, int i)
{
	dup2(exec->in_fd, STDIN_FILENO);
	dup2(exec->out_fd, STDOUT_FILENO);
	close(exec->in_fd);
	close(exec->out_fd);
	if (args[i] == NULL)
	{
		if (n_key == 0)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && n_key == 0)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	exit (EXIT_SUCCESS);
}

int	ft_builtin_echo(t_executer *exec, char **args)
{
	int		i;
	int		n_key;
	pid_t	pid;
	int		status;

	i = 1;
	n_key = 0;
	while (args[i] != NULL && is_n_key(args[i]) == 1)
	{
		n_key = 1;
		i++;
	}
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		echo_print(exec, args, n_key, i);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
