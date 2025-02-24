/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:16:05 by natallia          #+#    #+#             */
/*   Updated: 2025/02/17 13:48:19 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_lexer(t_mshell *mshell)
{
	int	status;

	status = LEXER_DEFAULT;
	tokenize_input(mshell->input, &mshell->tokens, &status);
	if (mshell->input)
	{
		free(mshell->input);
		mshell->input = NULL;
	}
	if (status == LEXER_CRITICAL_ERROR)
		return (MINISHELL_CLEANUP);
	if (status == LEXER_ERROR)
	{
		free_tokens(&mshell->tokens);
		return (MINISHELL_READLINE);
	}
	print_tokens(mshell->tokens);
	return (MINISHELL_PARSER);
}
