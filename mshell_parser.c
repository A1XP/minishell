/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:56:44 by natallia          #+#    #+#             */
/*   Updated: 2025/02/17 14:35:47 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_parser(t_mshell *mshell)
{
	int	status;

	status = PARSER_DEFAULT;
	parse_input(mshell->tokens, &mshell->ast, &status);
	if (mshell->tokens)
		free_tokens(&mshell->tokens);
	if (status == PARSER_CRITICAL_ERROR)
		return (MINISHELL_CLEANUP);
	if (status == PARSER_ERROR)
	{
		free_ast(&mshell->ast);
		return (MINISHELL_READLINE);
	}
	print_ast(mshell->ast, 0);
	return (MINISHELL_EXECUTER);
}
