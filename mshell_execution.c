/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:02:50 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/18 17:07:00 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_execution(t_mshell *mshell)
{
	g_exit_code = ft_execution(&mshell->exec, mshell->ast);
	free_ast(&mshell->ast);
	if (mshell->exec.isexit)
		return (MINISHELL_CLEANUP);
	return (MINISHELL_READLINE);
}
