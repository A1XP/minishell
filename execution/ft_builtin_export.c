/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:22:41 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/17 16:33:41 by pkhvorov         ###   ########.fr       */
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

char	**reallocate_env_nodes(char **env, int count)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(count + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i] && i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		free_ptr(env[i]);
		i++;
	}
	free(env);
	return (new_env);
}

int	set_var_value(char ***env, char *var, char *value)
{
	char	*new_value;
	int		index;
	char	**new_env;
	
	if (value == NULL)
		value = ft_calloc(1, sizeof(char));
	new_value = ft_strjoin("=", value);
	if (new_value == NULL)
		return (EXIT_FAILURE);
	index = get_env_index(*env, var);
	if (index != -1 && (*env)[index] != NULL)
	{
		// printf("INDEX %d\n", index);
		free((*env)[index]);
		(*env)[index] = ft_strjoin(var, new_value);
		// printf("KEY=VALUE in if: %s\n", *env[index]);
	}
	else
	{
		index = env_count(*env);
		new_env = reallocate_env_nodes(*env, index + 1);
		if (new_env == NULL)
		{
			free_ptr(new_value);
			return (EXIT_FAILURE);
		}
		*env = new_env;
		(*env)[index] = ft_strjoin(var, new_value);
		// printf("KEY=VALUE in else: %s\n", (*env)[index]);
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
	ft_exec_clean(exec);
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
			set_var_value(&exec->env, temp[0], temp[1]);
			free_double_array(temp);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
