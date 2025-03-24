/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:51:48 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/07 17:29:07 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ignore_sigint(int sig)
{
	(void)sig;
	g_exit_code = 130;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ignore_ctrl_c(void)
{
	struct sigaction	sa;

	sa.sa_handler = ignore_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

// void ignore_sigquit(void)
// {
// 	struct sigaction sa;

// 	sa.sa_handler = SIG_IGN;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sigaction(SIGQUIT, &sa, NULL);
// 	// signal(SIGQUIT, SIG_IGN);
// }
