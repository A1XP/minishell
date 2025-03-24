/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:41:27 by nkhamich          #+#    #+#             */
/*   Updated: 2025/03/18 15:52:36 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_start(t_mshell *mshell, char **envp)
{
	//execution
	// mshell->exec.env = get_envp_copy(envp);
	// if (mshell->exec.env == NULL)
	// 	return (MINISHELL_CLEANUP);
	if (ft_exec_init(&mshell->exec, envp) == EXIT_FAILURE)
		return (MINISHELL_CLEANUP);
	//common
	mshell->input = NULL;
	mshell->envp_copy = NULL;
	// mshell->envp_copy = get_envp_copy(envp); Pavel removed it coze it not in use right now and I am checking leaks
	// if (mshell->envp_copy == NULL)
	// 	return (MINISHELL_CLEANUP);
	mshell->tokens = NULL;
	mshell->ast = NULL;
	mshell->prompt = "minishell> ";
	return (MINISHELL_READLINE);
}
