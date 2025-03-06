/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:22:41 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/05 16:47:27 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_isalnumunder(int i)
{
	if (('a' <= i && i <= 'z') || ('A' <= i && i <= 'Z') \
		|| ('0' <= i && i <= '9') || i == '_')
		return (0);
	return (1);
}

int	check_var(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
	{
		if (ft_isalnumunder(var[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	**var_value_pair(char *arg)
{
	char	**temp;
	char	*pos;

	pos = ft_strchr(arg, '=');
	temp = malloc(3 * sizeof(char *));
	temp[0] = ft_substr(arg, 0, pos - arg);
	temp[1] = ft_substr(pos, 1, ft_strlen(pos));
	temp[2] = NULL;
	return (temp);
}

char	**reallocate_env_nodes(t_executer *exec, int count)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(count + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (exec->env[i] && i < count)
	{
		new_env[i] = ft_strdup(exec->env[i]);
		free_ptr(exec->env[i]);
		i++;
	}
	free(exec->env);
	return (new_env);
}

int	set_var_value(t_executer *exec, char *var, char *value)
{
	char	*new_value;
	int		index;

	if (value == NULL)
		value = "";
	new_value = ft_strjoin("=", value);
	// printf("=VALUE: %s\n", value);
	if (new_value == NULL)
		return (EXIT_FAILURE);
	index = get_env_index(exec->env, var);
	if (index != -1 && exec->env[index] != NULL)
	{
		free_ptr(exec->env[index]);
		exec->env[index] = ft_strjoin(var, new_value);
		// printf("KEY=VALUE in if: %s\n", exec->env[index]);
	}
	else
	{
		index = env_count(exec->env);
		exec->env = reallocate_env_nodes(exec, index + 1);
		if (exec->env == NULL)
			return (EXIT_FAILURE);
		exec->env[index] = ft_strjoin(var, new_value);
		// printf("KEY=VALUE in else: %s\n", exec->env[index]);
		// exec->env[index + 1] = NULL;
		// printf("KEY=VALUE in else + 1: %s\n", exec->env[index + 1]);
	}
	free_ptr(new_value);
	return (EXIT_SUCCESS);
}

static	int	export_print(t_executer *exec)
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
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(exec->env[i], STDOUT_FILENO);
		i++;
	}
	exit (EXIT_SUCCESS);
}

static	int	ft_export_print(t_executer *exec)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		export_print(exec);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	ft_builtin_export(t_executer *exec, char **args)
{
	int		i;
	char	**temp;

	// printf("0 %s\n", args[0]);
	// printf("1 %s\n", args[1]);
	// printf("2 %s\n", args[2]);
	// printf("= %s\n", ft_strchr(args[1], '='));
	if (args[1] == NULL)
		return (ft_export_print(exec));
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') == NULL || check_var(args[i]) == 1)
		{
			ft_putstr_fd("-minishell: export `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		else
		{
			temp = var_value_pair(args[i]);
			if (temp == NULL)
				return (EXIT_FAILURE);
			set_var_value(exec, temp[0], temp[1]);
			free_double_array(temp);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
