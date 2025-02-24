/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:41:27 by nkhamich          #+#    #+#             */
/*   Updated: 2025/02/12 13:38:18 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_minishell_init(t_mshell *data, char **env)
// {
// 	init_env(&data->exec, env);
// 	set_bin_paths(&data->exec, env);
// 	ft_exec_init(&data->exec);
//     init_wds(&data->exec);
//     return (0);
// }

t_mshell_phase	mshell_start(t_mshell *mshell, char **envp)
{
	//execution
	mshell->exec.env = get_envp_copy(envp);
	if (mshell->exec.env == NULL)
		return (MINISHELL_CLEANUP);
	set_bin_paths(&mshell->exec, envp);
	ft_exec_init(&mshell->exec);
	//common
	mshell->input = NULL;
	mshell->envp_copy = get_envp_copy(envp);
	if (mshell->envp_copy == NULL)
		return (MINISHELL_CLEANUP);
	mshell->tokens = NULL;
	mshell->ast = NULL;
	mshell->prompt = "minishell> ";
	return (MINISHELL_READLINE);
}
