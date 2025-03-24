/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:34:07 by nkhamich          #+#    #+#             */
/*   Updated: 2025/03/18 17:31:27 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_cleanup(t_mshell *mshell)
{
	if (mshell->input)
		free(mshell->input);
	if (mshell->envp_copy)
		free_envp_copy(mshell->envp_copy);
	if (mshell->tokens)
		free_tokens(&mshell->tokens);
	if (mshell->ast)
		free_ast(&mshell->ast);
	ft_exec_clean(&mshell->exec);
	return (MINISHELL_EXIT);
}
