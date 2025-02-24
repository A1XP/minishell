/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:19:47 by natallia          #+#    #+#             */
/*   Updated: 2025/02/03 12:41:13 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_readline(t_mshell *mshell)
{
	rl_on_new_line();
	mshell->input = readline(mshell->prompt);
	if (!mshell->input)
		return (MINISHELL_CLEANUP);
	add_history(mshell->input);
	return (MINISHELL_LEXER);
}
