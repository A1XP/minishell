/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:49:06 by natallia          #+#    #+#             */
/*   Updated: 2025/02/04 12:09:35 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_envp_copy(char **envp)
{
	int		i;
	int		count;
	char	**envp_copy;

	count = 0;
	while (envp[count])
		count++;
	envp_copy = malloc((count + 1) * sizeof(char *));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
		{
			free_envp_copy(envp_copy);
			return (NULL);
		}
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

void	free_envp_copy(char **envp_copy)
{
	int		i;

	if (!envp_copy)
		return ;
	i = 0;
	while (envp_copy[i])
	{
		free(envp_copy[i]);
		i++;
	}
	free(envp_copy);
	envp_copy = NULL;
}
