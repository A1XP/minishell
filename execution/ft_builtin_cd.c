/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:56:04 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/27 17:27:37 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	update_env_wds(t_executer *exec, char *path)
{
	set_var_value(exec, "OLDPWD", get_env_var(exec->env, "PWD"));
	set_var_value(exec, "PWD", path);
	if (exec->old_wd == NULL)
	{
		free_ptr(exec->old_wd);
		exec->old_wd = ft_strdup(exec->wd);
		if (exec->old_wd == NULL)
			return (-1);
	}
	if (exec->wd == NULL)
	{
		free_ptr(exec->wd);
		exec->wd = ft_strdup(path);
		if (exec->wd == NULL)
			return (-1);
	}
	return (0);
}

int change_dir(t_executer *exec, char *path)
{
	char	*cwd;
	char	*buffer;

	buffer = NULL;
	if (chdir(path) != 0)
	{
		ft_putendl_fd("minishell: cd: no such file or directory", 2);
		return (-1);
	}
	if (exec->old_wd != NULL)
		free (exec->old_wd);
	exec->old_wd = ft_strdup(exec->wd);
	if (exec->wd != NULL)
		free (exec->wd);
	cwd = getcwd(buffer, PATH_MAX);
	exec->wd = ft_strdup(cwd);
	printf("change_dir WD: %s\n", exec->wd);
	printf("change_dir OLDWD: %s\n", exec->old_wd);
	update_env_wds(exec, cwd);
	return (0);
}

int ft_builtin_cd(t_executer *exec, char **args)
{
	char	*path;
	int		resault;
	
	path = args[1];

	if (args[1] == NULL || ft_isspace(args[1][0]) != 0 \
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var(exec->env, "HOME");
		if (path == NULL || *path == '\0' || ft_isspace(*path) != 0)
			return (EXIT_FAILURE);
		// change_dir(exec, path);
		// return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var(exec->env, "OLDPWD");
		if (path == NULL || *path == '\0' || ft_isspace(*path) != 0 )
			return (EXIT_FAILURE);
		// change_dir(exec, path);
		// return (EXIT_SUCCESS);
	}
	else if (args[2] != NULL)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (EXIT_FAILURE);	
	}
	resault = change_dir(exec, path);
	if (resault != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
