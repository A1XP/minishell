/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:34:07 by natallia          #+#    #+#             */
/*   Updated: 2025/02/12 13:29:55 by pkhvorov         ###   ########.fr       */
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
		if (phase == MINISHELL_READLINE)
			phase = mshell_readline(&mshell);
		else if (phase == MINISHELL_LEXER)
			phase = mshell_lexer(&mshell);
		else if (phase == MINISHELL_PARSER)
			phase = mshell_parser(&mshell);
		else if (phase == MINISHELL_EXECUTER)
			phase = ft_execution(&mshell.exec, mshell.ast);
	}
	return (g_exit_code);
}
