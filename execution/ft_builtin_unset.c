/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:19:12 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/05 16:48:27 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	remove_env_var(t_executer *exec, int index)
{
	if (index > env_count(exec->env))
		return (EXIT_FAILURE);
	free_ptr(exec->env[index]);
	while (exec->env[index + 1] != NULL)
	{
		exec->env[index] = ft_strdup(exec->env[index + 1]);
		free_ptr(exec->env[index + 1]);
		index++;
	}
	exec->env = reallocate_env_nodes(exec, index);
	if (exec->env == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_builtin_unset(t_executer *exec, char **args)
{
	int	i;
	int	index;

	i = 1;
	while (args[i] != NULL)
	{
		if (check_var(args[i]) == 1 || ft_strchr(args[i], '=') != NULL)
			return (EXIT_FAILURE);
		else
		{
			index = get_env_index(exec->env, args[i]);
			if (index != -1)
				remove_env_var(exec, index);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
