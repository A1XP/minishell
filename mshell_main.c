/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:34:07 by natallia          #+#    #+#             */
/*   Updated: 2025/03/07 16:47:29 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mshell		mshell;
	t_mshell_phase	phase;

	((void)argc, (void)argv);
	phase = mshell_start(&mshell, envp);
	// ft_minishell_init(&mshell, envp);
	while (phase != MINISHELL_EXIT)
	{
		ignore_ctrl_c();
		// ignore_sigquit();
		if (phase == MINISHELL_READLINE)
			phase = mshell_readline(&mshell);
		else if (phase == MINISHELL_LEXER)
			phase = mshell_lexer(&mshell);
		else if (phase == MINISHELL_PARSER)
			phase = mshell_parser(&mshell);
		else if (phase == MINISHELL_EXECUTER)
			phase = mshell_execution(&mshell);
		else if (phase == MINISHELL_CLEANUP)
			phase = mshell_cleanup(&mshell);
	}
	return (g_exit_code);
}
