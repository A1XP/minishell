/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:34:07 by nkhamich          #+#    #+#             */
/*   Updated: 2025/02/03 16:04:11 by nkhamich         ###   ########.fr       */
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
	return (MINISHELL_EXIT);
}
