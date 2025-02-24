/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:19:12 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/11 15:40:48 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	remove_env_var(t_executer *exec, int index)
{
	if (index > env_count(exec->env))
		return (0);
	free_ptr(exec->env[index]);
	while (exec->env[index + 1] != NULL)
	{
		exec->env[index] = ft_strdup(exec->env[index + 1]);
		free_ptr(exec->env[index + 1]);
		index++;
	}
	exec->env = reallocate_env_nodes(exec, index);
	if (exec->env == NULL)
		return (0);
	return (1);
}

int	ft_buildin_unset(t_executer *exec, char **args)
{
	int	i;
	int	index;

	i = 1;
	while (args[i] != NULL)
	{
		if (check_var(args[i]) == 0 || ft_strchr(args[i], '=') != NULL)
			return (0);
		else
		{
			index = get_env_index(exec->env, args[i]);
			if (index != -1)
				remove_env_var(exec, index);
		}
		i++;
	}
	return (1);
}